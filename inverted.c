#include "index_lib.h"


int main() {
    graph g= initGraph(0);
    // get all the collection form file
    getCollection(g);

    // set the index by the graph
    set_index(g);
    // print the index into file
    show_index(NULL);

    return 0;
}
