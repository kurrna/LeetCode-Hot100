/*
 * @lc app=leetcode.cn id=5 lang=java
 *
 * [5] 最长回文子串
 */

// @lc code=start

import java.util.*;

class Solution {
    public String longestPalindrome(String s) {
        int n = s.length();
        boolean[] dp = new boolean[n];
        String result = "";

        for (int i = n - 1; i >= 0; i--) {
            for (int j = n - 1; j >= i; j--) {
                 // 此处的 dp[j - 1] 是上一次循环中 dp[j - 1] 的值，即 dp[i + 1][j - 1]
                dp[j] = s.charAt(i) == s.charAt(j) && (j - i < 3 || dp[j - 1]);
                if (dp[j] && j - i + 1 > result.length()) {
                    result = s.substring(i, j + 1);
                }
            }
        }

        return result;
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        List<String> testCases = Arrays.asList(
            "babad",
            "cbbd"
        );
        for (String s : testCases) {
            String ans = sol.longestPalindrome(s);
            System.out.println("intput: "+ s + " output: " + ans);
        }
    }
}
// @lc code=end

