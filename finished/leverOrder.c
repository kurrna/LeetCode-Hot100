//
// Created by Kurna on 25-7-9.
//
#include <../include/tree.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define min(a, b) (a < b ? a : b)

typedef struct queueNode {
    struct TreeNode *t;
    int depth;
    struct queueNode *next;
} QueueNode;

QueueNode *createQueue(struct TreeNode *root) {
    QueueNode *queue = malloc(sizeof(QueueNode));
    queue->t = root;
    queue->depth = 1;
    queue->next = NULL;
    return queue;
}

int **levelOrder(struct TreeNode *root, int *returnSize, int **returnColumnSizes) {
    int **ret = malloc(2000 * sizeof(int *));
    *returnSize = 0;
    *returnColumnSizes = calloc(2000, sizeof(int));
    if (root == NULL) return ret;
    QueueNode *queue = createQueue(root);
    QueueNode *right = queue;
    ret[0] = malloc(sizeof(int));
    while (queue != NULL) {
        if (queue->t->left != NULL) {
            right->next = createQueue(queue->t->left);
            right->next->depth = queue->depth + 1;
            right = right->next;
        }
        if (queue->t->right != NULL) {
            right->next = createQueue(queue->t->right);
            right->next->depth = queue->depth + 1;
            right = right->next;
        }
        if (*returnSize != queue->depth - 1) {
            ret[*returnSize] = realloc(ret[*returnSize],
                                       (*returnColumnSizes)[*returnSize] * sizeof(int));
            (*returnSize)++;
            ret[*returnSize] = malloc(min(pow(2, *returnSize), 2000) * sizeof(int));
        }
        ret[*returnSize][(*returnColumnSizes)[*returnSize]] = queue->t->val;
        (*returnColumnSizes)[*returnSize]++;
        QueueNode *temp = queue;
        queue = queue->next;
        free(temp);
    }
    (*returnSize)++;
    return ret;
}

void test() {
    int arr[] = {3, 9, 20, -1, -1, 15, 7};
    int size = sizeof(arr) / sizeof(arr[0]);
    struct TreeNode *root = buildBinaryTree(arr, size, 0);
    int *returnSize = malloc(sizeof(int));
    int **returnColumnSizes = malloc(sizeof(int *));
    if (returnSize == NULL || returnColumnSizes == NULL) exit(1);
    int **ret = levelOrder(root, returnSize, returnColumnSizes);
    printf("[");
    for (int i = 0; i < *returnSize; i++) {
        for (int j = 0; j < (*returnColumnSizes)[i]; j++) {
            if (j == 0) printf("[");
            printf("%d", ret[i][j]);
            if (j == (*returnColumnSizes)[i] - 1) printf("]");
            else printf(",");
        }
        free(ret[i]);
        if (i != *returnSize - 1) printf(",");
    }
    printf("]");
    free(*returnColumnSizes);
    free(returnSize);
    free(returnColumnSizes);
    free(ret);
}
