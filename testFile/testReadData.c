#include "readData.h"
#include "graph.h"

int main() {
    /* test readData's function */
    graph g = initGraph(0);

    // test1: getCollection
    getCollection(g);
    // print the output in getCollection
    for (int i = 0; i < g->nV; i++) {
        printf("%s\n", g->str_l[i]);
    }




    return 0;
}
