/*
 * @lc app=leetcode.cn id=45 lang=java
 *
 * [45] 跳跃游戏 II
 */

// @lc code=start
class Solution {
    public int jump(int[] nums) {
        int cnt = 0, maxPos = 0, end = 0;
        int n = nums.length;
        for (int i = 0; i < n; i++) {
            if (i > end) {
                cnt++;
                end = maxPos;
                if (end >= n - 1) {
                    break;
                }
            }
            maxPos = Math.max(maxPos, i + nums[i]);
        }
        return cnt;
    }

    public static void main(String[] args) {
        var sol = new Solution();
        int[] nums = new int[]{2, 3, 1, 1, 4};
        System.out.println(sol.jump(nums));
    }
}
// @lc code=end

