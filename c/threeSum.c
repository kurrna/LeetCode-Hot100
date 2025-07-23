//
// Created by Kurna on 25-7-6.
//
// ReSharper disable CppLocalVariableMayBeConst
// ReSharper disable CppParameterMayBeConst
// ReSharper disable CppParameterMayBeConstPtrOrRef
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "hash.h"

int myHashCode(HashMap hashMap, void *key) {
    int *intKey = (int *) key;
    unsigned long h = *intKey;
    h ^= (h >> 16);
    h *= 0x85ebca6b;
    h ^= (h >> 13);
    h *= 0xc2b2ae35;
    h ^= (h >> 16);
    return h % hashMap->listSize;
}

bool myEqual(void *key1, void *key2) {
    if (key1 == key2) {
        return true;
    }
    if (key1 == NULL || key2 == NULL) {
        return false;
    }
    int *num1 = (int *) key1;
    int *num2 = (int *) key2;
    return *num1 == *num2;
}

int compare_int(const void *a, const void *b) {
    int val1 = *(const int *) a;
    int val2 = *(const int *) b;
    return val1 - val2;
}

int compare_intptr(const void *a, const void *b) {
    int *triplet1 = *(int **) a;
    int *triplet2 = *(int **) b;
    if (triplet1[0] != triplet2[0]) return triplet1[0] - triplet2[0];
    if (triplet1[1] != triplet2[1]) return triplet1[1] - triplet2[1];
    return triplet1[2] - triplet2[2]; // 最后比较第三个元素
}

int *getByKey(HashMap map, int i, int n, int *returnSize) {
    HashMapIterator iterator = createHashMapIterator(map);
    int *ret = malloc(map->size * sizeof(int));
    *returnSize = 0;
    for (int index = 0; hasNextHashMapIterator(iterator); index++) {
        iterator = nextHashMapIterator(iterator);
        /* target等于key、本身下标不等于val、*/
        if (n == *(int *) iterator->entry->key && *(int *) iterator->entry->value > i) {
            ret[*returnSize] = *(int *) iterator->entry->value;
            (*returnSize)++;
        }
    }
    return ret;
}

int **twoSum(int *nums, int numsSize, int target, int *returnSize) {
    HashMap map = createHashMap(myHashCode, myEqual);
    int **ret = calloc(numsSize * 2, sizeof(int *));
    *returnSize = 0;
    int *indexList = malloc(numsSize * sizeof(int));
    for (int i = 0; i < numsSize; i++) {
        indexList[i] = i;
        map->put(map, nums + i, indexList + i);
    }
    for (int i = 0; i < numsSize; i++) {
        int n = target - nums[i];
        int *getByKeySize = malloc(sizeof(int));
        if (getByKeySize == NULL) exit(1);
        int *getByKeyRet = getByKey(map, i, n, getByKeySize);
        for (int j = 0; j < *getByKeySize; j++) {
            ret[*returnSize + j] = malloc(2 * sizeof(int));
            ret[*returnSize + j][0] = nums[i];
            ret[*returnSize + j][1] = nums[getByKeyRet[j]];
        }
        *returnSize += *getByKeySize;
        free(getByKeySize);
        free(getByKeyRet);
    }
    free(indexList);
    return ret;
}

bool tripletEquals(int *tri1, int *tri2) {
    return tri1[0] == tri2[0] && tri1[1] == tri2[1] && tri1[2] == tri2[2];
}

