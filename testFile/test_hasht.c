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

    insert_node(t, "e");
    insert_node(t, "f");
    insert_node(t, "g");
    insert_node(t, "h");
    printf("this_slot has key %s\n", find_node(t, "e")->key);
    printf("this_slot has key %s\n", find_node(t, "f")->key);
    printf("this_slot has key %s\n", find_node(t, "g")->key);
    printf("this_slot has key %s\n", find_node(t, "h")->key);

    insert_node(t, "i");
    insert_node(t, "j");
    insert_node(t, "k");
    insert_node(t, "l");
    printf("this_slot has key %s\n", find_node(t, "i")->key);
    printf("this_slot has key %s\n", find_node(t, "j")->key);
    printf("this_slot has key %s\n", find_node(t, "k")->key);
    printf("this_slot has key %s\n", find_node(t, "l")->key);
    insert_node(t, "m");
    insert_node(t, "n");
    insert_node(t, "o");
    insert_node(t, "[]");
    printf("this_slot has key %s\n", find_node(t, "m")->key);
    printf("this_slot has key %s\n", find_node(t, "n")->key);
    printf("this_slot has key %s\n", find_node(t, "o")->key);
    printf("this_slot has key %s\n", find_node(t, "[]")->key);


    // show all the  record in the table;s
    show_table(t);

    // try to generalise_table
    generalise_table(t);

    show_table(t);


    return 0;
}
