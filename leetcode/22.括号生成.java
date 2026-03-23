/*
 * @lc app=leetcode.cn id=22 lang=java
 *
 * [22] 括号生成
 */

// @lc code=start
import java.util.*;
class Solution {
    public List<String> generateParenthesis(int n) {
        List<String> res = new ArrayList<>();
        char[] cs = new char[2 * n];
        backtrack(n, res, cs, 0, 0, 0);
        return res;
    }

    void backtrack(int n, List<String> res, char[] cs, int index, int open, int close) {
        if (index == 2 * n) {
            res.add(new String(cs));
            return;
        }
        if (open < n) {
            cs[index] = '(';
            backtrack(n, res, cs, index + 1, open + 1, close);
        }
        if (close < open) {
            cs[index] = ')';
            backtrack(n, res, cs, index + 1, open, close + 1);
        }
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        List<Integer> testCases = Arrays.asList(3,1);
        for (Integer n : testCases) {
            var res = sol.generateParenthesis(n);
            for (String s : res) {
                System.out.print(s + ", ");
            }
            System.out.println();
        }
    }
}
// @lc code=end

