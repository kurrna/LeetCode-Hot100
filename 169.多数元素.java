/*
 * @lc app=leetcode.cn id=169 lang=java
 *
 * [169] 多数元素
 */

// @lc code=start
class Solution {
    public int majorityElement(int[] nums) {
        int n = nums.length;
        int candidate = 0;
        int count = 0;
        for (int i = 0; i < n; i++) {
            if (count == 0) {
                candidate = nums[i];
            }
            if (nums[i] == candidate) {
                count += 1;
            } else {
                count -= 1;
            }
        }
        return candidate;
    }

    public static void main(String[] args) {
        var sol = new Solution();
        int[] nums = new int[]{2, 2, 1, 1, 1, 2, 2};
        System.out.println(sol.majorityElement(nums));
    }
}
// @lc code=end

