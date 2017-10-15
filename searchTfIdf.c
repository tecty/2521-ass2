#include "index_lib.h"

int main(int argc, char const *argv[]){
    if(argc<=1){ //invalid input
        fprintf(stderr, "Usage: %s keywords..\n",argv[0]);
        exit(1);
    }
    
    //construct the index by file
    graph g = initGraph(0);
    getCollection(g);

}
