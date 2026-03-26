/*
 * @lc app=leetcode.cn id=34 lang=java
 *
 * [34] 在排序数组中查找元素的第一个和最后一个位置
 */

// @lc code=start
class Solution {
    public int[] searchRange(int[] nums, int target) {
        return searchRange(nums, target, 0, nums.length - 1);
    }

    private int[] searchRange(int[] nums, int target, int left, int right) {
        int[] res = new int[] { -1, -1 };
        if (left > right) {
            return res;
        }
        int mid = left + (right - left) / 2;
        if (nums[mid] > target) {
            return searchRange(nums, target, left, mid - 1);
        } else if (nums[mid] < target) {
            return searchRange(nums, target, mid + 1, right);
        } else {
            if (mid == left || nums[mid - 1] != target) {
                res[0] = mid;
            } else {
                res[0] = searchRange(nums, target, left, mid - 1)[0];
            }
            if (mid == right || nums[mid + 1] != target) {
                res[1] = mid;
            } else {
                res[1] = searchRange(nums, target, mid + 1, right)[1];
            }
        }

        return res;
    }

    public static void main(String[] args) {
        var sol = new Solution();
        int[] nums = new int[] { 5, 7, 7, 8, 8, 10 };
        int[] res = sol.searchRange(nums, 8);
        System.out.println(res[0] + ", " + res[1]);
    }
}
// @lc code=end
