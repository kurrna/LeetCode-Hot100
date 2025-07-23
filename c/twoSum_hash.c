//
// Created by Kurna on 25-7-4.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 条目结构，增加is_empty标志位
typedef struct entry {
    int key;
    int value;
    struct entry *next;
    bool is_empty;  // 标记槽位是否为空
} *Entry;

typedef struct hashMap *HashMap;

// 哈希函数类型
typedef int (*HashCode)(HashMap, int key);

// 判等函数类型
typedef bool (*Equal)(int key1, int key2);

// 添加键函数类型
typedef void (*Put)(HashMap hashMap, int key, int value);

// 获取键对应值的函数类型
typedef int (*Get)(HashMap hashMap, int key, bool *found);

// 删除键的函数类型
typedef bool (*Remove)(HashMap hashMap, int key);

// 清空Map的函数类型
typedef void (*Clear)(HashMap hashMap);

// 判断键值是否存在的函数类型
typedef bool (*Exists)(HashMap hashMap, int key);

typedef struct hashMap {
    int size; // 当前大小
    int listSize; // 有效空间大小
    HashCode hashCode; // 哈希函数
    Equal equal; // 判等函数
    Entry list; // 存储区域
    Put put; // 添加键的函数
    Get get; // 获取键对应值的函数
    Remove remove; // 删除键
    Clear clear; // 清空Map
    Exists exists; // 判断键是否存在
    bool autoAssign; // 设定是否根据当前数据量动态调整内存大小，默认开启
} *HashMap;

typedef struct hashMapIterator {
    Entry entry; // 迭代器当前指向
    int count; // 迭代次数
    int hashCode; // 键值对的哈希值
    HashMap hashMap;
} *HashMapIterator;

static int defaultHashCode(HashMap hashMap, int key);
static bool defaultEqual(int key1, int key2);
static void defaultPut(HashMap hashMap, int key, int value);
static int defaultGet(HashMap hashMap, int key, bool *found);
static bool defaultRemove(HashMap hashMap, int key);
static bool defaultExists(HashMap hashMap, int key);
static void defaultClear(HashMap hashMap);

HashMap createHashMap(HashCode hashCode, Equal equal);
static void resetHashMap(HashMap hashMap, int listSize);

// 创建哈希结构迭代器
HashMapIterator createHashMapIterator(HashMap hashMap);

// 迭代器是否有下一个
bool hasNextHashMapIterator(HashMapIterator iterator);

// 迭代到下一次
HashMapIterator nextHashMapIterator(HashMapIterator iterator);

// 释放迭代器内存
void freeHashMapIterator(HashMapIterator *iterator);

