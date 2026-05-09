/*
 * @lc app=leetcode.cn id=189 lang=java
 *
 * [189] 轮转数组
 */

// @lc code=start
import java.util.*;
class Solution {
    public void rotate(int[] nums, int k) {
        int n = nums.length;
        if (n == 0 || n == 1) return;
        k %= n;
        if (k == 0) return;
        reverse(nums, 0, n - 1);
        reverse(nums, 0, k - 1);
        reverse(nums, k, n - 1);
    }

    private void reverse(int[] nums, int l, int r) {
        int mid = l + (r - l) / 2;
        for (int i = l; i <= mid; i++) {
            swap(nums, i, r - i + l);
        }
    }

    private void swap(int[] nums, int i, int j) {
        int temp = nums[i];
        nums[i] = nums[j];
        nums[j] = temp;
    }

    public static void main(String[] args) {
        var sol = new Solution();
        int[] nums = {1, 2};
        sol.rotate(nums, 2);
        Arrays.stream(nums).forEach(num -> System.out.print(num + " "));
    }
}
// @lc code=end

