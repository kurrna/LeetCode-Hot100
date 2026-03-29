/*
 * @lc app=leetcode.cn id=49 lang=java
 *
 * [49] 字母异位词分组
 */

// @lc code=start
import java.util.*;
class Solution {
    public List<List<String>> groupAnagrams(String[] strs) {
        Map<String, List<String>> map = new HashMap<>();
        for (String str : strs) {
            char[] chars = str.toCharArray();
            Arrays.sort(chars);
            String key = new String(chars);
            map.putIfAbsent(key, new ArrayList<>());
            map.get(key).add(str);
        }
        return new ArrayList<>(map.values());
    }

    public static void main(String[] args) {
        var sol = new Solution();
        String[] strs = {
            "eat",
            "tea",
            "tan",
            "ate",
            "nat",
            "bat"
        };
        var res = sol.groupAnagrams(strs);
        for (var group : res) {
            group.stream().forEach(str -> System.out.print(str + " "));
            System.out.println();
        }
    }
}
// @lc code=end

