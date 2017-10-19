#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

// a very independent lib
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "strdup.h"

typedef struct pq_node_t {
    int index;
    int order;
    // distance of that index to place in that orders
    double dist;
    // after sorted it become a linklist
    struct pq_node_t * next;

} *pq_node;

typedef struct priority_q_t {
    // size of this matrix if the matrix is 5*5, the size is 5
    int size;
    // total distance after end of leaving
    double total;

    // a list of node, initial is 25 = 5*5, use as a 2D-array
    pq_node *list;
    // the head of the link list, after sorted
    pq_node head;
} *priority_q;

priority_q init_pq(int size);
void join_pq(priority_q q, char *pageName, int order, double dist);
void sort_pq(priority_q q);
int leave_pq(priority_q q, int *result);
void distnameArray_init(int size);
void distnameArray_free();
void show_pq(priority_q);
#endif
