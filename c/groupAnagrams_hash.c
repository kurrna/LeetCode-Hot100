#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定义字符串最大长度
#define MAX_LEN 101

// 定义哈希表大小（质数，减少冲突）
#define HASH_SIZE 10007

//键节点
typedef struct Node
{
    //key是桶的标志
    char key[MAX_LEN];
    //group是用来存放当前key对应的字符串的
    //由于字符串可能有多个，需要用二级数组，对应二级指针
    char** group;
    //这个是group中字符串数量的统计
    int groupsize;
    //这个指针用于处理冲突，不同key却映射到了哈希表中的
    //同一个位置，那么就用分离链接法连在一起即可
    struct Node* next;
}Node;

//哈希表，存指向键的指针
Node* HashTable[HASH_SIZE];

//哈希函数
unsigned int Hash(const char* key)
{
    //数学证明这个数字更难发生冲突
    unsigned int hash = 5381;
    int c;
    while ((c = *key++))
    {
        hash = (((hash << 5) + hash) + c) % HASH_SIZE;
    }
    return hash;
}

//比较函数，用于将原字符串排序然后作为键
int compare(const void* a, const void* b)
{
    return *(char*)a - *(char*)b;
}

//将字符串分组到哈希表中
void Add(char* key, char* str)
{
    //传入的key是排序后的字符串，str是未排序的对应字符串

    //检查这个键是否存在
    int position = Hash(key);
    Node* node = HashTable[position];

    //得处理不同键哈希值相同的情况，用分离链接法

    //不等于NULL时说明存在，看看key是否一样
    //不一样就往深处走一步，遇空说明不存在
    while (node)
    {
        //若key没问题，向其数组里添加str
        if (strcmp(node->key,key) == 0)
        {
            node->group[node->groupsize] = str;
            node->groupsize++;
            return;
        }
        //有问题，则再走一步，继续循环，遇空则退出
        node = node->next;
    }

    //键不存在，那就插入这个键
    Node* newnode = (Node*)malloc(sizeof(Node));
    strcpy(newnode->key, key);
    newnode->group = (char**)malloc(sizeof(char*) * 1000);
    newnode->group[0] = str;
    newnode->groupsize = 1;
    newnode->next = HashTable[position];
    HashTable[position] = newnode;
}

//销毁哈希表
void Destroy()
{
    int i = 0;
    for(i = 0; i < HASH_SIZE; i++)
    {
        Node* node = HashTable[i];
        while (node)
        {
            Node* tmp = node->next;
            free(node->group);
            free(node);
            node = tmp;
        }
    }
}

//接口
char ***groupAnagrams(char **strs, int strsSize, int *returnSize, int **returnColumnSizes)
{
    //char***是需要返回的三维数组，char** strs是传入的二维数组，strsSize是这个数组的元素个数，returnSize是返回的二维数组的元素个数，returnColumnSizes是个指向一维数组的指针，用于返回二维数组的各行的长度。

    //先给全局哈希表中置NULL
    memset(HashTable, 0, sizeof(HashTable));

    //将strs中所有元素按Add函数的逻辑处理进入哈希表分组
    int i = 0;
    for (i = 0; i < strsSize; i++)
    {
        //摘取当前行
        char* str = strs[i];
        //将当前行排序结果给key保存
        char key[MAX_LEN];
        strcpy(key, str);
        qsort(key, strlen(key), sizeof(char), compare);
        //加入哈希表
        Add(key, str);
    }

    //利用哈希表中信息，完成任务

    //处理returnsize的问题，统计表中node(桶)的数量即可
    (*returnSize) = 0;
    for (i = 0; i < HASH_SIZE; i++)
    {
        Node* node = HashTable[i];
        while(node)
        {
            (*returnSize)++;
            node = node->next;
        }
    }

    //创建返回数组以及returnColumnSizes
    char*** result = (char***)malloc(sizeof(char**) * (*returnSize));
    *returnColumnSizes = (int*)malloc(sizeof(int) * (*returnSize));

    //提取哈希表信息放入对应位置
    int index = 0;
    for (i = 0; i < HASH_SIZE; i++)
    {
        Node* node = HashTable[i];
        while(node)
        {
            //把node的group中的二维数组放到三维数组result中的对应位置
            //为result的每个指针开辟指向的二维数组空间
            result[index] = (char**)malloc(sizeof(char*) * node->groupsize);
            int j = 0;
            for (j = 0; j < node->groupsize; j++) 
            {
                result[index][j] = node->group[j];
                //每个字符串都可以看作是一个一维数组，但是是个整体，不用额外开空间
            }
            //把node的groupsize放returnColumnSizes的对应位置
            (*returnColumnSizes)[index] = node->groupsize;
            index++;
            node = node->next;
        }
    }
    //销毁哈希表
    Destroy();
    return result;
}

// 测试用例函数
void test() {
    char *strs[] = {"ate", "eat", "bat", "tan", "nat", "ate"};
    int strsSize = 6;
    int returnSize;
    int *returnColumnSizes;
    char ***result =
            groupAnagrams(strs, strsSize, &returnSize, &returnColumnSizes);

    if (result) {
        printf("[");
        for (int i = 0; i < returnSize; i++) {
            printf("[");
            for (int j = 0; j < returnColumnSizes[i]; j++) {
                printf("\"%s\"", result[i][j]);
                if (j < returnColumnSizes[i] - 1) printf(",");
            }
            printf("]");
            if (i < returnSize - 1) printf(",");
        }
        printf("]\n");

        // 释放内存
        for (int i = 0; i < returnSize; i++) {
            for (int j = 0; j < returnColumnSizes[i]; j++) {
                free(result[i][j]);
            }
            free(result[i]);
        }
        free(result);
        free(returnColumnSizes);
    }
}