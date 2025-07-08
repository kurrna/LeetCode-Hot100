//
// Created by Kurna on 25-7-8.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define max(a, b) (a > b ? a : b)

bool listEquals(int *a, int *b) {
    for (int i = 0; i < 129; i++) {
        if (a[i] != b[i]) return false;
    }
    return true;
}

int *findAnagrams(char *s, char *p, int *returnSize) {
    int len1 = strlen(s), len2 = strlen(p);
    *returnSize = 0;
    int *ret = malloc(max(0, len1 - len2 + 1) * sizeof(int));
    if (len1 < len2) return ret;
    int hash[27] = {0};
    int target[27] = {0};
    int left = 0, right = len2 - 1;
    for (int i = left; i <= right; i++) {
        hash[s[i] - 'a'] += 1;
    }
    for (int i = 0; i < len2; i++) {
        target[p[i] - 'a'] += 1;
    }
    while (right < len1) {
        if (memcmp(hash, target, sizeof(hash)) == 0) {
            ret[*returnSize] = left;
            (*returnSize)++;
        }
        hash[s[left] - 'a']--;
        left++, right++;
        if (right > len1 - 1) break;
        hash[s[right] - 'a']++;
    }
    return ret;
}

void test() {
    char s[] = "cbaebabacd";
    char p[] = "abc";
    int *returnSize = malloc(sizeof(int));
    if (returnSize == NULL) exit(1);
    int *ret = findAnagrams(s, p, returnSize);
    printf("[");
    for (int i = 0; i < *returnSize; i++) {
        for (int j = 0; j < strlen(p); j++) {
            printf("%c", s[ret[i] + j]);
        }
        if (i < *returnSize - 1) printf(",");
    }
    printf("]");
    free(returnSize);
    free(ret);
}
