/*
 * @lc app=leetcode.cn id=47 lang=java
 *
 * [47] 全排列 II
 */

// @lc code=start
import java.util.*;

class Solution {
    // public List<List<Integer>> permuteUnique(int[] nums) {
    // List<List<Integer>> res = new ArrayList<>();
    // List<Integer> path = new ArrayList<>();
    // for (int num : nums) {
    // path.add(num);
    // }
    // backtrack(res, path, 0);
    // return res;
    // }

    // private void backtrack(List<List<Integer>> res, List<Integer> path, int
    // index) {
    // int n = path.size();
    // if (index == n - 1) {
    // res.add(new ArrayList<>(path));
    // return;
    // }
    // for (int i = index; i < n; i++) {
    // if (path.subList(index, i).contains(path.get(i))) {
    // continue;
    // }
    // Collections.swap(path, index, i);
    // backtrack(res, path, index + 1);
    // Collections.swap(path, index, i);
    // }
    // }
    boolean[] visited;

    public List<List<Integer>> permuteUnique(int[] nums) {
        List<List<Integer>> ans = new ArrayList<List<Integer>>();
        List<Integer> perm = new ArrayList<Integer>();
        visited = new boolean[nums.length];
        Arrays.sort(nums);
        backtrack(nums, ans, 0, perm);
        return ans;
    }

    public void backtrack(int[] nums, List<List<Integer>> ans, int idx, List<Integer> perm) {
        if (idx == nums.length) {
            ans.add(new ArrayList<Integer>(perm));
            return;
        }
        for (int i = 0; i < nums.length; ++i) {
            if (visited[i] || (i > 0 && nums[i] == nums[i - 1] && !visited[i - 1])) {
                continue;
            }
            perm.add(nums[i]);
            visited[i] = true;
            backtrack(nums, ans, idx + 1, perm);
            visited[i] = false;
            perm.remove(idx);
        }
    }

    public static void main(String[] args) {
        var sol = new Solution();
        int[] nums = new int[] { 1, 1, 2 };
        var lists = sol.permuteUnique(nums);
        for (var list : lists) {
            list.stream().forEach(num -> System.out.print(num + " "));
            System.out.println();
        }
    }
}
// @lc code=end
