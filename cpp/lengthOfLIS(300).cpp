//
// Created by Kurna on 25-9-29.
//
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int lengthOfLIS(vector<int> &nums) {
        int res = INT_MIN;
        vector dp(nums.size(), 1);
        for (int i = 0; i < nums.size(); ++i) {
            for (int j = 0; j < i; ++j) {
                if (nums[i] > nums[j]) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
            res = max(res, dp[i]);
        }
        return res;
    }
};

int main() {
    Solution sol;
    vector nums = {1,3,6,7,9,4,10,5,6};
    cout << sol.lengthOfLIS(nums) << endl;
    return 0;
}