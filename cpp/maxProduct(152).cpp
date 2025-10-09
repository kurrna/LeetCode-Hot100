//
// Created by Kurna on 25-10-2.
//
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int maxProduct(const vector<int> &nums) {
        if (nums.empty()) return 0;
        int curMax = nums[0], curMin = nums[0], res = nums[0];
        for (size_t i = 1; i < nums.size(); ++i) {
            int x = nums[i];
            if (x < 0) swap(curMax, curMin);
            curMax = max(x, curMax * x);
            curMin = min(x, curMin * x);
            res = max(res, curMax);
        }
        return res;
    }
};

int main() {
    Solution sol;
    vector nums = {2,3,-2,4};
    cout << sol.maxProduct(nums) << endl;
    return 0;
}