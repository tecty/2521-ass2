#ifndef PAGE_RANK_H
#define PAGE_RANK_H

#include "graph.h"
#include "hashTable.h"
#include "readData.h"



void PageRankW(graph g, double d, double diffPR,int maxIteration);

// if the given fp is NULL, then it would print to stdout
void show_pagerank(FILE *fp);
void show_weight();
void sort_by_pr();

#endif
