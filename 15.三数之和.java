/*
 * @lc app=leetcode.cn id=15 lang=java
 *
 * [15] 三数之和
 */
import java.util.*;
// @lc code=start
class Solution {
    public List<List<Integer>> threeSum(int[] nums) {
        List<List<Integer>> res = new ArrayList<>();
        Arrays.sort(nums);
        for (int i = 0; i < nums.length - 2; i++) {
            if (i > 0 && nums[i] == nums[i-1]) continue;
            if (nums[i] > 0) break; // 剪枝优化
            int l = i + 1, r = nums.length - 1;
            while (l < r) {
                int cur = nums[i] + nums[l] + nums[r];
                if (cur > 0) {
                    r--;
                } else if (cur < 0) {
                    l++;
                } else {
                    res.add(List.of(nums[i], nums[l], nums[r]));
                    l++;
                    r--;
                    while (l < r && nums[l] == nums[l-1]) l++;
                    while (l < r && nums[r] == nums[r+1]) r--;
                }
            }
        }
        return res;
        
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        List<int[]> testCases = Arrays.asList(
            new int[]{2,-3,0,-2,-5,-5,-4,1,2,-2,2,0,2,-4,5,5,-10},
            new int[]{1,2,0,1,0,0,0,0},
            new int[]{-1,0,1,2,-1,-4},
            new int[]{0,1,1},
            new int[]{0,0,0,0}
        );
        for (int[] nums : testCases) {
            System.out.println(sol.threeSum(nums));
        }

    }
}
// @lc code=end

