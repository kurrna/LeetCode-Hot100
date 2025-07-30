//
// Created by Kurna on 25-7-29.
//
#include <iostream>
#include <unordered_map>
#include <vector>

class Solution {
public:
    std::unordered_map<int, int> mp;

    int subarraySum(std::vector<int> &nums, int k) {
        int sum = 0, ret = 0;
        mp[0] = 1;
        for (int x: nums) {
            sum += x;
            if (mp.find(sum - k) != mp.end()) {
                ret += mp[sum - k];
            }
            mp[sum]++;
        }
        return ret;
    }
};

int main() {
    Solution sol;
    std::vector nums = {1, 1, 1};
    auto k = 2;
    std::cout << sol.subarraySum(nums, k) << std::endl;
}
