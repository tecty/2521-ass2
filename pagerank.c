#include "pr_lib.h"
#include "index_lib.h"

int main(int argc, char const *argv[]) {

    double d, diffPR;
    int maxIteration;

    // try to read from command line
    if (argc != 4 ||
        sscanf(argv[1],"%lf", &d )!=1  ||
        sscanf(argv[2],"%lf", &diffPR )!=1  ||
        sscanf(argv[3],"%d", &maxIteration )!=1
        ) {
        /* insufficient data or wrong data */
        fprintf(stderr, "Usage: %s d diffPR maxIteration\n",argv[0] );
        exit(1);
    }

    graph g = initGraph(0);
    // getCollection the information form file
    getCollection(g);
    // calculate the pagerank
    PageRankW(g,d,diffPR,maxIteration);
    sort_by_pr();

    // try to write to a file
    FILE *fp=fopen("pagerankList.txt","w+");
    show_pagerank(fp);
    fclose(fp);

    // get the invertedIndex
    set_index(g);

    // print the index into the file
    fp = fopen("invertedIndex.txt","w");
    show_index(fp);
    fclose(fp);

    return 0;
}
