/*
 * @lc app=leetcode.cn id=46 lang=java
 *
 * [46] 全排列
 */

// @lc code=start
import java.util.*;
class Solution {
    public List<List<Integer>> permute(int[] nums) {
        List<List<Integer>> res = new ArrayList<>();
        List<Integer> path = new ArrayList<>();
        for (int num : nums) {
            path.add(num);
        }
        backtrack(res, path, 0);
        return res;
    }

    private void backtrack(List<List<Integer>> res, List<Integer> path, int index) {
        int n = path.size();
        if (index == n - 1) {
            res.add(new ArrayList<>(path));
            return;
        }
        for (int i = index; i < n; i++) {
            Collections.swap(path, index, i);
            backtrack(res, path, index + 1);
            Collections.swap(path, index, i);
        }
    }

    public static void main(String[] args) {
        var sol = new Solution();
        int[] nums = new int[]{1, 2, 3};
        var lists = sol.permute(nums);
        for (var list : lists) {
            list.stream().forEach(num -> System.out.print(num + " "));
            System.out.println();
        }
    }
}
// @lc code=end

