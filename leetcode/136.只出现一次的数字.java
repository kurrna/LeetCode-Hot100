/*
 * @lc app=leetcode.cn id=136 lang=java
 *
 * [136] 只出现一次的数字
 */

// @lc code=start
class Solution {
    public int singleNumber(int[] nums) {
        int result = 0;
        for (int num : nums) {
            result ^= num;
        }
        return result;
    }

    public static void main(String[] args) {
        var sol = new Solution();
        int[] nums = {2, 2, 1};
        System.out.println(sol.singleNumber(nums));
    }
}
// @lc code=end

