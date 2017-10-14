CC = clang
CFLAGS = -Wall -Werror -g -DDEBUG -Wextra
# just need to put all the depended .h files,
# it would look for the file.c with same name
DEPS = graph.h hashTable.h index_lib.h linklist_lib.h pr_lib.h readData.h


# for all the require programme name
#  invertedIndex
all: pagerank



%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

pagerank: pagerank.c graph.o hashTable.o pr_lib.o readData.o index_lib.o linklist_lib.o
	$(CC) -o $@ $^ $(CFLAGS)
# invertedIndex:
# 	$(CC) -o $@ $^ $(CFLAGS)

testReadData: testReadData.c graph.o hashTable.o pr_lib.o readData.o
	$(CC) -o $@ $^ $(CFLAGS)
testHashTable: test_hasht.c hashTable.o
	$(CC) -o $@ $^ $(CFLAGS)
testLL: test_linklist.c linklist_lib.o
	$(CC) -o $@ $^ $(CFLAGS)
searchPagerank:searchPagerank.c graph.o hashTable.o index_lib.o linklist_lib.o
	$(CC) -o $@ $^ $(CFLAGS)


clean:
	rm *.o *.gch pagerank invertedIndex -f
	rm testReadData testHashTable testLL
