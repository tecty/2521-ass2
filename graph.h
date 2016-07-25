#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "hashTable.h"

#define PAGE_PATH "ex1/"

typedef struct graph_t {
    int nV;
    int nE;
    int **edges;
    int *inlink;
    int *outlink;
    char **str_l;
    hash_table *content;
} *graph;

graph initGraph(int nV);


#endif
