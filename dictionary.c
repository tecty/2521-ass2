#include "dictionary.h"

hash_table tfidf_result;
summary final;

hash_table init_tfidf(graph g){
    tfidf_result = init_table();
    final = malloc(sizeof(struct tfidf_summary));
    final->fileName = malloc(g->nV*sizeof(char *));
    final->tfidfSum = malloc(g->nV*sizeof(double));
    for(int i = 0; i<g->nV; i++){
        final->fileName[i] = g->str_l[i];
        final->tfidfSum[i] = 0;
    }
    return tfidf_result;
}

int file_count(link files){
    ll_node p = files->head;
    int total = 0;
    while(p!=NULL){
        total++;
        p = p ->next;
    }
    return total;
}

void init_singleResult(hash_node new, graph g){
    new->val.result = malloc(g->nV*sizeof(double));
    for(int i = 0; i < g->nV; i++) new->val.result[i] = 0;
}

void calculate_tfIdf(char *keyword, hash_table read, graph g){
    printf("===============================================\n");
    printf("Now scanning %s..\n", keyword);
    //register the new word into the dictionary
    double tf; //change when scanning each file
    double idf; //never change when searching for one word
    double tfidf; //change when scanning each file
    //find keyword in read
    hash_node this1 = find_node(read, keyword);
    //count how many pages after the keyword -> base of idf
    int idf_base = file_count(this1->val.l);
    printf("Total %d files have this word\n", idf_base);
    //get the nV of g -> numerator of idf
    int idf_num = g->nV;
    printf("The system has totally %d files\n", idf_num);
    //now calculate idf
    idf = log10((double)idf_num/idf_base);
    printf("The idf for the word %s is %lf\n", keyword, idf);
    //scanning each file, for each file:
    for(int i = 0; i < g->nV; i++){
        printf("----------------------------------------------\n");
        printf("Now scanning the file %s for word %s..\n", g->str_l[i], keyword);
        //find if the word exists in the file
        hash_node this2 = find_node(g->content[i], keyword);
        //if the word exists in the file (frequency!=0)
        if(this2!=NULL){
            printf("The file contains this word\n");
            //get the frequency of the word
            int freq = this2->val.i;
            printf("The word appears %d times\n", freq);
            //get the total word count of the file
            int wc = g->wc[i];
            printf("There are %d words in this file\n", wc);
            //now calculate tf
            tf = (double)freq/wc;
            printf("The tf of the word %s in the file %s is %lf\n", keyword, g->str_l[i], tf);
            //search if file is in the "result" list
            hash_node insert = find_node(tfidf_result, keyword);
            if(insert==NULL){
                printf("APPEND\n");
                insert = insert_node(tfidf_result, keyword);
                init_singleResult(insert, g);
            }
            insert->val.result[i] += tf*idf;
            final->tfidfSum[i] += tf*idf;
        }
        else{
            printf("The file does not have this word\n");
            continue;
        }
    }
}

void show_result(graph g){ //sort is not implemented yet
    printf("%d\n", g->nV);
    for (int i = 0; i < g->nV; i++) {
        printf("%s %lf\n", final->fileName[i], final->tfidfSum[i]);
    }
}
