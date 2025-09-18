//
// Created by Kurna on 25-9-17.
//
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> searchRange(vector<int> &nums, int target) {
        if (nums.empty()) return {-1, -1};
        vector<int> res;
        int l = 0, r = nums.size() - 1;
        while (l <= r) {
            int mid = (r - l) / 2 + l; // 向下取整，避免向上溢出
            if (nums[mid] < target) {
                l = mid + 1;
            } else if (nums[mid] > target) {
                r = mid - 1;
            } else {
                l = r = mid;
                while (l < nums.size() && nums[l] == target) {
                    l++;
                }
                while (r >= 0 && nums[r] == target) {
                    r--;
                }
            }
        }
        if (l == r + 1 && (l == nums.size() || nums[r+1] != target)) res.push_back(-1), res.push_back(-1);
        else res.push_back(r + 1), res.push_back(l - 1);
        return res;
    }
};

int main() {
    Solution sol;
    vector nums = {5, 7, 7, 8, 8, 10};
    int target = 8;
    auto res = sol.searchRange(nums, target);
    for (auto x: res) {
        cout << x << " ";
    }
    cout << endl;
    return 0;
}
