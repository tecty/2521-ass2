#include "readData.h"
#include "graph.h"

int main() {
    /* test readData's function */
    graph g = initGraph(0);

    // test1: getCollection
    getCollection(g);

    // show what's has read
    showGraph(g);

    



    return 0;
}
