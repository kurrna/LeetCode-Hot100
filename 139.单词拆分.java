/*
 * @lc app=leetcode.cn id=139 lang=java
 *
 * [139] 单词拆分
 */

// @lc code=start
import java.util.*;

class Solution {
    public boolean wordBreak(String s, List<String> wordDict) {
        int n = s.length();
        boolean[] dp = new boolean[n+1];
        dp[0] = true;
        for (int i = 0; i < n; i++) {
            if (dp[i]) {
                for (var word : wordDict) {
                    int len = word.length();
                    if (i + len <= n && word.equals(s.substring(i, i + len))) {
                        dp[i + len] = true;
                        if (i + len == n) {
                            return true;
                        }
                    }
                }
            }
        }
        return dp[n];
    }

    public static void main(String[] args) {
        var sol = new Solution();
        String s = "leetcode";
        List<String> wordDict = new ArrayList<>();
        wordDict.add("leet");
        wordDict.add("code");
        System.out.println(sol.wordBreak(s, wordDict));
    }
}
// @lc code=end
