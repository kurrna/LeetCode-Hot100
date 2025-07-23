#include <stdio.h>

void swap (int *nums , const int left, const int right) {
    const int temp = *(nums + left);
    *(nums + left) = *(nums + right);
    *(nums + right) = temp;
}

void moveZeroes(int* nums, int numsSize) {
    int left = 0, right = 0;
    while (right < numsSize) {
        if (nums[right] != 0) {
            swap(nums, left, right);
            left++;
        }
        right++;
    }
}

void test() {
    int nums[] = {0, 1, 0, 3, 12};
    int numsSize = 5;
    moveZeroes(nums, numsSize);
    printf("[");
    for (int i = 0; i < numsSize; i++) {
        printf("%d", *(nums + i));
        if (i == numsSize - 1) {
            printf("]");
        } else {
            printf(", ");
        }
    }
}