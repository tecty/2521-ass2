#include "r_aggr.h"

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
