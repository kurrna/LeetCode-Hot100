#include <stdio.h>
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
    ht->table = (HashNode **) calloc(capacity, sizeof(HashNode *));
    return ht;
}

// 哈希函数 - 改进版，确保负数和正数有不同的哈希值
int hash(int key, int capacity) {
    unsigned int ukey;

    if (key < 0) {
        // 对于负数，使用特殊处理使其哈希值与对应的正数不同
        // 将符号位作为哈希计算的一部分
        ukey = (unsigned int)(-key) | 0x80000000; // 设置最高位为1表示负数
    } else {
        ukey = (unsigned int)key;
    }

    // 使用更优的哈希算法减少冲突
    ukey = ((ukey >> 16) ^ ukey) * 0x45d9f3b;
    ukey = ((ukey >> 16) ^ ukey) * 0x45d9f3b;
    ukey = (ukey >> 16) ^ ukey;

    return ukey % capacity;
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
    if (rootX == rootY) {
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
