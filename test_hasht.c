#include "hashTable.h"
int main() {
    /* test case for hashTable */
    hash_table t = init_table();
    insert_node(t, "a");
    insert_node(t, "b");
    insert_node(t, "c");
    insert_node(t, "d");
    printf("this_slot has key %s\n", find_node(t, "a")->key);
    printf("this_slot has key %s\n", find_node(t, "b")->key);
    printf("this_slot has key %s\n", find_node(t, "c")->key);
    printf("this_slot has key %s\n", find_node(t, "d")->key);
    printf("current table has sieze %d\n", t->max);


    return 0;
}
