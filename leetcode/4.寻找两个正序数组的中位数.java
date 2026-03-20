/*
 * @lc app=leetcode.cn id=4 lang=java
 *
 * [4] 寻找两个正序数组的中位数
 */
import java.util.*;
// @lc code=start
class Solution {
    public double findMedianSortedArrays(int[] nums1, int[] nums2) {
        int m = nums1.length, n = nums2.length;
        // 确保 nums1 是较短的数组
        if (m > n) {
            return findMedianSortedArrays(nums2, nums1);
        }
        int totalLeft = (m + n + 1) / 2;
        int left = 0, right = m - 1;
        while (left <= right) {
            int i = left + (right - left) / 2;
            int j = totalLeft - i;
            // 若 nums1[i] < nums2[j - 1]，说明 i 太小了，需要向右移动
            // 直到找到合适的 i，使得 nums1[i - 1] <= nums2[j] 且 nums2[j - 1] <= nums1[i]
            if (nums1[i] < nums2[j - 1]) {
                left = i + 1;
            } else {
                right = i - 1;
            }
        }
        int mid1 = left, mid2 = totalLeft - mid1;
        // nums1LeftMax、nums1RightMin、nums2LeftMax、nums2RightMin 分别表示 nums1 和 nums2 在分割线两侧的最大值和最小值
        int nums1LeftMax = (mid1 == 0) ? Integer.MIN_VALUE : nums1[mid1 - 1];
        int nums1RightMin = (mid1 == m) ? Integer.MAX_VALUE : nums1[mid1];
        int nums2LeftMax = (mid2 == 0) ? Integer.MIN_VALUE : nums2[mid2 - 1];
        int nums2RightMin = (mid2 == n) ? Integer.MAX_VALUE : nums2[mid2];
        if (((m + n) % 2) == 1) {
            return Math.max(nums1LeftMax, nums2LeftMax);
        } else {
            return (Math.max(nums1LeftMax, nums2LeftMax) + Math.min(nums1RightMin, nums2RightMin)) / 2.0;
        }
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        List<int[]> testCases = Arrays.asList(
            new int[]{1, 3}, new int[]{2},
            new int[]{1, 2}, new int[]{3, 4}
        );
        for (int i = 0; i < testCases.size(); i += 2) {
            int[] nums1 = testCases.get(i);
            int[] nums2 = testCases.get(i + 1);
            double median = sol.findMedianSortedArrays(nums1, nums2);
            System.out.printf("nums1: %s, nums2: %s, median: %.5f%n",
                Arrays.toString(nums1), Arrays.toString(nums2), median);
        }
    }
}
// @lc code=end

