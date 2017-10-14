/* Local Variables */

// store the table for the pagerank
double *PR;
double *prvePR;

// record the size of graph
int size;


// store the graph to pass
graph this_graph;




double weight_in(int src, int dest){


}

double weight_in(int src, int dest){


}


void PageRank(graph g, double d, int index){


}

void push_PR(){


}

void PageRankW(graph g, double d, double diffPR,int maxIteration){
    // set the graph
    this_graph = g;
    // set the graph size
    size = g->nV;


    // set the pr size
    PR = malloc(g->nV * sizeof(double));
    prevPR = malloc(g->nV * sizeof(double));
    for (int i = 0; i < g->nV; i++) {
        // initialised them to 1/n
        PR[i] = prevPR[i] = 1/size;
    }

    // starter of the loop
    double diff = diffPR;
    int iteration = 0;

    // try to find the pagerank
    while (diff >= diffPR && iteration <= maxIteration) {
        /* initialised the diff */
        diff = 0;
        for (int src = 0; src < size; src++) {
            /* every new pagerank */


        }

        for (int src = 0; src < size; src++) {
            // calculate the difference of this iteration;
            diff += PR[src] - prevPR[i];
        }
        // increament the iteration
        iteration ++;
    }






}
