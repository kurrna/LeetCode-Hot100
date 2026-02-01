//
// Created by Kurna on 2026/2/1.
//
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    void nextPermutation(vector<int> &nums) {
        int n = static_cast<int>(nums.size());
        int j = n - 2;
        // 从右到左找第一个顺序对(j, j+1)
        while (j >= 0 && nums[j] >= nums[j+1]) {
            j--;
        }
        // 在(j, n-1)中从右到左找第一个大于nums[j]的数nums[i]
        if (j >= 0) {
            int i = n - 1;
            while (i >= 0 && nums[i] <= nums[j]) {
                i--;
            }
            swap(nums[i], nums[j]);
        }
        reverse(nums.begin() + j + 1, nums.end());
    }
};

int main() {
    Solution sol;
    vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 12, 13, 11};
    sol.nextPermutation(nums);
    for (int num : nums) {
        cout << num << " ";
    }
    cout << endl;
    return 0;
}