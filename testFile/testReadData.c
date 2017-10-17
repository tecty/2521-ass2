#include "readData.h"
#include "graph.h"
#include "pr_lib.h"

int main() {
    /* test readData's function */
    graph g = initGraph(0);

    // test1: getCollection
    getCollection(g);

    // show what's has read
    showGraph(g);

    // calculate the pagerank
    PageRankW(g,0.85,0.00001,1000);

    printf("\nPageranks\n" );
    // show the pagerank
    show_pagerank(NULL);
    // show the weight_in and weight_out
    show_weight();


    // sort them and show the result
    sort_by_pr();
    show_pagerank(NULL);

    return 0;
}
