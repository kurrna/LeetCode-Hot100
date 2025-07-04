//
// Created by Kurna on 25-7-4.
//
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef HASH_H
#define HASH_H
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

void test();
#endif //HASH_H
