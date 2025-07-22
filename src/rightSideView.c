#include <tree.h>
#include <stdio.h>
#include <stdlib.h>

int *rightSideView(struct TreeNode *root, int *returnSize) {
    *returnSize = 0;
    if (root == NULL) return NULL;
    int *ret = malloc(sizeof(int) * 100);
    if (!ret) exit(1);
    struct TreeNode **queue = malloc(sizeof(struct TreeNode *) * 100);
    int head = 0, tail = -1, size = 0;
    tail = (tail + 1) % 99, size++;
    queue[tail] = root;
    while (size > 0) {
        int len = size;
        ret[(*returnSize)++] = queue[tail]->val;
        for (int i = 0; i < len; i ++) {
            struct TreeNode *tempNode = queue[head];
            head = (head + 1) % 99, size--;
            if (tempNode->left) {
                tail = (tail + 1) % 99, size++;
                queue[tail] = tempNode->left;
            }
            if (tempNode->right) {
                tail = (tail + 1) % 99, size++;
                queue[tail] = tempNode->right;
            }
        }
    }
    free(queue);
    return ret;
}

void test() {
    int arr[] = {1, 2, 3, -1, 5, -1, 4};
    int size = sizeof(arr) / sizeof(arr[0]);
    struct TreeNode *root = arrToTree(arr, size, 0);
    int *returnSize = malloc(sizeof(int));
    if (!returnSize) exit(1);
    int *ret = rightSideView(root, returnSize);
    printf("[");
    for (int i = 0; i < *returnSize; i++) {
        printf("%d", ret[i]);
        if (i != *returnSize - 1) printf(",");
    }
    printf("]");
    free(returnSize);
    free(ret);
}