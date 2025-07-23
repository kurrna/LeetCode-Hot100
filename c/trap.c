//
// Created by Kurna on 25-7-7.
//
#include <stdio.h>
#include <stdlib.h>

#define max(a, b) (a > b ? a : b)
#define min(a, b) (a < b ? a : b)

// 另外的方法：单调递减栈
int trap(int *height, int heightSize) {
    int ans = 0;
    int *actual = malloc(heightSize * sizeof(int));
    int left = 0, right = heightSize - 1;
    int tempHeight = 0;
    while (left <= right) {
        ans += (min(height[left], height[right]) - tempHeight) * (right - left + 1);
        tempHeight = min(height[left], height[right]);
        if (height[left] < height[right]) {
            int tempLeft = left;
            while (tempLeft <= right && height[left] >= height[tempLeft]) {
                actual[tempLeft] = min(height[tempLeft], tempHeight);
                tempLeft++;
            }
            left = tempLeft;
        } else if (height[left] > height[right]) {
            int tempRight = right;
            while (tempRight >= left && height[right] >= height[tempRight]) {
                actual[tempRight] = min(height[tempRight], tempHeight);
                tempRight--;
            }
            right = tempRight;
        } else {
            int tempLeft = left, tempRight = right;
            while (tempLeft <= right && height[left] >= height[tempLeft]) {
                actual[tempLeft] = min(height[tempLeft], tempHeight);
                tempLeft++;
            }
            while (tempRight >= tempLeft && height[right] >= height[tempRight]) {
                actual[tempRight] = min(height[tempRight], tempHeight);
                tempRight--;
            }
            left = tempLeft, right = tempRight;
        }
    }
    for (int i = 0; i < heightSize; i++) {
        ans -= actual[i];
    }
    free(actual);
    return ans;
}

void test() {
    int height[] = {5,5,1,7,1,1,5,2,7,6};
    int heightSize = sizeof(height) / sizeof(height[0]);
    printf("%d", trap(height, heightSize));
}
