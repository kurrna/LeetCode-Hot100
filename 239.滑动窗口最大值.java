/*
 * @lc app=leetcode.cn id=239 lang=java
 *
 * [239] 滑动窗口最大值
 */

// @lc code=start
import java.util.*;
class Solution {
    public int[] maxSlidingWindow(int[] nums, int k) {
        int len = nums.length;
        int[] res = new int[len - k + 1];
        PriorityQueue<int[]> heap = new PriorityQueue<>((a, b) -> b[0] - a[0]);
        for (int j = 0; j < k; j++) {
            heap.offer(new int[]{nums[j], j});
        }
        res[0] = heap.peek()[0];
        for (int i = 0; i <= len - k; i++) {
            int right = i + k - 1;
            heap.offer(new int[]{nums[right], right});
            while (heap.peek()[1] < i) {
                heap.poll();
            }
            res[i] = heap.peek()[0];
        }
        return res;
    }

    public static void main(String[] args) {
        var sol = new Solution();
        int[] nums = {1, 3, -1, -3, 5, 3, 6, 7};
        int k = 3;
        var res = sol.maxSlidingWindow(nums, k);
        Arrays.stream(res).forEach(num -> System.out.print(num + " "));
    }
}
// @lc code=end

