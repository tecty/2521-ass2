#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>


typedef struct graph_t {
    int nV;
    int nE;
    int **edges;
    char **str_l;
} *graph;

graph initGraph(int nV);


#endif
