#include "pr_lib.h"
/* Local Variables */

// store the table for the pagerank
double *PR;
double *prevPR;

// record the size of graph
int size;


// store the graph to pass
graph this_graph;




double weight_in(int src, int dest){
    double denominator = 0;

    for (int i = 0; i < size; i++) {
        /* search for the page could go from src */
        if (this_graph->edges[src][i]){
            // here is a edge
            denominator += this_graph->inlink[i];
        }
    }

    if (denominator == 0) {
        /* prevent from devide of 0 */
        denominator = 0.5;
    }
    return this_graph->inlink[dest] /denominator;
}

double weight_out(int src, int dest){
    double denominator = 0;

    for (int i = 0; i < size; i++) {
        /* search for the page could go from src */
        if (this_graph->edges[src][i]){
            // here is a edge
            denominator += this_graph->outlink[i];
        }
    }

    if (denominator == 0) {
        /* prevent from devide of 0 */
        denominator = 0.5;
    }
    // printf("i = %d j = %d\n",src,dest );
    // printf("%d / %lf\n",this_graph->outlink[dest] ,denominator );
    return this_graph->outlink[dest]/denominator;
}


void PageRank( double d, int index){
    // the sum of last part
    double sum = 0;
    for (int j = 0; j < size; j++) {
        /* for searching of all the page which has the dest is this page */
        if (this_graph->edges[j][index]) {
            /* here is a required page */
            sum += prevPR[j] * weight_in(j,index) *weight_out(j,index);
        }
    }

    // setting the new pagerank
    PR[index] = (1-d)/(double)size + d* sum;
}


double push_PR(){
    // update the pagerank
    double diff = 0;
    for (int i = 0; i < size; i++) {
        /* go through the lists of pr */
        diff += abs_d(prevPR[i] - PR[i]);
        // push the pagerank
        prevPR[i] = PR[i];
    }
    return diff;
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
        PR[i] = prevPR[i] = 1/(double) size;
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

            PageRank(d,src);
        }

        // get the diff for this iteration from push_PR
        diff = push_PR();

        // increament the iteration
        iteration ++;
    }


}


void sort_by_pr(){
    // sorting by pagerank
    int swaped = 1;
    double tmp;
    while (swaped) {
        /* ez bubble sort */
        swaped = 0;
        for (int i = 0; i < size-1; i++) {
            /* for the whole list */
            if (PR[i] < PR[i+1]) {
                /* swap them */
                swap_vertex(this_graph,i,i+1);
                // swap the pagerank
                tmp = PR[i];
                PR[i] = PR[i+1];
                PR[i+1] = tmp;
                swaped ++;
            }
        }


    }

}

void show_weight(){
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            /* for all the edge in the graph */
            if (this_graph->edges[i][j]) {
                /* calculate it's weight_in and weight_out */
                printf("win[%d][%d] = %lf , ",i,j,weight_in(i,j) );
                printf("wout[%d][%d]= %lf\n",i,j,weight_out(i,j) );
            }
        }
    }

}
void show_pagerank(FILE *fp) {
    if (fp == NULL) {
        /* print to stdio */
        fp = stdout;
    }
    /* show the calculated pagerank */
    for (int this = 0; this < size; this++) {
        /* for the last iteration of pagerank */
        fprintf(fp,"%s, %d, %.7f\n",this_graph->str_l[this],this_graph->outlink[this],PR[this] );
    }
}

hash_table read_pagerank(FILE *fp){
    if (fp == NULL) {
        /* go to the default place to find the pagerank list */
        fp = fopen("pagerankList.txt","r");
        // check whether the file is successful opened
        assert(fp!= NULL);
    }
    // not care about this value
    int dump;
    // temporary record the page's rank
    double pagerank;
    // temporary record the page_name
    char page_name[100];

    // temporary store the file
    char buff[1000];

    // store the page_name and table
    hash_table t = init_table();

    while (!feof(fp) &&
        fgets(buff,1000,fp)) {
        int len =  strlen(buff);
        for (int i = 0; i < len; i++) {
            /* replace all the , to " " */
            if (buff[i] == ',') {
                buff[i] = ' ';
            }
        }
        /* write it into hashTable */
        sscanf(buff,"%s %d %lf", page_name, &dump, &pagerank);
        insert_node(t, page_name) ->val.d = pagerank;
    }

    // sort the table by the inserted pagerank
    sort_table_by_double(t);

    return t;
}
