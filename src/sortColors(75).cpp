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
        int low = 0, mid = 0, high = n - 1;
        while (low <= high) {
            if (nums[low] == 0) {
                swap(nums[low], nums[mid]);
                low++;
                mid++;
            } else if (nums[low] == 1) {
                low++;
            } else {
                swap(nums[low], nums[high]);
                high--;
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