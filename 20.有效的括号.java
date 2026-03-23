/*
 * @lc app=leetcode.cn id=20 lang=java
 *
 * [20] 有效的括号
 */

// @lc code=start
import java.util.*;

class Solution {
    public boolean isValid1(String s) {
        if (s.length() % 2 != 0) {
            return false;
        }
        Stack<Character> stack = new Stack<>();
        Map<Character, Character> pairs = new HashMap<>();
        pairs.put(')', '(');
        pairs.put('}', '{');
        pairs.put(']', '[');

        for (char c : s.toCharArray()) {
            if (pairs.containsKey(c)) {
                if (stack.isEmpty() || stack.pop() != pairs.get(c)) {
                    return false;
                }
            } else {
                stack.push(c);
            }
        }

        return stack.isEmpty();

    }

    public boolean isValid(String s) {
        if (s.length() % 2 != 0) {
            return false;
        }
        int top = 0;
        char[] cs = s.toCharArray();
        for (char c : cs) {
            if (c == '(') {
                // 相当于压栈
                cs[top] = ')';
                top++;
            } else if (c == '{') {
                // 相当于压栈
                cs[top] = '}';
                top++;
            } else if (c == '[') {
                // 相当于压栈
                cs[top] = ']';
                top++;
            } else if (top == 0 || cs[--top] != c) {
                return false;
            }
        }
        return top == 0;
    }

    public static void main(String[] args) {
        Solution solution = new Solution();
        List<String> testCases = Arrays.asList(
            "{[]}",
            "()",
            "()[]{}",
            "(]",
            "([)]"
        );
        for (String testCase : testCases) {
            boolean result = solution.isValid(testCase);
            System.out.println("Input: " + testCase + " -> Output: " + result);
        }
    }
}
// @lc code=end
