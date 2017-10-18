#include "priority_q.h"

char **nameArray;
int total_files = 0;

//ensure that the same page will always locate to the same position in the WCP chart
void distnameArray_init(int size){
    nameArray = malloc(size*sizeof(char *));
    total_files = size;
    for(int i = 0; i < size; i++){
        nameArray[i] = NULL;
    }
}

void distnameArray_free(){
    free(nameArray);
}

int find_page(char *pageName){
    //printf("FINDING %s in %d files\n", pageName, total_files);
    int i;
    for(i = 0; i<total_files && nameArray[i]!=NULL; i++){
        if(strcmp(nameArray[i], pageName)==0) return i;
    }
    if(i<total_files){
        //printf("Now %d files are registered\n", i);
        nameArray[i] = pageName;
        return i;
    }
    return -1;
}

pq_node init_pq_node(int index, int order){
    pq_node new = malloc(sizeof(struct pq_node_t));
    // initial the value in the node
    new->index = index;
    new->order = order;
    new->dist  = 0;
    new->next  = NULL;

    // return this struct
    return new;
}

priority_q init_pq(int size){
    // initial the structure of priority_q
    priority_q new = malloc(sizeof(struct priority_q_t));
    // give the initil value
    new ->size = size;
    // initil the node tables;
    new ->list = malloc(size* size * sizeof(struct pq_node_t));
    // initial all the node in the table
    for (int x = 0; x < size; x++) {
        for (int y = 0; y < size; y++) {
            /* for all the node in the table, initial it */
            new->list[x*size + y] = init_pq_node(x,y);
        }
    }
    new->head = NULL;
    // initial the distance recorder
    new->total = 0;

    // return initialised struct
    return new;
}
void join_pq(priority_q q, char *pageName, int order, double dist){
    // set the correspond node to have that distance
    int index = find_page(pageName);
    q->list[index* q->size + order]->dist += dist;
}

int pq_cmp(const void *a, const void *b){
    // compare the value by the distance
    pq_node * n1 = (pq_node *)a;
    pq_node * n2 = (pq_node *)b;
    // calculate the diff between the value hold in both nodes
    double diff = (*n1) ->dist - (*n2) -> dist;
    // base the difference, return the compare result

    if (diff>0) {
        /* a > b */
        return 1;
    }
    else if (diff <0) {
        /* a < b */
        return -1;
    }

    // they are equal
    return 0;
}

// keep the sorted result as a linklist and not use the table anymore
void sort_pq(priority_q q){
    // use the system lib quick sort to sort the list hode in the structure
    qsort(q->list, q->size * q->size, sizeof(pq_node),pq_cmp);

    // base the sorted list, generate the link list
    // set the head
    q->head = q->list[0];
    // set the remain node;
    for (int n = 0; n < q->size * q->size -1; n++) {
        // arrange the links
        q->list[n]->next = q->list[n+1];
    }
    // free the memory used by the node list
    free(q->list);
    // give a flag to say this priority queue is sorted
    q->list = NULL;
}

pq_node do_leave_pq(pq_node this, int index , int order){
    // recursive remove the node contain the right index or order
    if (this == NULL) {
        /* the end of the list */
        return NULL;
    }
    // else: the list is not ended
    if (this->index == index || this->order == order) {
        /* this node should be remove */
        // record the next node to assemble the return node
        pq_node next_node = this->next;

#ifdef DEBUG
        printf("Leave node index = %d, order = %d\n",index, order );

#endif
        // free this node's memory
        free(this);
        // calculate the return value
        return do_leave_pq(next_node, index, order);
    }

    // this node may keep, arrange the link and return;
    this->next= do_leave_pq(this->next, index, order);
    return this;
}

int leave_pq(priority_q q, int *result){
    if (q->list != NULL) {
        /* the queue is not leaved */
        // sort the list
        sort_pq(q);
    }
#ifdef DEBUG

    printf("\nTry to leave a node in queue\n");
    //test if sorted
    int smallCount = 0;
    printf("SORT!\n");
    for(pq_node p = q->head; p!=NULL; p = p->next){
        printf("%lf->", p->dist);
        if((smallCount+1)%5==0) putchar('\n');
        smallCount++;
    }
    

#endif
    // special situation, all the node has leaved the queue
    if (q->head == NULL) {
        /* code */
        return -1;
    }
    //  else:
    // the index that removed in this leave
    int order = q->head->order;
    result[order] = q->head->index;
    // update the total distance
    q->total += q->head->dist;

    // set up the new head by removing the nodes
    q->head = do_leave_pq(q->head,q->head->index, q->head->order);

    // return this index for this leave
    return order;
}
