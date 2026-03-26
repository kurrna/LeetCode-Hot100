/*
 * @lc app=leetcode.cn id=40 lang=java
 *
 * [40] 组合总和 II
 */

// @lc code=start
import java.util.*;
class Solution {
    public List<List<Integer>> combinationSum2(int[] candidates, int target) {
        List<List<Integer>> res = new ArrayList<>();
        List<Integer> path = new ArrayList<>();
        Arrays.sort(candidates);
        backtrack(candidates, res, path, 0, -1, target);
        return res;
    }

    private void backtrack(int[] candidates, List<List<Integer>> res, List<Integer> path, int sum, int index, int target) {
        if (sum == target) {
            res.add(new ArrayList<>(path));
            return;
        }
        for (int i = index + 1; i < candidates.length; i++) {
            if (i > index + 1 && candidates[i] == candidates[i-1]) continue;
            int num = candidates[i];
            if (sum + num > target) break;
            path.add(num);
            backtrack(candidates, res, path, sum + num, i, target);
            path.removeLast();
        }
    }

    public static void main(String[] args) {
        var sol = new Solution();
        int[] candidates = new int[]{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
        var res = sol.combinationSum2(candidates, 30);
        for (var list : res) {
            list.stream().forEach(n -> System.out.print(n + " "));
            System.out.println();
        }
    }
}
// @lc code=end

