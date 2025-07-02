#include <stdbool.h>
#include <stdlib.h>

typedef struct HashNode {
	int key;
	int parent;
	int size;
	struct HashNode *next
} HashNode;

typedef struct {
	int capacity;
	HashNode **table;
} HashTable;

HashTable *createHashTable(int capacity) {
	HashTable *ht = (HashTable *)malloc(sizeof(HashTable));
	ht->capacity = capacity;
	ht->table = (HashNode **)calloc(capacity, sizeof(HashNode *));
	return ht;
}

int hashCode(int key, int capacity) {
	if (key < 0)
		key = -key;
	return key % capacity;
}

void insert(HashTable *ht, int key) {
    
}

typedef struct {
	int *parent;
	int *rank;
	int size;
} UnionFind;

int longestConsecutive(int *nums, int numsSize) {
	int a;
	int b;
}