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

int main() {
    Solution sol;
    vector<int> input = {3,2,1,5,6,4};
    int k = 2;
    int ans = sol.findKthLargest(input, k);
    cout << ans << endl;
    return 0;
}