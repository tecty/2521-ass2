#include "index_lib.h"

typedef struct file_dictionary{
    char *file_name;
    double tfidf;
} *file_dict;

int file_count(link);
int searchInResult(char *);
void insert_dict(char *, double);
void calculate_tfIdf(char *, hash_table, graph);
