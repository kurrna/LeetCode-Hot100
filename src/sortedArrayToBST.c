//
// Created by Kurna on 25-7-15.
//
#include <stdio.h>
#include <stdlib.h>
#include <tree.h>

typedef struct _AVLNode {
    struct TreeNode *tn;
    int height;
} AVLNode;

int compare_int(const void *a, const void *b) {
    return *(int *) a - *(int *) b;
}

struct TreeNode *fn(int *nums, int i, int j) {
    if (i == j) {
        return createNode(nums[i]);
    }
    int mid = (i + j) >> 1;
    struct TreeNode *root = createNode(nums[mid]);
    if (i < mid) {
        root->left = fn(nums, i, mid - 1);
    }
    root->right = fn(nums, mid + 1, j);
    return root;
}

struct TreeNode *sortedArrayToBST(int *nums, int numsSize) {
    return fn(nums, 0, numsSize - 1);
}

void inOrderTraverse(struct TreeNode *root) {
    if (!root) return;
    inOrderTraverse(root->left);
    printf("%d,", root->val);
    inOrderTraverse(root->right);
}

void test() {
    int arr[] = {-10, -3, 0, 5, 9};
    int size = sizeof(arr) / sizeof(arr[0]);
    struct TreeNode *root = sortedArrayToBST(arr, size);
    int *ret = treeToArr(root);
    printf("[");
    for (int i = 0; i < size; i++) {
        printf("%d", ret[i]);
        if (i != sizeof(arr) / sizeof(arr[0]) - 1) printf(",");
    }
    printf("]");
    free(ret);
}
