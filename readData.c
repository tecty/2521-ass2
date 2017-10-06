#include "readData.h"

// provide a initialised graph, even it has nV = 0
void getCollection(graph g){
    // open the file
    FILE *fp = fopen("ex1/collection.txt");
    char buff[1024];
    while (!feof(fp) && fscanf(fp,"%s", buff)) {
        /* scan all the url name */
        g->

    }




}
