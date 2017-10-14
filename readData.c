#include "readData.h"

void getSect1(graph g,FILE *fp,int src){
    char buff[1000];
    while (!feof(fp) && fscanf(fp, "%s",buff)){
        if (strcmp("#end", buff)==0) {
            /* push one more to end this session*/
             fscanf(fp, "%s",buff);
             break;
        }

        // resolve the dest number
        int dest = getIdByKey(g,buff);
        // inser the edge of this link
        insert_edge(g,src,dest);


    }
}

void word_generlise(char *word) {
    /* formalise the word to no comma, just lowwer case */
    int fast = 0, slow = 0;
    while(word[fast]!= '\0'){
        if (word[fast]>='A' && word[fast]<='Z') {
            /* change this to the lower case */
            word[slow] = tolower(word[fast]);
            slow ++;
        }
        else if (word[fast]>='a' && word[slow]<= 'z') {
            /* just increament the slow */
            slow ++;
        }
        // read next char
        fast ++;
    }

    // add null terminator for new string
    word[slow]= '\0';

}

void getSect2(graph g, FILE *fp, int src) {
    /* fuction to solve the part 2 information */
    char buff[1000];
    // shortcut to get this table
    hash_table t = g->content[src];
    // tmp val to record the node for the word it has read
    hash_node this_node;
    while (!feof(fp) && fscanf(fp, "%s",buff)){
        // push all the words into the hash table

        if (strcmp("#end", buff) == 0) {
            /* push one more to end this session*/
            fscanf(fp, "%s",buff);
            // generalise the table because it just a word count
            generalise_table(t);
            break;
        }

        // generalise the word
        word_generlise(buff);

        // search for this word
        this_node = find_node(t,buff);
        if (this_node == NULL) {
            /* current table don't have this word */
            this_node = insert_node(t, buff);
            // set the word count to 0
            this_node->val.i = 0;
            // increament the wordcount
            g->wc[src] ++;
        }

        // count one more for this node
        this_node->val.i ++;



    }


}


void getContent(graph g){
    // path for each pages
    char  path[100];
    for (int src = 0; src < g->nV; src++) {
        /* for all the pages */

        // construct the url
        sprintf(path, "%s%s.txt", PAGE_PATH, g->str_l[src]);

#ifdef DEBUG
        printf("open file: %s\n", path );
#endif

        FILE *fp = fopen(path, "r");
        // buffer for record each words in a page
        char  buff[1000];
        while (fp != NULL && !feof(fp) && fscanf(fp, "%s",buff)) {
            /* get all the buff */
            if (strcmp("#start", buff)==0){
                // start a session
                // read one more to get the session code;
                 fscanf(fp, "%s",buff);
                 if (strcmp("Section-1",buff)==0) {
                     /* read all the link */
                     getSect1(g, fp,src);
                 }
                 else if (strcmp("Section-2",buff) ==0) {
                     /* read all the link */
                     getSect2(g, fp,src);
                 }
                 else{
                    //  couldn't handle this section
                     assert(-1);
                 }
            }
        }
        // close the opened file
        fclose(fp);
    }
}

void readCollection(graph g) {
    /* read the information in the collection and re initialise the graph */

    char buff[1024];

    // construct the location of the collection
    sprintf(buff, "%scollection.txt",PAGE_PATH );


    // open the file
    FILE *fp = fopen(buff,"r");
    int max = 4;

    // initialised the array to store the string pointer
    g->str_l = malloc(max * sizeof(char * ));

    while (!feof(fp) && fscanf(fp,"%s", buff)) {
        /* scan all the url name */
        if (g->nV >= max) {
            /* the pointer array is not enought, resize the array */
            max *=2;
            g->str_l = realloc(g->str_l, max*sizeof(char *));
            assert(g->str_l != NULL);
        }
        // store the string into pointer array
        g->str_l[g->nV] = strdup(buff);
        g->nV ++;

    }

    // read to the end of the file
    fclose(fp);

    // resize the edge table;
    g->edges = realloc(g->edges,g->nV * sizeof(int *));
    assert(g->edges!= NULL);
    for (int i = 0; i < g->nV; i++) {
        /* malloc all the sub list in memory */
        g->edges[i]= realloc(g->edges[i],g->nV * sizeof(int *));
        assert(g->edges[i]!= NULL);
        /* reset the int value in edge list */
        for (int j = 0; j < g->nV; j++) {
            /* initialised all the edges */
            g->edges[i][j]= 0;
        }

    }
    // intilise all the hash_tables
    g->content = realloc(g->content,g->nV* sizeof(hash_table));
    for (int i = 0; i < g->nV; i++) {
        /* initialise tables */
        g ->content[i] = init_table();
    }
    //initialised all the inlink and outlink table
    g->wc= realloc(g->wc,g->nV * sizeof(int));
    g->inlink= realloc(g->inlink,g->nV * sizeof(int));
    g->outlink= realloc(g->outlink,g->nV * sizeof(int));
    for (int i = 0; i < g->nV; i++) {
        /* initila to all 0 table */
        g->wc[i] = g->inlink[i] = g->outlink[i] = 0;
    }

}


// provide a initialised graph, even it has nV = 0
void getCollection(graph g){
    // get the edges in the graph
    readCollection(g);

    // get the content by the page provide
    getContent(g);

}
