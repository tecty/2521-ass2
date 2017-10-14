#ifndef LINKLIST_H
#define LINKLIST_H

typedef struct linklist_t {
    /* a linklist */
    char *val;
    ll_node next;
} *ll_node;


typedef struct link_t {
    /* a queue point to start node and an end */
    ll_node head;
    ll_node tail;
} *link;

void push(link l, char *val);
void pop(link l, char *val);
void leave(link l, char *val);

#endif
