#include "hashTable.h"
int main() {
    /* test case for hashTable */
    hash_table t = init_table();
    // insert_node(t, "human");
    // insert_node(t, "observations");
    // insert_node(t, "nasa");
    // insert_node(t, "intelligent");
    // printf("this_slot has key %s\n", find_node(t, "human")->key);
    // printf("this_slot has key %s\n", find_node(t, "observations")->key);
    // printf("this_slot has key %s\n", find_node(t, "nasa")->key);
    // printf("this_slot has key %s\n", find_node(t, "intelligent")->key);
    // printf("current table has sieze %d\n", t->max);
    //
    // insert_node(t, "surface");
    // insert_node(t, "weather");
    // insert_node(t, "that");
    // insert_node(t, "moons");
    // printf("this_slot has key %s\n", find_node(t, "surface")->key);
    // printf("this_slot has key %s\n", find_node(t, "weather")->key);
    // printf("this_slot has key %s\n", find_node(t, "that")->key);
    // printf("this_slot has key %s\n", find_node(t, "moons")->key);
    //
    // insert_node(t, "revealed");
    // insert_node(t, "sun");
    // insert_node(t, "and");
    // insert_node(t, "telescopic");
    // printf("this_slot has key %s\n", find_node(t, "revealed")->key);
    // printf("this_slot has key %s\n", find_node(t, "sun")->key);
    // printf("this_slot has key %s\n", find_node(t, "and")->key);
    // printf("this_slot has key %s\n", find_node(t, "telescopic")->key);
    // insert_node(t, "ascribed");
    // insert_node(t, "landing");
    // insert_node(t, "of");
    // insert_node(t, "man");
    // printf("this_slot has key %s\n", find_node(t, "ascribed")->key);
    // printf("this_slot has key %s\n", find_node(t, "landing")->key);
    // printf("this_slot has key %s\n", find_node(t, "of")->key);
    // printf("this_slot has key %s\n", find_node(t, "man")->key);
    // insert_node(t, "cycles");
    // insert_node(t, "on");
    // insert_node(t, "attributed");
    // insert_node(t, "features");
    // printf("this_slot has key %s\n", find_node(t, "cycles")->key);
    // printf("this_slot has key %s\n", find_node(t, "on")->key);
    // printf("this_slot has key %s\n", find_node(t, "attributed")->key);
    // printf("this_slot has key %s\n", find_node(t, "features")->key);
    // insert_node(t, "interest");
    // insert_node(t, "long");
    // insert_node(t, "early");
    // insert_node(t, "experiments");
    // printf("this_slot has key %s\n", find_node(t, "interest")->key);
    // printf("this_slot has key %s\n", find_node(t, "long")->key);
    // printf("this_slot has key %s\n", find_node(t, "early")->key);
    // printf("this_slot has key %s\n", find_node(t, "experiments")->key);
    // insert_node(t, "vegetation");
    // insert_node(t, "promise");
    // insert_node(t, "small");
    // printf("this_slot has key %s\n", find_node(t, "vegetation")->key);
    // printf("this_slot has key %s\n", find_node(t, "promise")->key);
    // printf("this_slot has key %s\n", find_node(t, "small")->key);


    insert_node(t,"human");
    insert_node(t,"observations");
    insert_node(t,"nasa");
    insert_node(t,"intelligent");
    insert_node(t,"surface");
    insert_node(t,"weather");
    insert_node(t,"that");
    insert_node(t,"moons");
    insert_node(t,"revealed");
    insert_node(t,"sun");
    insert_node(t,"and");
    insert_node(t,"telescopic");
    insert_node(t,"ascribed");
    insert_node(t,"landing");
    insert_node(t,"of");
    insert_node(t,"man");
    insert_node(t,"cycles");
    insert_node(t,"on");
    insert_node(t,"attributed");
    insert_node(t,"features");
    insert_node(t,"interest");
    insert_node(t,"long");
    insert_node(t,"early");
    insert_node(t,"experiments");
    insert_node(t,"vegetation");
    insert_node(t,"promise");
    insert_node(t,"small");
    insert_node(t,"winds");
    insert_node(t,"apparent");
    insert_node(t,"robot");
    insert_node(t,"volcano");
    insert_node(t,"moon");
    insert_node(t,"high");
    insert_node(t,"rays");
    insert_node(t,"to");
    insert_node(t,"weather");
    insert_node(t,"robotics");
    insert_node(t,"seasonal");
    insert_node(t,"planets");
    insert_node(t,"design");
    insert_node(t,"light");
    insert_node(t,"japan");
    insert_node(t,"circle");
    insert_node(t,"red");
    insert_node(t,"jupiter");
    insert_node(t,"the");
    insert_node(t,"planet");
    insert_node(t,"been");
    insert_node(t,"pluto");
    insert_node(t,"sun");
    insert_node(t,"were");
    insert_node(t,"volcano");
    insert_node(t,"color");
    insert_node(t,"eu");
    insert_node(t,"jupitor");
    insert_node(t,"waves");
    insert_node(t,"linear");
    insert_node(t,"has");
    insert_node(t,"changes");
    insert_node(t,"seasonal");
    insert_node(t,"mars");
    insert_node(t,"sun");
    insert_node(t,"subject");


    // show all the  record in the table;s
    show_table(t);

    // try to generalise_table
    generalise_table(t);

    show_table(t);


    return 0;
}
