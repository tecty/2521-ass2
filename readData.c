#include "readData.h"


// provide a initialised graph, even it has nV = 0
void getCollection(graph g){
    // open the file
    FILE *fp = fopen("ex1/collection.txt","r");
    int max = 4;
    char buff[1024];

    // initialised the array to store the string pointer
    g->str_l = malloc(max * sizeof(char * ));

    while (!feof(fp) && fscanf(fp,"%s", buff)) {
        /* scan all the url name */
        if (g->nV >= max) {
            /* the pointer array is not enought, resize the array */
            max *=2;
            g->str_l = realloc(g->str_l, max*sizeof(char *));
            assert(g->str_l != NULL);
        }
        // store the string into pointer array
        g->str_l[g->nV] = strdup(buff);
        g->nV ++;

    }

    // read to the end of the file
    fclose(fp);

    // resize the edge table;
    g->edges = malloc(g->nV * sizeof(int *));
    assert(g->edges!= NULL);
    for (int i = 0; i < g->nV; i++) {
        /* malloc all the sub list in memory */
        g->edges[i]= malloc(g->nV * sizeof(int *));
        assert(g->edges[i]!= NULL);
        /* reset the int value in edge list */
        memset(g->edges[i], 0, g->nV*sizeof(int));
    }

}
