#include <stdbool.h>
#include <stdlib.h>

typedef struct HashNode {
    int key;
    int parent;
    int size;
    struct HashNode *next;
} HashNode;

typedef struct {
    int capacity;
    HashNode **table;
} HashTable;

HashTable *createHashTable(const int capacity) {
    HashTable *ht = (HashTable *) malloc(sizeof(HashTable));
    ht->capacity = capacity;
    ht->table = (HashNode **) malloc(capacity * sizeof(HashNode *));
    return ht;
}

int hash(int key, const int capacity) {
    if (key < 0) key = -key;
    return key % capacity;
}

void insert(const HashTable *ht, const int key) {
    const int index = hash(key, ht->capacity);
    HashNode *node = (HashNode *) malloc(sizeof(HashNode));
    node->key = key;
    node->parent = key;
    node->size = 1;
    node->next = ht->table[index];
    ht->table[index] = node;
}

HashNode *findKey(const HashTable *ht, const int key) {
    const int index = hash(key, ht->capacity);
    HashNode *current = ht->table[index];
    while (current != NULL) {
        if (current->key == key) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

int find(const HashTable *ht, const int x) {
    HashNode *node = findKey(ht, x);
    if (node == NULL) return -1;
    if (node->parent != x) {
        node->parent = find(ht, node->parent);
    }
    return node->parent;
}

void unionSets(HashTable *ht, int x, int y) {
    int rootX = find(ht, x);
    int rootY = find(ht, y);
    if (rootX == -1 || rootY == -1 || rootX == rootY) {
        return;
    }
    HashNode *nodeX = findKey(ht, rootX);
    HashNode *nodeY = findKey(ht, rootY);
    if (nodeX->size < nodeY->size) {
        nodeX->parent = rootY;
        nodeY->size += nodeX->size;
    } else {
        nodeY->parent = rootX;
        nodeX->size += nodeY->size;
    }
}

void freeHashTable(HashTable *ht) {
    if (ht == NULL) return;
    for (int i = 0; i < ht->capacity; i++) {
        HashNode *current = ht->table[i];
        while (current != NULL) {
            HashNode *temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(ht->table);
    free(ht);
}

typedef struct {
    int *parent;
    int *rank;
    int size;
} UnionFind;

int longestConsecutive(int *nums, int numsSize) {
    if (numsSize == 0) return 0;
    HashTable *ht = createHashTable(numsSize * 2);
    for (int i = 0; i < numsSize; i++) {
        if (findKey(ht, nums[i]) == NULL) {
            insert(ht, nums[i]);
        }
    }
    for (int i = 0; i < numsSize; i++) {
        int num = nums[i];
        if (findKey(ht, num + 1) != NULL) {
            unionSets(ht, num, num + 1);
        }
    }
    int maxLen = 0;
    for (int i = 0; i < numsSize; i++) {
        int root = find(ht, nums[i]);
        HashNode *node = findKey(ht, root);
        if (node->size > maxLen) {
            maxLen = node->size;
        }
    }
    freeHashTable(ht);
    return maxLen;
}

void test() {
    int nums[] = {0, -1};
    int numsSize = 2;
    printf("%d", longestConsecutive(nums, numsSize));
}
