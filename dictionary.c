#include "dictionary.h"

file_dict *result = NULL; //the list of pages which have tfidf != 0 for searching key words
int length = 0; //the length of the above list

int file_count(link files){
    ll_node p = files->head;
    int total = 0;
    while(p!=NULL){
        total++;
        p = p ->next;
    }
    return total;
}

int searchInResult(char *file){
    if(length == 0) return -1; //list is empty
    for(int index = 0; index < length; index++){
        if(strcmp(result[index]->file_name, file)==0){ //found
            return index;
        }
    }
    return -1; //not found
}

void insert_dict(char *file, double tfidf){
    result = realloc(result, (length+1) * sizeof(file_dict));
    result[length]->file_name = file;
    result[length]->tfidf = tfidf;
    length++;
}

void calculate_tfIdf(char *keyword, graph g){
    //register the new word into the dictionary
    double tf; //change when scanning each file
    double idf; //never change when searching for one word
    double tfidf; //change when scanning each file
    //find keyword in I_index
    hash_node slot = find_slot(I_index, keyword);
    //count how many pages after the keyword -> base of idf
    int idf_base = file_count(slot->val.l);
    //get the nV of g -> numerator of idf
    int idf_num = g->nV;
    //now calculate idf
    idf = (double)idf_num/idf_base;
    //scanning each file, for each file:
    for(int i = 0; i < nV; i++){
        //find if the word exists in the file
        hash_node slot_f = find_slot(g->content[i], keyword);
        //if the word exists in the file (frequency!=0)
        if(slot_f!=NULL){
            //get the frequency of the word
            int freq = slot_f->val.i;
            //get the total word count of the file
            int wc = g->wc[i];
            //now calculate tf
            tf = (double)freq/wc;
            //search if file is in the "result" list
            int pos = searchInResult(g->str_l[i]);
            //if exist
            if(pos!=-1)
                //add on tfidf value
                result[pos]->tfidf += tf/idf;
            else
                //add the file into the list and assign tfidf value
                insert_dict(g->str_l[i], tf/idf);
        }
        //else skip
        else  continue;
    }
}

void show_result(){

}