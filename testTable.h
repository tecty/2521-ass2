#ifndef HASH_TABLE_H
#define HASH_TABLE_H
union val_u{
    // multi type of union
    double d;
    int i;
    // this two kind of val type
    // queue q;
    // stack s;

}

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


#endif
