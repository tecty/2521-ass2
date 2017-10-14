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
    int this_hash = (int) (hash1(str, 1) + trail * hash1(str, 3)) % size;
    if (this_hash<0) {
        /* have the absolute value of hash value */
        this_hash = - this_hash;
    }

    return this_hash;
}

int find_slot(hash_table t,char * key){
    // find a slot for provide key
    int this_slot = -1;
    for (int trail = 0; trail < t->max; trail++) {
        // find through the table by exhause the trail
        this_slot = hash(key, trail, t->max);

        // printf("imhere %d %d\n", this_slot);
        if (t->table[this_slot] == NULL) {
            /* found the empty slot for this key */
            return -this_slot-1;
        }
        else if (strcmp(t->table[this_slot]->key,key)== 0) {
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
    int trial = 0;
    for (int i = 0; i < t->max/2; i++) {
        /* search all the node in the table */
        if (t->table[i]!= NULL) {
            /* this slot has record，record this in the new table */
            while ( trial < t->max) {
                /* found new slot for this key */
                int this_slot = hash(t->table[i]->key,trial,t->max);
                if (new_table[this_slot] == NULL) {
                    /* here is an empty slot for insert this */
                    new_table[this_slot]= t->table[i];
                    // break the loop for this insertion
                    break;
                }
                trial++;
            }
            if (trial == t->max) {
                /* this table is not enought too.. */
                free(new_table);
                expand_table(t);
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
        expand_table(t);
        #ifdef DEBUG
            // debug output
            printf("couldn't find slot, so expand the table %d, for %s\nexpand to size %d\n", this_slot,key, t->max);
        #endif

        this_slot = find_slot(t, key);

    }
    if (this_slot >= 0) {
        /* end the programme */
#ifdef DEBUG
        printf("Error in slot %d\n",this_slot );
        printf("the slot has key: %s ; search for key '%s'\n","null",key );
        show_table(t);
#endif
        assert(this_slot<0);
    }
    // no this key in table;
    hash_node this_node = malloc(sizeof(struct hash_node_t));
    this_node->key = strdup(key);
    // refresh the counter of table
    t->nItem ++;

    // return this_node
    return t->table[-this_slot -1 ]  = this_node;
}


void generalise_table(hash_table t){
    int slow = 0;
    for (int this = 0; this < t->max; this++) {
        /* search for no empty slot */
        if (t->table[this] != NULL) {
            /* this slot is not empty */
            t->table[slow] = t->table[this];
            slow ++;
        }
    }
    // resize this table;
    t->max = t->nItem;
    t->table = realloc(t->table, t->max*sizeof(hash_node));
}

void show_table(hash_table t){
    for (int this = 0; this < t->max; this++) {
        /* search for all the node in the table */
        if (t->table[this] != NULL) {
            /* print out this_node */
            printf("%d:%s ", this,t->table[this]->key);
        }
    }
    printf("\n" );

}
