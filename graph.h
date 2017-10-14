#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "hashTable.h"

#define PAGE_PATH "ex2/"

typedef struct graph_t {
    int nV;
    int nE;
    int **edges;
    int *inlink;
    int *outlink;
    char **str_l;
    // counter for word of each page
    int *wc;
    hash_table *content;
} *graph;

graph initGraph(int nV);
// insert  the edge in the graph
void insert_edge(graph g, int src, int dest);
// search the id for the link
int getIdByKey(graph g, char *key);
// show all the information in the graph
// the value in the hash table must be int
void showGraph(graph g);

// swap the vertex and its content
void swap_vertex (graph g, int src, int dest);

#endif
