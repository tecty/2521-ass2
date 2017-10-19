#include "index_lib.h"


int main() {
    graph g= initGraph(0);
    // get all the collection form file
    getCollection(g);

    // set the index by the graph
    set_index(g);
    // print the index into file
    FILE *fp = fopen("invertedIndex.txt","w");
    show_index(fp);
    // close the opened file
    fclose(fp);

    return 0;
}
