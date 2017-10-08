int hash(char *str, int size){



}

int name(/* arguments */) {
    /* code */
    return 0;
}

void expand_table(hash_table t) {
    /* expand the insufficient */
    t->max *= 2;
    // intilise the pointer array for nodes
    hash_node *new_table = malloc(t->table, t->max * sizeof(struct hash_node));
    assert(hash_table!= NULL);
    for (int i = 0; i < max; i++) {
        /* clear all the pointer to NULL */
        new_table[i] = NULL;
    }

    for (int i = 0; i < t->max/2; i++) {
        /* search all the node in the table */
        if (t->table[i]!= NULL) {
            /* this slot has record，record this in the new table */
            new_table[hash(t->table[i]->key, t->max)] = t->table[i];
        }
    }
    // swap the table
    free(t->table);
    t->table = new_table;
}


hash_table init_table(){
    // malloc the space of hash_table
    new = malloc(sizeof(struct hash_table_t));
    assert(new != NULL);
    // initialised the table size
    new->nItem=0;
    new->max= 4;
    // malloc the array for pointer to actual value record
    new-> table = malloc(new->max * sizeof(struct hash_node));
    assert(new->table != NULL);
    for (int i = 0; i < new->max; i++) {
        /* ini all slot with NULL */
        new->table[i]= NULL;
    }
    return new;
}
