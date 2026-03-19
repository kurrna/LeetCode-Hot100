/*
 * @lc app=leetcode.cn id=1 lang=java
 *
 * [1] 两数之和
 */

// @lc code=start
import java.util.HashMap;

class Solution {
    public int[] twoSum(int[] nums, int target) {
        HashMap<Integer, Integer> prefixMap = new HashMap<>();
        for (int i = 0; i < nums.length; i++ ) {
            int complement = target - nums[i];
            if (prefixMap.containsKey(complement)) {
                return new int[] { prefixMap.get(complement), i };
            } else {
                prefixMap.put(nums[i], i);
            }
        }
        return new int[] {-1, -1};
    }
}
// @lc code=end

