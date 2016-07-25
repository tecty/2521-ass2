#include "readData.h"

void getSect1(graph g,FILE fp,int src){
    char * buff[1000];
    while (!feof(fp) && fscanf(fp, "%s",buff)){
        int dest = getIdByKey(g,buff);
        // insert_edge(src,dest)

        if (strcmp("#end", buff)) {
            /* push one more to end this session*/
             fscanf(fp, "%s",buff);
             break;
        }
    }
}


void getContent(graph g){
    // path for each pages
    char * path[100];
    for (int i = 0; i < g->nV; i++) {
        /* for all the pages */
        sprintf(path, "%s,%s",PAGE_PATH, g->str_l[i]);
        FILE *fp = fopen(path, "r");
        // buffer for record each words in a page
        char * buff[1000];
        while (!feof(fp) && fscanf(fp, "%s",buff)) {
            /* get all the buff */
            if (strcmp("#start", buff)==0){
                // start a session
                // read one more to get the session code;
                 fscanf(fp, "%s",buff);
                 if (strcmp("Section-1",buff)) {
                     /* read all the link */
                     getSect1(g, fp)
                 }
            }
        }
    }


}

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
    g->edges = realloc(g->edges,g->nV * sizeof(int *));
    assert(g->edges!= NULL);
    for (int i = 0; i < g->nV; i++) {
        /* malloc all the sub list in memory */
        g->edges[i]= realloc(g->edges[i],g->nV * sizeof(int *));
        assert(g->edges[i]!= NULL);
        /* reset the int value in edge list */
        for (int j = 0; j < g->nV; j++) {
            /* initialised all the edges */
            g->edges[i][j]= 0;
        }

    }
    // intilise all the hash_tables
    g->content = realloc(g->content,g->nV* sizeof(hash_table));
    for (int i = 0; i < nV; i++) {
        /* initialise tables */
        g ->content[i] = init_table();
    }
    //initialised all the inlink and outlink table
    g->inlink= realloc(g->inlink,g->nV * sizeof(int));
    g->outlink= realloc(g->outlink,g->nV * sizeof(int));
    for (int i = 0; i < g->nV; i++) {
        /* initila to all 0 table */
        g->inlink[i] = g->outlink[i] = 0;
    }


    // get the content by the page provide
    getContent(g);

}
