/*
 * @lc app=leetcode.cn id=215 lang=java
 *
 * [215] 数组中的第K个最大元素
 */

// @lc code=start
class Solution {
    public int findKthLargest(int[] nums, int k) {
        return quickSelection(nums, 0, nums.length - 1, k - 1);
    }

    private int quickSelection(int[] nums, int l, int r, int k) {
        if (l == r)
            return nums[l];
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
        var sol = new HeapSolution();
        int[] nums = { 2, -1, 0 };
        System.out.println(sol.findKthLargest(nums, 3));
    }
}
// @lc code=end

class HeapSolution {
    public int findKthLargest(int[] nums, int k) {
        int n = nums.length;
        if (n < k)
            return -1;
        var obj = new MaxHeap(n);
        for (int i = 0; i < n; i++) {
            obj.insert(nums[i]);
        }
        for (int j = 0; j < k - 1; j++) {
            obj.extractMax();
        }
        return obj.top();
    }

    private class MaxHeap {
        private int[] nums;
        private int size;

        private MaxHeap(int capacity) {
            nums = new int[capacity];
            size = 0;
        }

        private int parentIdx(int i) {
            return (i - 1) / 2;
        }

        private int leftChildIdx(int i) {
            return i * 2 + 1;
        }

        private int rightChildIdx(int i) {
            return i * 2 + 2;
        }

        private void insert(int num) {
            nums[size++] = num;
            int idx = size - 1;
            while (num > nums[parentIdx(idx)]) {
                if (idx == 0)
                    break;
                swap(idx, parentIdx(idx));
                idx = parentIdx(idx);
            }
        }

        private void extractMax() {
            nums[0] = nums[--size];
            heapifyDown(0);
        }

        private void heapifyDown(int i) {
            int val = nums[i];
            if (leftChildIdx(i) >= size) return;
            int leftVal = nums[leftChildIdx(i)];
            if (rightChildIdx(i) >= size) {
                if (leftVal > val) swap(i, leftChildIdx(i));
                return;
            }
            int rightVal = nums[rightChildIdx(i)];
            if (val > leftVal && val > rightVal) {
                return;
            }
            if (val < leftVal || val < rightVal) {
                if (leftVal < rightVal) {
                    swap(i, rightChildIdx(i));
                    heapifyDown(rightChildIdx(i));
                } else {
                    swap(i, leftChildIdx(i));
                    heapifyDown(leftChildIdx(i));
                }
            }
        }

        private int top() {
            return nums[0];
        }

        private void swap(int i, int j) {
            int temp = nums[i];
            nums[i] = nums[j];
            nums[j] = temp;
        }
    }
}