#define newEntry() NEW(struct entry)
#define newEntryList(length) (Entry)malloc(length * sizeof(struct entry))
#define newHashMap() NEW(struct hashMap)
#define newHashMapIterator() NEW(struct hashMapIterator)
#define NEW(type) \
    ({\
        type* _ptr = (type*)malloc(sizeof(type));\
        if (_ptr == NULL) {\
            perror("内存分配失败");\
            fprintf(stderr, "在分配类型 %s 的内存时发生错误\n", #type);\
            exit(EXIT_FAILURE);\
        }\
        _ptr;\
    })

int defaultHashCode(HashMap hashMap, int key) {
    // 改进的哈希函数，处理负数情况
    unsigned int unsigned_key = (unsigned int)key;
    return unsigned_key % hashMap->listSize;
}

void defaultPut(HashMap hashMap, int key, int value) {
    if (hashMap->autoAssign && hashMap->size >= hashMap->listSize * 0.75) {
        // 内存扩充至原来的两倍
        resetHashMap(hashMap, hashMap->listSize * 2);
    }

    int index = hashMap->hashCode(hashMap, key);

    // 使用is_empty标志判断空槽位
    if (hashMap->list[index].is_empty) {
        hashMap->size++;
        hashMap->list[index].key = key;
        hashMap->list[index].value = value;
        hashMap->list[index].is_empty = false;
    }
    else {
        Entry current = &hashMap->list[index];
        while (current != NULL) {
            if (hashMap->equal(key, current->key)) {
                // 对于键值已经存在的直接覆盖
                current->value = value;
                return;
            }
            current = current->next;
        };

        // 发生冲突则创建节点挂到相应位置的next上
        Entry entry = newEntry();
        entry->key = key;
        entry->value = value;
        entry->next = hashMap->list[index].next;
        entry->is_empty = false;  // 新节点默认为非空
        hashMap->list[index].next = entry;
        hashMap->size++;
    }
}

bool defaultEqual(int key1, int key2) {
    return key1 == key2;
}

int defaultGet(HashMap hashMap, int key, bool *found) {
    // 初始化found为false
    if (found != NULL) {
        *found = false;
    }

    int index = hashMap->hashCode(hashMap, key);
    Entry entry = &hashMap->list[index];

    // 如果槽位为空，直接返回
    if (entry->is_empty) {
        return 0;
    }

    // 遍历查找键值
    while (entry != NULL) {
        if (hashMap->equal(entry->key, key)) {
            if (found != NULL) {
                *found = true;
            }
            return entry->value;
        }
        entry = entry->next;
    }

    return 0;
}

bool defaultRemove(HashMap hashMap, int key) {
    int index = hashMap->hashCode(hashMap, key);
    Entry entry = &hashMap->list[index];

    // 如果槽位为空，直接返回false
    if (entry->is_empty) {
        return false;
    }

    bool result = false;
    if (hashMap->equal(entry->key, key)) {
        hashMap->size--;
        if (entry->next != NULL) {
            // 有后续节点，用后续节点覆盖当前节点
            Entry temp = entry->next;
            entry->key = temp->key;
            entry->value = temp->value;
            entry->next = temp->next;
            free(temp);
        }
        else {
            // 没有后续节点，标记为empty
            entry->is_empty = true;
        }
        result = true;
    }
    else {
        Entry p = entry;
        entry = entry->next;
        while (entry != NULL) {
            if (hashMap->equal(entry->key, key)) {
                hashMap->size--;
                p->next = entry->next;
                free(entry);
                result = true;
                break;
            }
            p = entry;
            entry = entry->next;
        };
    }

    // 如果空间占用不足一半，则释放多余内存
    if (result && hashMap->autoAssign && hashMap->size < hashMap->listSize / 2) {
        resetHashMap(hashMap, hashMap->listSize / 2);
    }
    return result;
}

bool defaultExists(HashMap hashMap, int key) {
    int index = hashMap->hashCode(hashMap, key);
    Entry entry = &hashMap->list[index];

    // 如果槽位为空，直接返回false
    if (entry->is_empty) {
        return false;
    }

    // 检查当前节点
    if (hashMap->equal(entry->key, key)) {
        return true;
    }

    // 检查后续节点
    if (entry->next != NULL) {
        do {
            entry = entry->next;
            if (entry == NULL) return false;
            if (hashMap->equal(entry->key, key)) {
                return true;
            }
        } while (1);
    }
    return false;
}

void defaultClear(HashMap hashMap) {
    for (int i = 0; i < hashMap->listSize; i++) {
        // 释放冲突值内存
        Entry entry = hashMap->list[i].next;
        while (entry != NULL) {
            Entry next = entry->next;
            free(entry);
            entry = next;
        }
        hashMap->list[i].next = NULL;
        hashMap->list[i].is_empty = true;  // 标记为空
    }
    // 释放存储空间
    free(hashMap->list);
    hashMap->list = NULL;
    hashMap->size = 0;
    hashMap->listSize = 0;
}

void resetHashMap(HashMap hashMap, int listSize) {
    if (listSize < 8) return;

    // 键值对临时存储空间
    Entry tempList = newEntryList(hashMap->size);

    HashMapIterator iterator = createHashMapIterator(hashMap);
    int length = hashMap->size;
    for (int index = 0; hasNextHashMapIterator(iterator); index++) {
        // 迭代取出所有键值对
        iterator = nextHashMapIterator(iterator);
        tempList[index].key = iterator->entry->key;
        tempList[index].value = iterator->entry->value;
        tempList[index].next = NULL;
        tempList[index].is_empty = false;
    }
    freeHashMapIterator(&iterator);

    // 清除原有键值对数据
    hashMap->size = 0;
    for (int i = 0; i < hashMap->listSize; i++) {
        Entry current = &hashMap->list[i];
        current->is_empty = true;
        if (current->next != NULL) {
            while (current->next != NULL) {
                Entry temp = current->next->next;
                free(current->next);
                current->next = temp;
            }
        }
    }

    // 更改内存大小
    hashMap->listSize = listSize;
    Entry relist = (Entry) realloc(hashMap->list, hashMap->listSize * sizeof(struct entry));
    if (relist != NULL) {
        hashMap->list = relist;
        relist = NULL;
    }

    // 初始化数据
    for (int i = 0; i < hashMap->listSize; i++) {
        hashMap->list[i].key = 0;
        hashMap->list[i].value = 0;
        hashMap->list[i].next = NULL;
        hashMap->list[i].is_empty = true;  // 新槽位标记为空
    }

    // 将所有键值对重新写入内存
    for (int i = 0; i < length; i++) {
        hashMap->put(hashMap, tempList[i].key, tempList[i].value);
    }
    free(tempList);
}

HashMap createHashMap(HashCode hashCode, Equal equal) {
    HashMap hashMap = newHashMap();
    hashMap->size = 0;
    hashMap->listSize = 8;
    hashMap->hashCode = hashCode == NULL ? defaultHashCode : hashCode;
    hashMap->equal = equal == NULL ? defaultEqual : equal;
    hashMap->exists = defaultExists;
    hashMap->get = defaultGet;
    hashMap->put = defaultPut;
    hashMap->remove = defaultRemove;
    hashMap->clear = defaultClear;
    hashMap->autoAssign = true;
    // 起始分配8个内存空间，溢出时会自动扩充
    hashMap->list = newEntryList(hashMap->listSize);
    Entry p = hashMap->list;
    for (int i = 0; i < hashMap->listSize; i++) {
        p[i].key = 0;
        p[i].value = 0;
        p[i].next = NULL;
        p[i].is_empty = true;  // 初始化为空槽位
    }
    return hashMap;
}

HashMapIterator createHashMapIterator(HashMap hashMap) {
    HashMapIterator iterator = newHashMapIterator();
    iterator->hashMap = hashMap;
    iterator->count = 0;
    iterator->hashCode = -1;
    iterator->entry = NULL;
    return iterator;
}

bool hasNextHashMapIterator(HashMapIterator iterator) {
    return iterator->count < iterator->hashMap->size ? true : false;
}

HashMapIterator nextHashMapIterator(HashMapIterator iterator) {
    if (hasNextHashMapIterator(iterator)) {
        if (iterator->entry != NULL && iterator->entry->next != NULL) {
            iterator->count++;
            iterator->entry = iterator->entry->next;
            return iterator;
        }
        while (++iterator->hashCode < iterator->hashMap->listSize) {
            Entry entry = &iterator->hashMap->list[iterator->hashCode];
            if (!entry->is_empty) {  // 检查槽位是否非空
                iterator->count++;
                iterator->entry = entry;
                break;
            }
        }
    }
    return iterator;
}

void freeHashMapIterator(HashMapIterator *iterator) {
    free(*iterator);
    *iterator = NULL;
}

int *twoSum(const int *nums, int numsSize, int target, int *returnSize) {
    int *ret = malloc(8);
    *returnSize = 0;
    HashMap hashMap = createHashMap(NULL, NULL);
    for (int i = 0; i < numsSize; i++) {
        int ans = target - *(nums + i);
        if (hashMap->exists(hashMap, ans)) {
            bool *found = 0;
            *returnSize = 2;
            *ret = hashMap->get(hashMap, ans, found);
            *(ret + 1) = i;
            return ret;
        }
        if (!hashMap->exists(hashMap, *(nums + i))) {
            hashMap->put(hashMap, *(nums + i), i);
        }
    }
    free(ret);
    return NULL;
}

void test() {
    int nums[] = {-1000,1000,-999,999,1001,-1001,2,-1002,1004,5,18,-1000000};
    int numsSize = 12;
    int target = 7;
    int *returnSize = malloc(4);
    if (returnSize == NULL) exit(1);
    int *ret = twoSum(nums, numsSize, target, returnSize);
    if (ret != NULL) {
        printf("[%d, %d]", *ret, *(ret + 1));
        free(ret);
    } else {
        printf("[]");
    }
    free(returnSize);
}
