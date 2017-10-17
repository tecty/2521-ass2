#ifndef LINKLIST_H
#define LINKLIST_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct linklist_t {
    /* a linklist */
    char *val;
    struct linklist_t *prev;
    struct linklist_t *next;
} *ll_node;


typedef struct link_t {
    /* a queue point to start node and an end */
    ll_node head;
    ll_node tail;
} *link;

void push_l(link l, char *val);
void join_l(link l, char *val);
char *pop_l(link l);
char *leave_l(link l);
void show_l(link l);
link init_link();
void filter_l(link keep, link filter);
// show the order by just print new line, without any format
void print_l(link l);

#endif
