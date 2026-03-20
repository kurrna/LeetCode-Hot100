/*
 * @lc app=leetcode.cn id=11 lang=java
 *
 * [11] 盛最多水的容器
 */

// @lc code=start

import java.util.*;

class Solution {
    public int maxArea(int[] height) {
        int n = height.length;
        int l = 0, r = n - 1;
        int curArea = (r - l) * Math.min(height[l], height[r]);
        int maxArea = curArea;
        while (r > l) {
            if (height[l] > height[r]) {
                r--;
            } else {
                l++;
            }
            curArea = (r - l) * Math.min(height[l], height[r]);
            maxArea = Math.max(maxArea, curArea);
        }
        return maxArea;
    }

    public static void main(String[] args) {
        Solution solution = new Solution();
        List<int[]> testCases = Arrays.asList(
            new int[]{1,8,6,2,5,4,8,3,7},
            new int[]{1,2,4,3}
        );
        for (int[] height : testCases) {
            System.out.println(solution.maxArea(height));
        }
    }
}
// @lc code=end

