//
// Created by Kurna on 25-9-25.
//
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

// dp[i] = max(dp[i - 1], dp[i - 2] + nums[i]);
class Solution {
public:
    int rob(vector<int> &nums) {
        vector<int> dp(nums.size() + 1);
        dp[0] = 0, dp[1] = nums[0];
        for (int i = 2; i <= nums.size(); ++i) {
            dp[i] = max(dp[i - 1], dp[i - 2] + nums[i - 1]);
        }
        return dp[static_cast<int>(nums.size())];
    }
};

int main() {
    Solution sol;
    vector nums = {1, 2, 3, 1};
    cout << sol.rob(nums) << endl;
}
