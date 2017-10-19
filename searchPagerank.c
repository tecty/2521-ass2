// the searching engine for invertedIndex
#include "index_lib.h"



int main(int argc, char const *argv[]) {
    /* read the file and try to search something */
    if (argc<= 1) {
        /* insufficient input */
        fprintf(stderr, "Usage: %s keywords..\n",argv[0] );
        exit(1);
    }

    // construct the index by file
    read_index();

#ifdef DEBUG
    // show the index it has read
    // show_index(NULL);
#endif


    // search for the table
    for (int i = 1; i < argc; i++) {
        /* give all the keywords to table */
        search_index((char *) argv[i]);
    }

    // print the result
    print_l(get_result(),NULL);

    return 0;
}
