//
// Created by Kurna on 2026/1/20.
//
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

class Solution {
public:
    int quickSelect(vector<int> &nums, int l, int k, int r) {
        if (l == r) return nums[k];
        int pivot = nums[l], i = l - 1, j = r + 1;
        while (i < j) {
            do i++; while (nums[i] < pivot);
            do j--; while (nums[j] > pivot);
            if (i < j) swap(nums[i], nums[j]);
        }
        if (k <= j) return quickSelect(nums, l, k, j);
        return quickSelect(nums, j + 1, k, r);
    }

    int findKthLargest(vector<int> &nums, int k) {
        int n = static_cast<int>(nums.size());
        return quickSelect(nums, 0, n - k, n - 1);
    }
};

class SolutionByHeap {
public:
    void heapify(vector<int> &nums, int i, int heapSize) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        if (left < heapSize && nums[left] > nums[largest]) {
            largest = left;
        }
        if (right < heapSize && nums[right] > nums[largest]) {
            largest = right;
        }
        if (largest != i) {
            swap(nums[i], nums[largest]);
            heapify(nums, largest, heapSize);
        }
    }

    void buildMaxHeap(vector<int> &nums) {
        int n = static_cast<int>(nums.size());
        for (int i = n / 2 - 1; i >= 0; --i) {
            heapify(nums, i, n);
        }
    }

    int findKthLargest(vector<int> &nums, int k) {
        int heapSize = static_cast<int>(nums.size());
        buildMaxHeap(nums);
        for (int i = 0; i < k - 1; ++i) {
            swap(nums[0], nums[heapSize - 1]);
            heapSize--;
            heapify(nums, 0, heapSize);
        }
        return nums[0];
    }
};

int main() {
    SolutionByHeap sol;
    vector<int> input = {3,2,1,5,6,4};
    int k = 2;
    int ans = sol.findKthLargest(input, k);
    cout << ans << endl;
    return 0;
}