// 超时，失败的解法
int **threeSum_hash(int *nums, int numsSize, int *returnSize, int **returnColumnSizes) {
    HashMap map = createHashMap(myHashCode, myEqual);
    int **ret = malloc(18000 * sizeof(int *));
    *returnSize = 0;
    *returnColumnSizes = malloc(18000 * sizeof(int));
    int *indexList = malloc(numsSize * sizeof(int));
    qsort(nums, numsSize, sizeof(int), compare_int);
    for (int i = 0; i < numsSize; i++) {
        indexList[i] = i;
        map->put(map, nums + i, indexList + i);
    }
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] > 0) break;
        if (i > 0 && nums[i] == nums[i - 1]) continue;
        int t = -nums[i];
        int *twoSumSize = malloc(sizeof(int));
        if (twoSumSize == NULL) exit(1);
        int **twoSumRet = twoSum(nums + i + 1, numsSize - i - 1, t, twoSumSize);
        for (int j = 0; j < *twoSumSize; j++) {
            (*returnColumnSizes)[*returnSize + j] = 3;
            ret[*returnSize + j] = malloc(3 * sizeof(int));
            ret[*returnSize + j][0] = nums[i];
            ret[*returnSize + j][1] = twoSumRet[j][0];
            ret[*returnSize + j][2] = twoSumRet[j][1];
            free(twoSumRet[j]);
        }
        *returnSize += *twoSumSize;
        free(twoSumSize);
        free(twoSumRet);
    }
    free(indexList);
    if (*returnSize > 0) {
        int j = 0;
        qsort(ret, *returnSize, sizeof(int *), compare_intptr);
        for (int i = 1; i < *returnSize; i++) {
            if (!tripletEquals(ret[j], ret[i])) {
                ret[++j] = ret[i];
                (*returnColumnSizes)[j] = (*returnColumnSizes)[i];
            } else {
                free(ret[i]);
            }
        }
        *returnSize = *returnSize == 0 ? 0 : j + 1;
    }
    *returnColumnSizes = realloc(*returnColumnSizes, *returnSize * sizeof(int));
    return ret;
}

int **threeSum(int *nums, int numsSize, int *returnSize, int **returnColumnSizes) {
    int **ret = malloc(18000 * sizeof(int *));
    *returnSize = 0;
    *returnColumnSizes = malloc(18000 * sizeof(int));
    if (numsSize < 3) {
        (*returnColumnSizes)[0] = 0;
        return ret;
    }
    qsort(nums, numsSize, sizeof(int), compare_int);
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] > 0) break;
        if (i > 0 && nums[i] == nums[i - 1]) continue;
        int left = i + 1, right = numsSize - 1;
        while (left < right) {
            int temp = nums[i] + nums[left] + nums[right];
            if (temp > 0) {
                right--;
            } else if (temp < 0) {
                left++;
            } else {
                (*returnColumnSizes)[*returnSize] = 3;
                ret[*returnSize] = malloc(3 * sizeof(int));
                ret[*returnSize][0] = nums[i];
                ret[*returnSize][1] = nums[left];
                ret[*returnSize][2] = nums[right];
                (*returnSize)++;
                // 去重
                int tempLeft = left, tempRight = right;
                while (tempLeft < numsSize && nums[left] == nums[tempLeft]) tempLeft++;
                while (tempRight > i && nums[right] == nums[tempRight]) tempRight--;
                left = tempLeft, right = tempRight;
            }
        }
    }
    return ret;
}

void test() {
    int nums[] = {
        0, 0, 0
    };
    int numsSize = sizeof(nums) / sizeof(nums[0]);
    int *returnSize = malloc(sizeof(int));
    int **returnColumnSizes = malloc(1000 * sizeof(int *));
    if (returnSize == NULL || returnColumnSizes == NULL) exit(1);
    int **ret = threeSum(nums, numsSize, returnSize, returnColumnSizes);
    printf("[");
    for (int i = 0; i < *returnSize; i++) {
        for (int j = 0; j < *(*returnColumnSizes + i); j++) {
            if (j == 0) printf("[");
            printf("%d", ret[i][j]);
            if (j == *(*returnColumnSizes + i) - 1) printf("]");
            else printf(",");
        }
        if (i != *returnSize - 1) printf(",");
    }
    printf("]");
    free(returnSize);
    free(returnColumnSizes);
    free(ret);
}

void test_twoSum() {
    // 单元测试完成
    int nums[] = {-1, 0, 1, 2, -1, -4};
    int numsSize = 6;
    int target = 0;
    int *returnSize = malloc(sizeof(int));
    if (returnSize == NULL) exit(1);
    int **ret = twoSum(nums, numsSize, target, returnSize);
    printf("[");
    for (int i = 0; i < *returnSize; i++) {
        printf("[");
        for (int j = 0; j < 2; j++) {
            printf("%d", ret[i][j]);
            if (j == 1) printf("]");
            else printf(",");
        }
        free(ret[i]);
        if (i != *returnSize - 1) printf(",");
    }
    printf("]");
    free(returnSize);
    free(ret);
}
