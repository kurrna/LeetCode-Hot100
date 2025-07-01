#include <stdlib.h>

int *twoSum(int *nums, int numsSize, int target, int *returnSize) {
  int *ret = (int *)malloc(8);
  for (int i = 0; i < numsSize; i++) {
    for (int j = i + 1; j < numsSize; j++) {
      if (nums[i] + nums[j] == target) {
        *ret = i;
        *(ret + 1) = j;
        *returnSize = 2;
        return ret;
      }
    }
  }
  *returnSize = 0;
  return NULL;
}

void test() {
  int nums[] = {1, 2, 3, 4};
  int numsSize = 4;
  int target = 5;
  int *returnSize = malloc(sizeof(int));
  int *ret = twoSum(nums, numsSize, target, returnSize);
  for (int i = 0; i < *returnSize; i++) {
    printf("%d ", ret[i]);
  }
}