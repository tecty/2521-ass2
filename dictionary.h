#include "inverted.h"
#include <math.h>

//prepared for mergesort
typedef struct tfidf_summary{
    char **fileName;
    double *tfidfSum;
} *summary;

hash_table init_tfidf();
void calculate_tfIdf(char *keyword, hash_table read, graph g);
void show_result();
