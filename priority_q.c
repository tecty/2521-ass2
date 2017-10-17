#include "priority_q.h"
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
    new ->size = 0;
    // initil the node tables;
    new ->list = malloc(size* size * sizeof(struct pq_node_t));
    // initial all the node in the table
    for (int x = 0; x < size; x++) {
        for (int y = 0; y < size; y++) {
            /* for all the node in the table, initial it */
            new->list[x][y] = init_pq_node(x,y);
        }
    }
    new->head = NULL;
    // return initialised struct
    retrun new;
}
void join_pq(priority_q q, int index, int order, int dist){
    // set the correspond node to have that distance
    q->list[index][order]->dist = dist;
}

int pq_cmp(const void *a, const void *b){
    // compare the value by the distance
    pq_node * n1 = pq_node *a;
    pq_node * n2 = pq_node *b;
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
    q->head = q->list[0][0];
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
    if (this->index == index || this=order == order) {
        /* this node should be remove */
        // record the next node to assemble the return node
        pq_node next_node = this->next;

        // free this node's memory
        free(this);
        // calculate the return value
        return do_leave_pq(next_node, index, order);
    }

    // this node may keep, arrange the link and return;
    this->next= do_leave_pq(this->next, index, order);
    return this;
}

int leave_pq(priority_q q){
    if (q->list != NULL) {
        /* the queue is not leaved */
        // sort the list
        sort_pq(q);
    }
    // special situation, all the node has leaved the queue
    if (q->head == NULL) {
        /* code */
        return -1;
    }
    //  else:
    // the index that removed in this leave
    int return_index = q->head->index;
    // set up the new head by removing the nodes
    this->head = do_leave_pq(q->head,q->head->index, q->head->order);

    // return this index for this leave
    return return_index;
}