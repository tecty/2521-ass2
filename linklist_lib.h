#ifndef LINKLIST_H
#define LINKLIST_H

#include <stdlib.h>
#include <string.h>
#include "strdup.h"

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
    int total;
} *link;

void push_l(link l, char *val);
void join_l(link l, char *val);
char *pop_l(link l);
char *leave_l(link l);
void show_l(link l);
void print_l(link l, FILE *fp);
link init_link();
void filter_l(link keep, link filter);
int count_l(link l);

#endif
