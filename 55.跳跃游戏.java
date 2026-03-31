/*
 * @lc app=leetcode.cn id=55 lang=java
 *
 * [55] 跳跃游戏
 */

// @lc code=start
class Solution {
    public boolean canJump(int[] nums) {
        int maxPos = 0;
        int n = nums.length;
        for (int i = 0; i < n; i++) {
            if (i > maxPos) {
                break;
            }
            maxPos = Math.max(maxPos, i + nums[i]);
            if (maxPos >= n - 1) {
                return true;
            }
        }
        return false;
    }
}
// @lc code=end

