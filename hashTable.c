#include "hashTable.h"
#include "string.h"

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
void expand_table(hash_table table) {
    /* double the table size */
    table->max *= 2;

    // pointer list
    hash_node *new = malloc(table->max * sizeof(hash_node));
    assert(new != NULL);
    // suppor for old c standard
    int i=0;

    // initial the table
    for (i = 0; i < table->max; i++) {
        /* initial all table, pointing then to NULL */
        new[i] = NULL;
    }

    int trial = 0;
    // rehashing the table
    for (i = 0; i < table->max/2; i++) {
        /* for every key value in the old str_table */
        // reset the trial
        trial = 0;
        if (table->table[i]!= NULL) {
            /* this location has value before, do rehashing */
            hash_node this_node =  table ->table[i];
            while (trial< table->max/2) {
                /* try to inser this node into new table */
                int this_hash =hash(this_node->key, trial, table->max);
                if (new[this_hash]== NULL) {
                    /* this slot is empty, insert into this slot */
                    new[this_hash] = this_node;
                    break;
                }else{
                    trial ++;
                }
            }
        }
    }


    // free the old table
    free(table->table);

    // assign the new one to pressive
    table->table = new;
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
    if (t->nItem > (t->max/3) *2) {
        /* couldn't be more than 2/3 of max */
        expand_table(t);
    }
    int  this_slot;
    while ((this_slot = find_slot(t,key)) == -t->max -1) {
        /* couldn't find slot for this key */
        expand_table(t);
    }

    // the slot number must exist in the table
    assert(this_slot<=0);

    t->nItem++;

    // insert for this node
    hash_node new = malloc(sizeof(struct hash_node_t));

    // check whether this is successful malloc
    assert(new != NULL);

    // duplicate its' key
    new->key = strdup(key);

    // return this_node
    return t->table[-this_slot -1 ]  = new;
}


int hash_node_cmp(const void *a,const void *b){
    // cmpare function for using in C-lib qsort;
    hash_node *n1 = (hash_node *) a;
    hash_node *n2 = (hash_node *) b;
    // return the comparison
    return strcmp((*n1)->key, (*n2)->key);
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

    // sorting the table by the string in the struct
    qsort(t->table,t->max, sizeof(hash_node),hash_node_cmp);
}

int hash_node_cmp_int(const void *a,const void *b){
    // cmpare function for using in C-lib qsort;
    hash_node *n1 = (hash_node *) a;
    hash_node *n2 = (hash_node *) b;
    // return the comparison
    return (*n1)->val.i - (*n2)->val.i;

}

void sort_table_by_int(hash_table t){
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

    // sorting the table by the string in the struct
    qsort(t->table,t->max, sizeof(hash_node),hash_node_cmp_int);

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
