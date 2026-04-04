/*
 * @lc app=leetcode.cn id=76 lang=java
 *
 * [76] 最小覆盖子串
 */

// @lc code=start

import java.util.*;

class Solution {
    public String minWindow(String s, String t) {
        int n = s.length(), l = 0, r = 0;
        Map<Character, Integer> need = new HashMap<>();
        for (char c : t.toCharArray()) {
            need.put(c, need.getOrDefault(c, 0) + 1);
        }
        // 剩余需要匹配的字符总次数
        int needCnt = t.length();
        int minLen = Integer.MAX_VALUE, start = 0;
        while (r < n) {
            char c = s.charAt(r);
            if (need.containsKey(c)) {
                if (need.get(c) > 0) {
                    needCnt--;
                }
                need.put(c, need.get(c) - 1);
            }
            while (needCnt == 0) {
                if (r - l + 1 < minLen) {
                    minLen = r - l + 1;
                    start = l;
                }
                char leftChar = s.charAt(l);
                if (need.containsKey(leftChar)) {
                    need.put(leftChar, need.get(leftChar) + 1);
                    if (need.get(leftChar) > 0) {
                        needCnt++;
                    }
                }
                l++;
            }
            r++;
        }
        return minLen == Integer.MAX_VALUE ? "" : s.substring(start, start + minLen);

    }

    public static void main(String[] args) {
        var sol = new Solution();
        List<String[]> testCases = new ArrayList<>(
            Arrays.asList(
                new String[] {"ADOBECODEBANC", "ABC"},
                new String[] {"a", "a"},
                new String[] {"a", "aa"}
            )
        );
        for (var testCase : testCases) {
            System.out.println(sol.minWindow(testCase[0], testCase[1]));
        }
    }
}
// @lc code=end

