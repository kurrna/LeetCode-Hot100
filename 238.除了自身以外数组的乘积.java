/*
 * @lc app=leetcode.cn id=238 lang=java
 *
 * [238] 除了自身以外数组的乘积
 */

// @lc code=start
import java.util.*;
class Solution {
    public int[] productExceptSelf(int[] nums) {
        int len = nums.length;
        int[] ans = new int[len];
        ans[0] = 1;
        int right = nums[len - 1];
        for (int i = 1; i < len; i++) {
            ans[i] = ans[i-1] * nums[i-1];
        }
        for (int j = len-2; j >= 0; j--) {
            ans[j] = ans[j] * right;
            right *= nums[j];
        }
        return ans;
    }

    public static void main(String[] args) {
        var sol = new Solution();
        int[] nums = {1, 2, 3, 4};
        var res = sol.productExceptSelf(nums);
        Arrays.stream(res).forEach(num -> System.out.print(num + " "));
    }
}
// @lc code=end

