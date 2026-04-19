/*
 * @lc app=leetcode.cn id=131 lang=java
 *
 * [131] 分割回文串
 */

// @lc code=start
import java.util.*;

class Solution {
    boolean[][] dp;

    public List<List<String>> partition(String s) {
        List<List<String>> res = new ArrayList<>();
        List<String> path = new ArrayList<>();
        int n = s.length();
        dp = new boolean[n][n];
        for (int i = 0; i < n; ++i) {
            Arrays.fill(dp[i], true);
        }
        for (int i = n - 1; i >= 0; i--) {
            for (int j = i + 1; j < n; j++) {
                dp[i][j] = s.charAt(i) == s.charAt(j) && dp[i + 1][j - 1];
            }
        }
        dfs(res, path, s, 0);
        return res;
    }

    private void dfs(List<List<String>> res, List<String> path, String s, int idx) {
        if (idx == s.length()) {
            res.add(new ArrayList<>(path));
            return;
        }

        for (int i = idx; i < s.length(); i++) {
            if (dp[idx][i]) {
                path.add(s.substring(idx, i + 1));
                dfs(res, path, s, i + 1);
                path.removeLast();
            }
        }
    }

    private boolean isPalidrome(String s) {
        if (s.length() == 0) {
            return false;
        }
        int l = 0, r = s.length() - 1;
        while (l <= r) {
            if (s.charAt(l) != s.charAt(r)) {
                return false;
            }
            l++;
            r--;
        }
        return true;
    }

    public static void main(String[] args) {
        var sol = new Solution();
        String s = "ccb";
        var res = sol.partition(s);
        for (var strings : res) {
            strings.forEach(string -> System.out.print(string + " "));
            System.out.println();
        }
    }
}
// @lc code=end
