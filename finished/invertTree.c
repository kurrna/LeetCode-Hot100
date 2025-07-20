//
// Created by Kurna on 25-7-13.
//
#include <stdio.h>
#include <stdlib.h>
#include <../include/tree.h>

#define max(a, b) (a > b ? a : b)
#define min(a, b) (a < b ? a : b)
#define MAXSIZE 100

typedef struct {
    struct TreeNode **np;
    int head, tail;
    int size;
} Queue;

Queue *initQueue() {
    Queue *ret = malloc(sizeof(Queue));
    ret->np = malloc(sizeof(struct TreeNode *) * MAXSIZE);
    ret->head = 0, ret->tail = -1, ret->size = 0;
    return ret;
}

void enqueue(Queue *q, struct TreeNode *tn) {
    q->tail = (q->tail + 1) % MAXSIZE;
    q->np[q->tail] = tn;
    q->size++;
}

struct TreeNode *dequeue(Queue *q) {
    struct TreeNode *ret = q->np[q->head];
    q->head = (q->head + 1) % MAXSIZE;
    q->size--;
    return ret;
}

void freeQueue(Queue *q) {
    free(q->np);
    free(q);
}

struct TreeNode *invertTree(struct TreeNode *root) {
    if (root == NULL) return NULL;
    struct TreeNode *ret = createNode(root->val);
    ret->left = invertTree(root->right);
    ret->right = invertTree(root->left);
    return ret;
}

// 层序遍历
int **levelOrder(struct TreeNode *root, int *returnSize, int **returnColumnSizes) {
    *returnSize = 0;
    if (root == NULL) return NULL;
    int **ret = malloc(sizeof(int *) * MAXSIZE);
    *returnColumnSizes = calloc(MAXSIZE, sizeof(int));
    Queue *q = initQueue(), *q_next = initQueue();
    enqueue(q, root);
    struct TreeNode *temp;
    ret[0] = malloc(sizeof(int));
    while (q->size > 0) {
        while (q->size > 0) {
            temp = dequeue(q);
            ret[*returnSize][(*returnColumnSizes)[*returnSize]++] = temp->val;
            if (temp->left != NULL) {
                enqueue(q_next, temp->left);
            }
            if (temp->right != NULL) {
                enqueue(q_next, temp->right);
            }
        }
        ret[*returnSize] = realloc(ret[*returnSize],
                                   (*returnColumnSizes)[*returnSize] * sizeof(int));
        (*returnSize)++;
        ret[*returnSize] = malloc(min(pow(2, *returnSize), MAXSIZE) * sizeof(int));
        freeQueue(q);
        q = q_next;
        q_next = initQueue();
    }
    freeQueue(q), free(q_next);
    return ret;
}

void test() {
    int arr[] = {4, 2, 7, 1, 3, 6, 9};
    int size = sizeof(arr) / sizeof(arr[0]);
    struct TreeNode *root = arrToTree(arr, size, 0);
    struct TreeNode *ret = invertTree(root);
    int *returnSize = malloc(sizeof(int));
    int **returnColumnSizes = malloc(sizeof(int *));
    if (!returnSize || returnColumnSizes == NULL) exit(1);
    int **inverted = levelOrder(ret, returnSize, returnColumnSizes);
    printf("[");
    for (int i = 0; i < *returnSize; i++) {
        for (int j = 0; j < (*returnColumnSizes)[i]; j++) {
            if (j == 0) printf("[");
            printf("%d", inverted[i][j]);
            if (j == (*returnColumnSizes)[i] - 1) printf("]");
            else printf(",");
        }
        free(inverted[i]);
        if (i != *returnSize - 1) printf(",");
    }
    printf("]");
    if (*returnSize != 0) {
        free(*returnColumnSizes);
        free(returnColumnSizes);
        free(inverted);
    }
    free(returnSize);
    free(ret);
    free(root);
}
