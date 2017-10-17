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

void init_singleResult(hash_node new, graph g){
    new->val.result = malloc(g->nV*sizeof(double));
    for(int i = 0; i < g->nV; i++) new->val.result[i] = 0;
}

void calculate_tfIdf(char *keyword, hash_table read, graph g){
    //register the new word into the dictionary
    double tf; //change when scanning each file
    double idf; //never change when searching for one word
    //find keyword in read
    hash_node this1 = find_node(read, keyword);
    //count how many pages after the keyword -> base of idf
    int idf_base = this1->val.l->total;
    //get the nV of g -> numerator of idf
    int idf_num = g->nV;
    //now calculate idf
    idf = log10((double)idf_num/idf_base);
    //scanning each file, for each file:
    for(int i = 0; i < g->nV; i++){
        //find if the word exists in the file
        hash_node this2 = find_node(g->content[i], keyword);
        //if the word exists in the file (frequency!=0)
        if(this2!=NULL){
            //get the frequency of the word
            int freq = this2->val.i;
            //get the total word count of the file
            int wc = g->wc[i];
            //now calculate tf
            tf = (double)freq/wc;
            //search if file is in the "result" list
            hash_node insert = find_node(tfidf_result, keyword);
            if(insert==NULL){
                insert = insert_node(tfidf_result, keyword);
                init_singleResult(insert, g);
            }
            insert->val.result[i] += tf*idf;
            final->tfidfSum[i] += tf*idf;
        }
        else{
            continue;
        }
    }
}

void merge(summary final, summary temp, int lo, int hi, int hi_end){
    int lo_end = hi-1;
    int p = lo;
    while(lo<=lo_end && hi <= hi_end){
        if(final->tfidfSum[lo]>final->tfidfSum[hi]){
            temp->tfidfSum[p]=final->tfidfSum[lo];
            temp->fileName[p]=final->fileName[lo];
	        lo++;
        }
        else{
            temp->tfidfSum[p]=final->tfidfSum[hi];
            temp->fileName[p]=final->fileName[hi];
	        hi++;
        }
        p++;
    }
    while(lo<=lo_end){
        temp->tfidfSum[p]=final->tfidfSum[lo];
        temp->fileName[p]=final->fileName[lo];
    	p++;
    	lo++;
    }
    while(hi<=hi_end){
        temp->tfidfSum[p]=final->tfidfSum[hi];
        temp->fileName[p]=final->fileName[hi];
    	hi++;
    	p++;
    }
    for(int i = 0; i<=hi_end;i++){
        final->tfidfSum[i] = temp->tfidfSum[i];
	    final->fileName[i] = temp->fileName[i];
    }
}

void msort(summary final, summary temp, int lo, int hi){
    int mid;
    if(lo<hi){
        mid = (lo+hi)/2;
        msort(final, temp, lo, mid);
        msort(final, temp, mid+1, hi);
        merge(final, temp, lo, mid+1, hi);
    }
}

void mergesort(summary final, int size){
    summary temp = malloc(sizeof(struct tfidf_summary));
    temp->fileName = malloc(size*sizeof(char *));
    temp->tfidfSum = malloc(size*sizeof(double));
    assert(temp!=NULL);
    msort(final, temp, 0, size-1);
    free(temp->fileName);
    free(temp->tfidfSum);
    free(temp);
}

void show_result(graph g){ //sort is not implemented yet
    mergesort(final, g->nV);
    int count = 0;
    for (int i = 0; i < g->nV; i++) {
        if(count>=30) break;
        if(final->tfidfSum[i]!=0){
        printf("%s  %.6f\n", final->fileName[i], final->tfidfSum[i]);
            count++;
        }
    }
}
