CC = gcc
CFLAGS = -std=c11 -lm -Wall -Werror -g -Wextra -DDEBUG
# just need to put all the depended .h files,
# it would look for the file.c with same name
DEPS =r_aggr.h priority_q.h graph.h hashTable.h index_lib.h linklist_lib.h pr_lib.h readData.h dictionary.h


# for all the require programme name
#  index_libIndex
all: pagerank searchPagerank searchTfIdf scaledFootrule inverted



%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

pagerank: pagerank.c graph.o hashTable.o pr_lib.o readData.o index_lib.o linklist_lib.o
	$(CC) -o $@ $^ $(CFLAGS)
# index_libIndex:
# 	$(CC) -o $@ $^ $(CFLAGS)

testReadData: testReadData.c graph.o hashTable.o pr_lib.o readData.o
	$(CC) -o $@ $^ $(CFLAGS)
testHashTable: test_hasht.c hashTable.o
	$(CC) -o $@ $^ $(CFLAGS)
testLL: test_linklist.c linklist_lib.o
	$(CC) -o $@ $^ $(CFLAGS)
searchPagerank:searchPagerank.c graph.o hashTable.o pr_lib.o index_lib.o linklist_lib.o
	$(CC) -o $@ $^ $(CFLAGS)
searchTfIdf:searchTfIdf.c graph.o hashTable.o pr_lib.o index_lib.o linklist_lib.o dictionary.o readData.o
	$(CC) -o $@ $^ $(CFLAGS)
scaledFootrule:scaledFootrule.c graph.o hashTable.o index_lib.o linklist_lib.o r_aggr.o priority_q.o  pr_lib.o
	$(CC) -o $@ $^ $(CFLAGS)
inverted:inverted.c graph.o hashTable.o index_lib.o linklist_lib.o readData.o  pr_lib.o
	$(CC) -o $@ $^ $(CFLAGS)



clean:
	rm *.o *.gch pagerank index_libIndex searchPagerank -f
	rm -f testReadData testHashTable testLL scaledFootrule
	# may trigger some bug, even i fixed it..
	rm -f *.txt
