#include "graph.h"

int getIdByKey(graph g, char *key){
    for (int i = 0; i < g->nV; i++) {
        /* get all the key */
        if (strcmp(g->str_l[i], key)==0) {
            /* found the key */
            return i;
        }
    }
    //  the vertex has no found
    return -1;
}

void insert_edge(graph g, int src, int dest) {
    /* insert_edge by id */
    if (src!=dest) {
        g->edges[src][dest] =1;
        g->inlink[dest]++;
        g->outlink[src]++;
    }

}


graph initGraph(int nV){
    // base on the nv initialised the graph
    graph new = malloc(sizeof(struct graph_t));
    assert(new != NULL);
    // initialised the graph info
    new->nV = nV;
    new->nE = 0;
    // initialised the edges array
    new->edges = malloc(nV * sizeof(int *));
    assert(new->edges!= NULL);
    for (int i = 0; i < nV; i++) {
        /* malloc all the sub list in memory */
        new->edges[i]= malloc(nV * sizeof(int *));
        assert(new->edges[i]!= NULL);
        /* reset the int value in edge list */
        memset(new->edges[i], 0, nV*sizeof(int));
    }
    // intilise an empty pointer array
    new->str_l = malloc(nV* sizeof(char *));
    assert(new->str_l != NULL);
    // intilise all the hash_tables
    new->content = malloc(g->nV * sizeof(hash_table));
    for (int i = 0; i < nV; i++) {
        /* initialise tables */
        new ->content[i] = init_table();
    }

    //initialised all the inlink and outlink table
    g->inlink= malloc(nV * sizeof(int));
    g->outlink= malloc(nV * sizeof(int));
    for (int i = 0; i < nV; i++) {
        /* initila to all 0 table */
        g->inlink[i] = g->outlink[i] = 0;
    }

    return new;
}
