//
// Created by Kurna on 25-7-4.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct entry {
    void *key;
    void *value;
    struct entry *next;
} *Entry;

typedef struct hashMap *HashMap;

// 哈希函数类型
typedef int (*HashCode)(HashMap, void *key);

// 判等函数类型
typedef bool (*Equal)(void *key1, void *key2);

// 添加键函数类型
typedef void (*Put)(HashMap hashMap, void *key, void *value);

// 获取键对应值的函数类型
typedef void *(*Get)(HashMap hashMap, void *key);

// 删除键的函数类型
typedef bool (*Remove)(HashMap hashMap, void *key);

// 清空Map的函数类型
typedef void (*Clear)(HashMap hashMap);

// 判断键值是否存在的函数类型
typedef bool (*Exists)(HashMap hashMap, void *key);

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

static int defaultHashCode(HashMap hashMap, void *key);

static bool defaultEqual(void *key, void *key2);

static void defaultPut(HashMap hashMap, void *key, void *value);

static void *defaultGet(HashMap hashMap, void *key);

static bool defaultRemove(HashMap hashMap, void *key);

static bool defaultExists(HashMap hashMap, void *key);

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

int defaultHashCode(HashMap hashMap, void *key) {
    char *k = (char *) key;
    unsigned long h = 0;
    while (*k) {
        h = (h << 4) + *k++;
        unsigned long g = h & 0xF0000000L;
        if (g) {
            h ^= g >> 24;
        }
        h &= ~g;
    }
    return h % hashMap->listSize;
}

void defaultPut(HashMap hashMap, void *key, void *value) {
    if (hashMap->autoAssign && hashMap->size >= hashMap->listSize) {

        // 内存扩充至原来的两倍
        // *注: 扩充时考虑的是当前存储元素数量与存储空间的大小关系，而不是存储空间是否已经存满，
        // 例如: 存储空间为10，存入了10个键值对，但是全部冲突了，所以存储空间空着9个，其余的全部挂在一个上面，
        // 这样检索的时候和遍历查询没有什么区别了，可以简单这样理解，当我存入第11个键值对的时候一定会发生冲突，
        // 这是由哈希函数本身的特性(取模)决定的，冲突就会导致检索变慢，所以这时候扩充存储空间，对原有键值对进行
        // 再次散列，会把冲突的数据再次分散开，加快索引定位速度。
        resetHashMap(hashMap, hashMap->listSize * 2);
    }

    int index = hashMap->hashCode(hashMap, key);
    if (hashMap->list[index].key == NULL) {
        hashMap->size++;
        // 该地址为空时直接存储
        hashMap->list[index].key = key;
        hashMap->list[index].value = value;
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
        hashMap->list[index].next = entry;
        hashMap->size++;
    }
}

bool defaultEqual(void *key1, void *key2) {
    // 如果两个键的地址相同，直接认为相等
    if (key1 == key2) {
        return true;
    }

    // 如果其中一个键为NULL，另一个不为NULL，认为不相等
    if (key1 == NULL || key2 == NULL) {
        return false;
    }

    // 尝试将键转换为字符串进行比较
    char *str1 = (char *)key1;
    char *str2 = (char *)key2;

    // 逐个字符比较字符串内容
    while (*str1 && *str2 && (*str1 == *str2)) {
        str1++;
        str2++;
    }

    // 字符串完全相同或者两个键都到达结尾
    return (*str1 == '\0' && *str2 == '\0');
}

void * defaultGet(HashMap hashMap, void * key) {
    int index = hashMap->hashCode(hashMap, key);
    Entry entry = &hashMap->list[index];
    while (entry->key != NULL && !hashMap->equal(entry->key, key)) {
        entry = entry->next;
    }
    return entry->value;
}

bool defaultRemove(HashMap hashMap, void * key) {
    int index = hashMap->hashCode(hashMap, key);
    Entry entry = &hashMap->list[index];
    if (entry->key == NULL) {
        return false;
    }
    bool result = false;
    if (hashMap->equal(entry->key, key)) {
        hashMap->size--;
        if (entry->next != NULL) {
            Entry temp = entry->next;
            entry->key = temp->key;
            entry->value = temp->value;
            entry->next = temp->next;
            free(temp);
        }
        else {
            entry->key = entry->value = NULL;
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
    if (result && hashMap->autoAssign &&  hashMap->size < hashMap->listSize / 2) {
        resetHashMap(hashMap, hashMap->listSize / 2);
    }
    return result;
}

bool defaultExists(HashMap hashMap, void *key) {
    int index = hashMap->hashCode(hashMap, key);
    Entry entry = &hashMap->list[index];
    if (entry->key == NULL) {
        return false;
    }
    if (hashMap->equal(entry->key, key)) {
        return true;
    }
    if (entry->next != NULL) {
        do {
            if (hashMap->equal(entry->key, key)) {
                return true;
            }
            entry = entry->next;

        } while (entry != NULL);
        return false;
    }
    else {
        return false;
    }
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
    }
    // 释放存储空间
    free(hashMap->list);
    hashMap->list = NULL;
    hashMap->size = -1;
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
    }
    freeHashMapIterator(&iterator);

    // 清除原有键值对数据
    hashMap->size = 0;
    for (int i = 0; i < hashMap->listSize; i++) {
        Entry current = &hashMap->list[i];
        current->key = NULL;
        current->value = NULL;
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
        hashMap->list[i].key = NULL;
        hashMap->list[i].value = NULL;
        hashMap->list[i].next = NULL;
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
        p[i].key = p[i].value = p[i].next = NULL;
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
            if (entry->key != NULL) {
                iterator->count++;
                iterator->entry = entry;
                break;
            }
        }
    }
    return iterator;
}

void freeHashMapIterator(HashMapIterator * iterator) {
    free(*iterator);
    *iterator = NULL;
}

void test() {
    HashMap map = createHashMap(NULL, NULL);
    map->put(map, "asdfasdf", "asdfasdfds");
    map->put(map, "sasdasd", "asdfasdfds");
    map->put(map, "asdhfgh", "asdfasdfds");
    map->put(map, "4545", "asdfasdfds");
    map->put(map, "asdfaasdasdsdf", "asdfasdfds");
    map->put(map, "asdasg", "asdfasdfds");
    map->put(map, "qweqeqwe", "asdfasdfds");

    printf("key: asdfasdf, exists: %s\n", map->exists(map, "asdfasdf") ? "true" : "false");
    printf("4545: %s\n", (char *)map->get(map, "4545"));
    printf("remove 4545 %s\n", map->remove(map, "4545") ? "true" : "false");
    printf("remove 4545 %s\n", map->remove(map, "4545") ? "true" : "false");
    printf("key: 4545, exists: %s\n", map->exists(map, "4545") ? "true" : "false");

    HashMapIterator iterator = createHashMapIterator(map);
    while (hasNextHashMapIterator(iterator)) {
        iterator = nextHashMapIterator(iterator);
        printf("{ key: %s, key: %s, hashcode: %d }\n",
            (char *)iterator->entry->key, (char *)iterator->entry->value, iterator->hashCode);
    }
    map->clear(map);
    freeHashMapIterator(&iterator);
}