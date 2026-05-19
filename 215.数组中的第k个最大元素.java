/*
 * @lc app=leetcode.cn id=215 lang=java
 *
 * [215] 数组中的第K个最大元素
 */

// @lc code=start
import java.util.concurrent.*;;
class Solution {
    public int findKthLargest(int[] nums, int k) {
        return quickSelection(nums, 0, nums.length - 1, k - 1);
    }

    private int quickSelection(int[] nums, int l, int r, int k) {
        if (l == r) return nums[l];
        int pivotIdx = partition(nums, l, r);
        if (k == pivotIdx) {
            return nums[k];
        } else if (k < pivotIdx) {
            return quickSelection(nums, l, pivotIdx - 1, k);
        } else {
            return quickSelection(nums, pivotIdx + 1, r, k);
        }
    }

    private int partition(int[] nums, int l, int r) {
        // int randomIdx = ThreadLocalRandom.current().nextInt(l, r + 1);
        // swap(nums, randomIdx, r);
        int val = nums[r];
        int i = l;
        for (int j = l; j < r; j++) {
            if (nums[j] > val) {
                swap(nums, i, j);
                i++;
            }
        }
        swap(nums, i, r);
        return i;
    }

    private void swap(int[] nums, int i, int j) {
        int temp = nums[i];
        nums[i] = nums[j];
        nums[j] = temp;
    }

    public static void main(String[] args) {
        var sol = new Solution();
        int[] nums = {3, 2, 1, 5, 6, 4};
        System.out.println(sol.findKthLargest(nums, 2));
    }
}
// @lc code=end

