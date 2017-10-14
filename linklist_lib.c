#include "linklist_lib.h"

ll_node new_node(char *val){
    // create the struct
    ll_node new = malloc(sizeof(struct linklist_t));

    // initialise it
    new->next = NULL;
    new->prev = NULL;
    new->val = strdup(val);

    // return it
    return new;
}

void push_l(link l, char *val){
    // create new node for this value
    ll_node new = new_node(val);
    // set up the link
    new->next = l->head;

    if (l->tail == NULL) {
        /* this is the first node in the list */
        l->tail = new;
    }
    else{
        // set up the link in the head
        l->head ->prev = new;
    }

    l->head = new;

}
void join_l(link l, char *val){
    // create new node for this value
    ll_node new = new_node(val);
    if (l->tail == NULL) {
        /* this is the first node  */
        l->tail = l->head = new;
    }
    else{
        // set up the link
        l->tail->next = new;
        new->prev = l->tail;
        l->tail = new;
    }

}
char *pop_l(link l){
    if (l->head == NULL) {
        /* couldn't pop */
        return NULL;
    }
    ll_node this = l->head;
    // keep the pointer to return
    char * return_val = this->val;

    // arrage the list
    l->head = l->head->next;
    if (l->head == NULL) {
        /* the last node is poped */
        l->tail = NULL;
    }
    else{
        // clean up the link
        l->head->prev = NULL;
    }

    // free the node
    free(this);

    return return_val;
}

char *leave_l(link l){
    if (l->tail == NULL) {
        /* couldn't leave */
        return NULL;
    }
    ll_node this = l->tail;
    // keep the pointer to return
    char * return_val = this->val;

    // arrage the list
    l->tail = l->tail->prev;
    if (l->tail == NULL) {
        /* the last node is poped */
        l->head = NULL;
    }
    else{
        // arrange the link
        l->tail->next = NULL;
    }
    // free the node
    free(this);

    return return_val;
}

void show_l(link l){
    printf("This list contain: " );
    for (ll_node this = l->head; this != NULL; this = this->next) {
        /* for all the node in the list */
        printf("-> %s", this->val );
    }
}

link init_link(){
    link new = malloc(sizeof(struct link_t));
    // initial the struct
    new->head = new->tail = NULL;
    // return the struct just create
    return new;
}
