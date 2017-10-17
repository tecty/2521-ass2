#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include "linklist_lib.h"

union val_u{
    // multi type of union
    double d;
    int i;
    // in the linklist lib, the type
    link l;

};

typedef struct hash_node_t {
    char *key;
    union val_u val;

} * hash_node;

typedef struct hash_table_t {
    int max;
    int nItem;
    // point to the data node, which actually record the data
    hash_node *table;

} *hash_table;

hash_table init_table();
hash_node find_node(hash_table t, char * key);
hash_node insert_node(hash_table t , char* key);

// generalise_table to a table has length = nItem
void generalise_table(hash_table t);

// sort the table by the val.i
void sort_table_by_int(hash_table t);


// show all the key in table
void show_table(hash_table t);
#endif
