#include "linklist_lib.h"


int main() {
    /* code */

    link l = init_link();


    push_l(l,"a");
    push_l(l,"a");
    push_l(l,"a");
    push_l(l,"a");
    push_l(l,"a");

    printf("poped: %s\n",pop_l(l) );
    printf("poped: %s\n",pop_l(l) );
    printf("poped: %s\n",pop_l(l) );
    printf("poped: %s\n",pop_l(l) );

    printf("Leaved: %s\n",leave_l(l) );
    printf("Leaved: %s\n",leave_l(l) );
    printf("Leaved: %s\n",leave_l(l) );
    printf("Leaved: %s\n",leave_l(l) );
    printf("Leaved: %s\n",leave_l(l) );

    join_l(l,"a");
    join_l(l,"a");
    join_l(l,"a");
    join_l(l,"a");

    printf("Leaved: %s\n",leave_l(l) );
    printf("Leaved: %s\n",leave_l(l) );
    printf("Leaved: %s\n",leave_l(l) );
    printf("Leaved: %s\n",leave_l(l) );
    printf("Leaved: %s\n",leave_l(l) );
    printf("Leaved: %s\n",leave_l(l) );
    

    return 0;
}
