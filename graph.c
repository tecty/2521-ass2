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
        // prevent the self link
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
    new->content = malloc(new->nV * sizeof(hash_table));
    for (int i = 0; i < nV; i++) {
        /* initialise tables */
        new ->content[i] = init_table();
    }

    //initialised all the inlink, outlink, wordcount table
    new->inlink= malloc(nV * sizeof(int));
    new->outlink= malloc(nV * sizeof(int));
    new->wc= malloc(nV * sizeof(int));
    for (int i = 0; i < nV; i++) {
        /* initila to all 0 table */
        new->wc[i] = new->inlink[i] = new->outlink[i] = 0;
    }

    return new;
}

void showGraph(graph g) {
    /* show the link in the graph */
    for (int src = 0; src < g->nV; src++) {
        // print all the pages' name
        printf("%s : ", g->str_l[src]);
        // print its link table

        for (int dest = 0; dest < g->nV; dest++) {
            /* print every edges */
            printf("%d ", g->edges[src][dest]);
        }
        // print a new line
        printf("\n");
    }
    printf("\nThe information for helper table\n");
    for (int src = 0; src < g->nV; src++) {
        printf("%s: Wc:%d\tInlink:%d\tOutlin:%d\n",g->str_l[src],g->wc[src],g->inlink[src],g->outlink[src] );
    }

    printf("\nThe information in hash table\n" );

    // show the information in hash table
    for (int src = 0; src < g->nV; src++) {
        // print all the pages' name
        printf("%s : ", g->str_l[src]);

        // print the table
        for (int this_node = 0; this_node < g->content[src]->max; this_node++) {
            // print the information in this_node
            if (g->content[src]->table[this_node]!= NULL){
                // print the word and the counter
                printf("%s:%d ",g->content[src]->table[this_node]->key,
                        g->content[src]->table[this_node]->val.i );
            }
        }
        // print the new line
        printf("\n");
    }
}

void swap_vertex (graph g, int src, int dest){
    // a porary pointer
    void *tmp;

    // swap the edges
    tmp = g->edges[src];
    g->edges[src] = g->edges[dest];
    g->edges[dest] = tmp;

    // swap the str_l
    tmp = g->str_l[src];
    g->str_l[src] = g->str_l[dest];
    g->str_l[dest] = tmp;

    // swap the hashTable
    tmp = g->content[src];
    g->content[src] = g->content[dest];
    g->content[dest] = tmp;


    // integer tmp value
    int int_tmp;
    int_tmp = g->inlink[src];
    g->inlink[src] = g->inlink[dest];
    g->inlink[dest] = int_tmp;

    // swap outlink
    int_tmp = g->outlink[src];
    g->outlink[src] = g->outlink[dest];
    g->outlink[dest] = int_tmp;

    // swap word count
    int_tmp = g->wc[src];
    g->wc[src] = g->wc[dest];
    g->wc[dest] = int_tmp;

}
