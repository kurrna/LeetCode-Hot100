
/*
 * @lc app=leetcode.cn id=17 lang=java
 *
 * [17] 电话号码的字母组合
 */
import java.util.*;

// @lc code=start
class Solution {
    private static final String[] LETTERS = {
        "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"
    };

    public List<String> letterCombinations(String digits) {
        if (digits == null || digits.isEmpty()) return List.of();

        int n = digits.length();
        List<String> res = new ArrayList<>();
        char[] path = new char[n];
        backtrack(digits, 0, path, res);
        return res;
    }

    private void backtrack(String digits, int index, char[] path, List<String> res) {
        if (index == digits.length()) {
            res.add(new String(path));
            return;
        }

        char digit = digits.charAt(index);
        if (digit < '2' || digit > '9') {
            return;
        }

        String letters = LETTERS[digit - '2'];
        for (int i = 0; i < letters.length(); i++) {
            path[index] = letters.charAt(i);
            backtrack(digits, index + 1, path, res);
        }
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        List<String> testCases = Arrays.asList("23", "2");
        for (String testCase : testCases) {
            System.out.println("Input: " + testCase);
            List<String> result = sol.letterCombinations(testCase);
            System.out.println("Output: " + result);
        }
    }
}
// @lc code=end
