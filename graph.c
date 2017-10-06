#include "graph.h"


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
    g->str_l = malloc(nV* sizeof(char *));
    assert(g->str_l != NULL);
    return g;
}
