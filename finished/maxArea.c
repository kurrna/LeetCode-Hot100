//
// Created by Kurna on 25-7-5.
//
#include <stdio.h>

#define min(a, b) (a < b ? a : b)

int maxArea(int* height, int heightSize) {
    int left = 0;
    int right = heightSize - 1;
    int ans = min(height[left], height[right]) * (right - left);
    while (left < right) {
        int temp = min(height[left], height[right]) * (right - left);
        if (temp >= ans) {
            ans = temp;
        }
        height[left] > height[right] ? right-- : left++;
    }
    return ans;
}

void test() {
    int height[] = {1, 8, 6, 2, 5, 4, 8, 3, 7};
    const int heightSize = 9;
    printf("%d", maxArea(height, heightSize));
}