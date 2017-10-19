#ifndef INDEX_LIB_H
#define INDEX_LIB_H

#include "readData.h"
#include "pr_lib.h"
#include "linklist_lib.h"
#include "stdlib.h"
#include <string.h>
#include "strdup.h"

#include <assert.h>

void show_index(FILE *fp);

// controller of the index
hash_table set_index(graph g);

hash_table read_index();
void search_index(char *key);
link get_result();
#endif
