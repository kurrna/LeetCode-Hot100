/*
 * @lc app=leetcode.cn id=75 lang=java
 *
 * [75] 颜色分类
 */

// @lc code=start
import java.util.*;
class Solution {
    private void swap(int[] nums, int i, int j) {
        int temp = nums[i];
        nums[i] = nums[j];
        nums[j] = temp;
    }

    public void sortColors(int[] nums) {
        int l = 0, r = nums.length - 1;
        int i = 0;
        while (i <= r) {
            if (nums[i] == 0) {
                swap(nums, i, l);
                l++;
                i++;
            } else if (nums[i] == 2) {
                swap(nums, i, r);
                r--;
            } else {
                i++;
            }
        }
    }

    public static void main(String[] args) {
        var sol = new Solution();
        List<Integer[]> testCases = new ArrayList<>(
            Arrays.asList(
                new Integer[]{2, 0, 1},
                new Integer[]{2, 0, 2, 1, 1, 0}
            )
        );
        for (Integer[] testCase : testCases) {
            int[] nums = Arrays.stream(testCase).mapToInt(Integer::intValue).toArray();
            sol.sortColors(nums);
            Arrays.stream(nums).forEach(num -> System.out.print(num + " "));
            System.out.println();
        }
    }
}
// @lc code=end

