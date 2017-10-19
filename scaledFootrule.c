#include "r_aggr.h"
/**
*  All of the code in this assignment is written by Toby Huang z5141448 and
*  Maggie Zhu z5141541. No reference code from any tut or lab in 2521.
*
*  Explaination "smart" Algroithm in Part3:
*  This algroithm is base on the Hungarian algorithm with some improvement.
*  First we generate a matrix-like list to record any possible distance for each page in different
*  positions. Then, we use a priority queue to sort the list and leave the smallest distance node in the
*  queue, which contain its page_name and derived proper rank. After the queue is empty, generate
*  a link-list of urls that contains the final order of page_names. Finally, we print
*  all the pagenames in the link list and the minimal total distance.
*
*  To have a better understanding, you can compile with -DDEBUG
*  
*
**/
int main(int argc, char const *argv[]) {
    /* main for scaledFootrule */
    if (argc <= 1) {
        /* insufficient input */
        fprintf(stderr, "Usage: %s Indexed files\n", argv[0] );
        exit(1);
    }

    // buffer to sotre the readed page name
    char buff[100];

    for (int i = 1; i < argc; i++) {
        /* read sorted file, and sent it into rank */
        // the link list to store the sorter order
        link list = init_link();


        // try to open the file
        FILE *fp = fopen(argv[i],"r");

        if (fp == NULL) {
            /* open the file failed */
            continue;
        }

        while (!feof(fp) && fscanf(fp, "%s", buff) ==1) {
            /* read all the link in the file */
            // construct the ordered link list
            join_l(list, buff);
        }

        // insert the sorted in to the system
        insert_rank(list);
    }

    // show the final result
    show_rank(NULL);


    return 0;
}
