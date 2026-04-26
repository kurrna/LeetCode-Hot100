/*
 * @lc app=leetcode.cn id=153 lang=java
 *
 * [153] 寻找旋转排序数组中的最小值
 */

// @lc code=start
class Solution {
    public int findMin(int[] nums) {
        int l = 0, r = nums.length - 1;
        int mid = l + (r - l) / 2;
        while (l < r) {
            if (r - l == 1) {
                return Math.min(nums[l], nums[r]);
            }
            mid = l + (r - l) / 2;
            if (nums[l] < nums[r]) {
                return nums[l];
            }
            if (nums[mid] > nums[r]) {
                l = mid + 1;
            } else if (nums[mid] < nums[l]) {
                r = mid;
            }
        }
        return nums[l];
    }

    public static void main(String[] args) {
        var sol = new Solution();
        int[] nums = {3, 1, 2};
        System.out.println(sol.findMin(nums));
    }
}
// @lc code=end

