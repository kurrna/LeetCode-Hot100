/*
 * @lc app=leetcode.cn id=152 lang=java
 *
 * [152] 乘积最大子数组
 */

// @lc code=start
class Solution {
    public int maxProduct(int[] nums) {
        int max = Integer.MIN_VALUE;
        int[] dpMax = new int[nums.length];
        int[] dpMin = new int[nums.length];
        dpMax[0] = nums[0];
        dpMin[0] = nums[0];
        for (int i = 1; i < nums.length; i++) {
            dpMax[i] = Math.max(nums[i], Math.max(dpMax[i - 1] * nums[i], dpMin[i - 1] * nums[i]));
            dpMin[i] = Math.min(nums[i], Math.min(dpMax[i - 1] * nums[i], dpMin[i - 1] * nums[i]));
        }
        for (int i = 0; i < nums.length; i++) {
            max = Math.max(max, dpMax[i]);
        }
        return max;
    }

    public static void main(String[] args) {
        var sol = new Solution();
        int[] nums = {2, 3, -2, 4};
        System.out.println(sol.maxProduct(nums));
    }
}
// @lc code=end

