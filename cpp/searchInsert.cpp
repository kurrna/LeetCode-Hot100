//
// Created by Kurna on 25-9-15.
//
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int searchInsert(vector<int> &nums, int target) {
        int l = 0, r = nums.size() - 1;
        while (l <= r) {
            int mid = (r - l) / 2 + l;
            if (nums[mid] > target) {
                r = mid - 1;
            } else if (nums[mid] < target) {
                l = mid + 1;
            } else {
 return mid;
            }
        }
        // nums.insert(nums.begin() + l, target);
        return l;
    }
};

int main() {
    vector nums = {1, 3, 5, 6};
    Solution sol;
    cout << sol.searchInsert(nums, 7) << endl;
    return 0;
}