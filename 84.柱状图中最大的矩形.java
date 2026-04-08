/*
 * @lc app=leetcode.cn id=84 lang=java
 *
 * [84] 柱状图中最大的矩形
 */

// @lc code=start
import java.util.*;
class Solution {
    public int largestRectangleArea(int[] heights) {
        int n = heights.length;
        int maxArea = 0;
        Stack<Integer> stk = new Stack<>();
        for (int i = 0; i < n; i++) {
            while (!stk.isEmpty() && heights[stk.peek()] > heights[i]) {
                int height = heights[stk.pop()];
                int width = stk.isEmpty() ? i : i - stk.peek() - 1;
                maxArea = Math.max(maxArea, height * width);
            }
            stk.push(i);
        }
        // 处理栈中剩余的元素
        while (!stk.isEmpty()) {
            int height = heights[stk.pop()];
            int width = stk.isEmpty() ? n : n - stk.peek() - 1;
            maxArea = Math.max(maxArea, height * width);
        }
        return maxArea;
    }

    public static void main(String[] args) {
        var sol = new Solution();
        int[] heights = {2,1,5,6,2,3};
        int result = sol.largestRectangleArea(heights);
        System.out.println(result); // 输出: 10
    }
}
// @lc code=end

