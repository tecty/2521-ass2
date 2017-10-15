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

//only search item in the tfIdf list (graph does not contain tfidf value)
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
    file_dict new = malloc(sizeof(struct file_dictionary));
    new->file_name = file;
    new->tfidf = tfidf;
    result = realloc(result, (length+1) * sizeof(file_dict));
    result[length] = new;
    length++;
}

void calculate_tfIdf(char *keyword, hash_table read, graph g){
    printf("===============================================\n");
    printf("Now scanning %s..\n", keyword);
    //register the new word into the dictionary
    double tf; //change when scanning each file
    double idf; //never change when searching for one word
    double tfidf; //change when scanning each file
    //find keyword in I_index
    hash_node this1 = find_node(read, keyword);
    //count how many pages after the keyword -> base of idf
    int idf_base = file_count(this1->val.l);
    printf("Total %d files have this word\n", idf_base);
    //get the nV of g -> numerator of idf
    int idf_num = g->nV;
    printf("The system has totally %d files\n", idf_num);
    //now calculate idf
    idf = (double)idf_num/idf_base;
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
            int pos = searchInResult(g->str_l[i]);
            //if exist
            if(pos!=-1){
                printf("The page already has the value %lf, add on value %lf\n", result[pos]->tfidf, tf*idf);
                //add on tfidf value
                result[pos]->tfidf += tf*idf;
            }
            else{
                printf("This page is not in the output list. Append this page with value %lf\n", tf*idf);
                //add the file into the list and assign tfidf value
                insert_dict(g->str_l[i], tf*idf);
            }
        }
        //else skip
        else{
            printf("The file does not have this word\n");
            continue;
        }
    }
}

void show_result(){
    if(result!=NULL){
        //mergesort(result); // not implemented yet
        for(int i = 0; i < length; i++)
            printf("%s  %lf\n", result[i]->file_name, result[i]->tfidf);
    }
}
