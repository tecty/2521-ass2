#include "index_lib.h"
// local var to record the invertedIndex
hash_table I_index;

// the link list for searching
link search_list = NULL;



hash_table init_index(){
    // record it to local variable
    I_index= init_table();

    return I_index;
}

// get the index calculated by the graph
// the order of vertex is the pagerank order
// The content in the graph is generaliseed
hash_table set_index(graph g){
    // initial the table is used
    init_index();

    // temporary record the node for each words
    hash_node this = NULL;

    hash_table page_name =init_table();

    for (int v = 0; v < g->nV; v++) {
        /* push all the page name and its' v into a hashTable */
        this = insert_node(page_name, g->str_l[v]);
        // set its' int into vertex id
        this->val.i = v;
    }

    // sort the table by page_name
    generalise_table(page_name);



    for (int t_id = 0; t_id < page_name->nItem; t_id++) {
        /* go throught all the vertex by sorted page name*/
        // store the calculated vertex_number
        int v = page_name->table[t_id]->val.i;


        // first generalise all the hashTable would be used
        generalise_table(g->content[v]);




        for (int i = 0; i < g->content[v]->nItem; i++) {
            /* go throught all the words */
            this = find_node(I_index, g->content[v]->table[i]->key);
            if (this == NULL) {
                /* try to insert this word in the table */
                this = insert_node(I_index,g->content[v]->table[i]->key);
                // initial the linklist
                this->val.l = init_link();
            }

            // record this links' name
            join_l(this->val.l,g->str_l[v]);
        }
    }
    // return the hashTable if needed
    return I_index;
}

// read the index from file
hash_table read_index(){
    // read the data from file
    FILE *fp = fopen("invertedIndex.txt","r");
    assert(fp != NULL);

    // initial the index to store the info
    init_index();

    // temporary char*
    char buff[1000];
    char word[100];

    // indent for the string
    int indent = 0;
    // to record the word's node (like an entry)
    hash_node this_node;



    while (!feof(fp) && fgets(buff,1000, fp)!= NULL ) {
        /* read by line */
        // reset the indent
        indent = 0;
        while (indent < (int)strlen(buff)  && sscanf(buff+indent,"%s",word )== 1) {
            /* read word by word */
            if (indent == 0) {
                /* this is the first word */
                this_node = find_node(I_index,word);

                // insert for this word
                this_node= insert_node(I_index, word);

                // initial the link
                this_node->val.l = init_link();

                // this node has initilised
                indent = 0;
                // first node have one more indent
                indent ++;
            }
            else{
                // urls, join the link
                join_l(this_node->val.l, word);
            }
            // record the indent
            indent += strlen(word)+1;
        }
    }


    // close the opened file
    fclose(fp);

    // return the hash table if needed
    return I_index;
}
void show_index(FILE *fp){

    if (fp == NULL) {
        /* print to stdout */
        fp = stdout;
    }
    // print to a given file
    // generalise_table would sort the table and reduce the NULL link
    generalise_table(I_index);


    for (int i = 0; i < I_index->max; i++) {
        /* search for all the node */

        if (I_index->table[i] != NULL) {
            /* show its key */
            fprintf(fp, "%s ",I_index->table[i]->key );
            for (ll_node this = I_index->table[i]->val.l->head; this!= NULL;
                 this= this->next) {
                // print for all the node
                fprintf(fp, " %s",this->val );
            }
            // print for a new line
            fprintf(fp, "\n");
        }
    }
}

void search_index(char *key){
    // filter list by list
    if (search_list == NULL) {
        /* the first keyword */
        // init the list to keep
        search_list = find_node(I_index, key)->val.l;
        if (search_list == NULL) {
            /* the first keyword don't point to any page */
            // let the search_list point to an empty list
            search_list = init_link();
        }
    }
    else{
        // not the first node, try to filter the list
        filter_l(search_list, find_node(I_index, key)->val.l);
    }
}

link get_result(){
    // return the final result of the list
    // read the sorted pagerank
    hash_table pr = read_pagerank(NULL);

    // reconstruct the search_list
    link result= init_link();

#ifdef DEBUG
    printf("\nThe pagerank read from file is\n" );
    show_table(pr);
    printf("\n");
#endif

    // rearrange the sult by the pagerank order
    for (int i = 0; i < pr->nItem; i++) {
        /* all the node in the hashTable, try to search it in the list*/
        for (ll_node node = search_list->head; node != NULL; node = node->next) {
            /* search for all the node in the list, find the this page name */
            if (strcmp(pr->table[i]->key, node->val)== 0) {
                /* found the key for this position */
                join_l(result,node->val);
            }
        }
    }


    return result;
}
