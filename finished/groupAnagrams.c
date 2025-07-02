#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct Word {
    short f[26];
} Word;

Word toWord(char *str) {
    char *p = str;
    Word ret;
    for (int i = 0; i < 26; i++) {
        ret.f[i] = 0;
    }
    while (*p != '\0') {
        ret.f[*p - 'a']++;
        p++;
    }
    return ret;
}

bool compare(Word word1, Word word2) {
    for (int i = 0; i < 26; i++) {
        if (word1.f[i] != word2.f[i]) return false;
    }
    return true;
}

char ***groupAnagrams(char **strs, int strsSize, int *returnSize,
                      int **returnColumnSizes) {
    Word *word = (Word *) malloc(strsSize * sizeof(Word));
    bool *visited = (bool *) malloc(strsSize * sizeof(bool));
    char ***ret = (char ***) malloc(strsSize * sizeof(char **));
    *returnColumnSizes = (int *) malloc(strsSize * sizeof(int));
    *returnSize = 0;
    for (int i = 0; i < strsSize; i++) {
        word[i] = toWord(*(strs + i));
        visited[i] = false;
    }
    for (int i = 0; i < strsSize; i++) {
        if (visited[i]) continue;
        int len = strlen(*(strs + i)) + 1;
        ret[*returnSize] = (char **) malloc(strsSize * sizeof(char *));
        ret[*returnSize][0] = (char *) malloc(len * sizeof(char));

        strcpy(ret[*returnSize][0], *(strs + i));
        (*returnColumnSizes)[*returnSize] = 1;

        int used = 1; // 记录实际使用的字符串数量
        for (int j = i + 1; j < strsSize; j++) {
            if (visited[j]) continue;
            if (compare(word[i], word[j])) {
                len = strlen(*(strs + j)) + 1;
                ret[*returnSize][(*returnColumnSizes)[*returnSize]] =
                        (char *) malloc(len * sizeof(char));
                strcpy(ret[*returnSize][(*returnColumnSizes)[*returnSize]],
                       *(strs + j));
                ((*returnColumnSizes)[*returnSize])++;
                visited[j] = true;
                used++;
            }
        }
        (*returnSize)++;
    }
    return ret;
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
