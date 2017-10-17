#include "r_aggr.h"
int *dist;

// record all the given order by a list
int order_count =0;
link *order_list = NULL;
// count how many files has inputed
int file_count =0;

double abs_d (double d ){
    // return the absolute val
    if (d <0 ) {
        return -d;
    }
    return d;
}

double cal_dist(int order ,int expect_order, int list_len){
    // calculate this page dist in this order
    // order would start at 0 here
    return abs_d((order +1)/(double)list_len
            - (expect_order+1)/(double)file_count );
}

void get_rank(FILE *fp){
    // print the final rank by a list
    if (fp == NULL) {
        /* print the result in the command line */
        fp = stdout;
    }

    // have a hashTable to reduce the duplicate page
    hashTable t = init_table();

    //tmp node for insert
    hash_node this_hash_node;

    for (int i = 0; i < order_count; i++) {
        for (ll_node this_ll_node = order_list[i]; this_ll_node != NULL;
            this_ll_node = this_ll_node->next) {
            /* read all given order, get all the pagename */
            // try to insert this name
            this_hash_node = find_node(t, this_ll_node->val);
            if (this_hash_node != NULL) {
                /* insert this pagename */
                this_hash_node = insert_node(t, this_ll_node->val);

                // given it a unique pageno
                this_hash_node->val.i = t->nItem -1;
            }
        }
    }

    // record the file_count;
    t->nItem;

    // initial the priority_q with the size of pages
    priority_q queue init_pq(t->nItem);

    // tmp pointer for the page name
    char * this_page;

    for (int i = 0; i < order_count; i++) {
        /* for all the given order, increment it's distance */
        // tmp for count the order for each page
        int this_order = 0;
        // record how many pages in the order
        int list_len = count_l(order_list[i]);
        while ((this_page = pop_l(order_list[i]))!= NULL) {
            /* for all the pagename */
            // get this pageid from hash table
            int this_page_no = find_node(t,this_page)->val.i;

            for (int o = 0; o < t->nItem; o++) {
                /* for all the order of this page, update its' value */
                join_pq(queue,this_page_no,o,cal_dist(this_order,o,list_len));
            }
        }
    }

    // generalise the hashtable by it's pageno
    sort_table_by_int(t);


    // final list of order for return
    link l = init_link();
    // search the pagename by leaved pageno
    join_l(l, t->table[leave_pq(q)]->key);

    // free the table has used
    for (size_t i = 0; i < order_count; i++) {
        /* free the link list */
        free (order_list[i]);
    }
    // free the table for order_list
    free(order_list);
    order_list = NULL;
    order_count = 0;
}


void insert_rank (link this_order){
    if (order_count == 0) {
        /* this is the first given order */
        order_list = malloc((order_count+1) * sizeof(link) );
    }
    else{
        // realloc the table
        order_list = realloc(order_list,(order_count+1) * sizeof(link) );
    }
    // record the given order_list
    order_list[order_count]= this_order;
    order_count ++;

}
