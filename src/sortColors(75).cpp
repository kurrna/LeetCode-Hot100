//
// Created by Kurna on 2026/1/30.
//
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    void sortColors(vector<int> &nums) {
        int n = static_cast<int>(nums.size());
        int left = 0, right = n - 1, current = 0;
        while (current <= right) {
            if (nums[current] == 0) {
                swap(nums[current], nums[left]);
                left++;
                current++;
            } else if (nums[current] == 2) {
                swap(nums[current], nums[right]);
                right--;
            } else {
                current++;
            }
        }
    }
};

int main() {
    Solution solution;
    vector<int> nums = {2, 0, 2, 1, 1, 0};
    solution.sortColors(nums);
    for (int num : nums) {
        cout << num << " ";
    }
    cout << endl;
    return 0;
}