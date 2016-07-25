#include "hashTable.h"


unsigned int hash1(char *str,int seed){
    unsigned int sum= 0;
    while(*str){
        // get all the characters' sum
        sum += *str-'a';
        // bit shifting the sum up
        sum = sum << seed;
        str++;
    }
    // return the sum up
    return  sum;
}
int hash(char *str,int trail, int size){
    // double hashing to get the index of table
    return (int) (hash1(str, 1) + trail * hash1(str, 3)) % size;
}

int find_slot(hash_table t,char * key){
    // find a slot for provide key
    int this_slot = -1;
    for (int trail = 0; trail < t->max; trail++) {
        // find through the table by exhause the trail
        this_slot = hash(key, trail, t->max);

        if (t->table[this_slot] == NULL) {
            /* found the empty slot for this key */
            return -this_slot-1;
        }
        if (strcmp(t->table[this_slot]->key,key)== 0) {
            /* found the key  */
            return this_slot;
        }
    }
    // couldn't found a slot for this
    return -t->max-1;
}
void expand_table(hash_table t) {
    /* expand the insufficient */
    t->max *= 2;
    // intilise the pointer array for nodes
    hash_node *new_table = malloc(t->max * sizeof(hash_node));
    assert(new_table != NULL);
    for (int i = 0; i < t->max; i++) {
        /* clear all the pointer to NULL */
        new_table[i] = NULL;
    }
    for (int i = 0; i < t->max/2; i++) {
        /* search all the node in the table */
        if (t->table[i]!= NULL) {
            /* this slot has record，record this in the new table */
            for (int trail = 0; trail < t->max; trail++) {
                /* found new slot for this key */
                int this_slot = hash(t->table[i]->key,trail,t->max);
                if (new_table[this_slot] == NULL) {
                    /* here is an empty slot for insert this */
                    new_table[this_slot]= t->table[i];
                    // break the loop for this insertion
                    break;
                }
            }
        }
    }
    // swap the table
    free(t->table);
    t->table = new_table;
}

hash_table init_table(){
    // malloc the space of hash_table
    hash_table new = malloc(sizeof(struct hash_table_t));
    assert(new != NULL);
    // initialised the table size
    new->nItem=0;
    new->max= 4;
    // malloc the array for pointer to actual value record
    new-> table = malloc(new->max * sizeof(struct hash_node_t));
    assert(new->table != NULL);
    for (int i = 0; i < new->max; i++) {
        /* ini all slot with NULL */
        new->table[i]= NULL;
    }
    return new;
}

hash_node find_node(hash_table t, char * key){

    int this_slot = find_slot(t, key);
    if (this_slot<0){
        // no this key in table;
        if (this_slot == -t->max -1) {
            /* not enought slot for the table */
            expand_table(t);
        }
        return NULL;
    }
    // retrun the founded slot
    return t->table[this_slot];
}


hash_node insert_node(hash_table t , char* key){
    // calculate the slot for this key
    int  this_slot = find_slot(t, key);

    while (this_slot == - t->max -1) {
        /* the table don't have enought space for this key */
        #ifdef DEBUG
            // debug output
            printf("couldn't find slot to expand the table %d, for %s\n", this_slot,key);
        #endif
        expand_table(t);
        this_slot = find_slot(t, key);
    }
    assert(this_slot<0);
    // no this key in table;
    hash_node this_node = malloc(sizeof(struct hash_node_t));
    this_node->key = strdup(key);
    // return this_node
    return t->table[-this_slot -1 ]  = this_node;
}
