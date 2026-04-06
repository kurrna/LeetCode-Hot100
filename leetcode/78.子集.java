/*
 * @lc app=leetcode.cn id=78 lang=java
 *
 * [78] 子集
 */

// @lc code=start
import java.util.*;
class Solution {
    public List<List<Integer>> subsets(int[] nums) {
        List<List<Integer>> result = new ArrayList<>();
        List<Integer> path = new ArrayList<>();
        result.add(new ArrayList<>());
        backtrack(nums, result, path, 0);
        return result;
    }

    private void backtrack(int[] nums, List<List<Integer>> res, List<Integer> path, int index) {
        int n = nums.length;
        for (int i = index; i < n; i++) {
            path.add(nums[i]);
            res.add(new ArrayList<>(path));
            backtrack(nums, res, path, i + 1);
            path.removeLast();
        }
    }

    public static void main(String[] args) {
        var sol = new Solution();
        int[] nums = {1, 2, 3};
        var res = sol.subsets(nums);
        for (var list : res) {
            list.stream().forEach(num -> System.out.print(num + " "));
            System.out.println();
        }
    }
}
// @lc code=end

