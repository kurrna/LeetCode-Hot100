/*
 * @lc app=leetcode.cn id=56 lang=java
 *
 * [56] 合并区间
 */

// @lc code=start
import java.util.*;
class Solution {
    public int[][] merge(int[][] intervals) {
        Arrays.sort(intervals, Comparator.comparingInt(a -> a[0]));
        if (intervals.length <= 1) {
            return intervals;
        }
        List<int[]> res = new ArrayList<>();
        int[] pre = intervals[0];
        for (int i = 1; i < intervals.length; i++) {
            int[] cur = intervals[i];
            if (pre[1] >= cur[0]) {
                pre[1] = Math.max(pre[1], cur[1]);
            } else {
                res.add(pre);
                pre = cur;
            }
        }
        res.add(pre);
        return res.toArray(new int[res.size()][]);
    }

    public static void main(String[] args) {
        var sol = new Solution();
        int[][] intervals = {
            {1, 3}, {2, 6}, {8, 10}, {15, 18}
        };
        var res = sol.merge(intervals);
        for (var list : res) {
            Arrays.stream(list).forEach(num -> System.out.print(num + " "));
            System.out.println();
        }
    }
}
// @lc code=end

