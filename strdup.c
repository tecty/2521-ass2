#include "strdup.h"

char * strdup(const char *s){
    // just make the compailer happy
    int len = strlen(s);
    char *new = malloc(len*sizeof(char));
    strncat(new,s,len);
    return new;
}
