/*
 * @lc app=leetcode.cn id=3 lang=java
 *
 * [3] 无重复字符的最长子串
 */
import java.util.*;
// @lc code=start
class Solution {
    public int lengthOfLongestSubstring(String s) {
        Set<Character> charSet = new HashSet<>();
        int left = 0, maxLength = 0;
        for (int right = 0; right < s.length(); right++) {
            char currentChar = s.charAt(right);
            while (charSet.contains(currentChar)) {
                charSet.remove(s.charAt(left));
                left++;
            }
            charSet.add(currentChar);
            maxLength = Math.max(maxLength, right - left + 1);
        }
        return maxLength;
    }
    public static void main(String[] args) {
        Solution sol = new Solution();
        List<String[]> testCases = Arrays.asList(
            new String[]{"abcabcbb", "3"},
            new String[]{"bbbbb", "1"},
            new String[]{"pwwkew", "3"}
        );
        for (String[] testCase : testCases) {
            String input = testCase[0];
            int expected = Integer.parseInt(testCase[1]);
            int result = sol.lengthOfLongestSubstring(input);
            System.out.println("Input: " + input + ", Expected: " + expected + ", Result: " + result);
        }

    }
}
// @lc code=end

