#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum = 0;
        for (auto &num : nums) {
            sum += num;
        }
        if ((sum & 1) == 1) return false;
        int target = sum >> 1;
        vector dp(target + 1, false);
        dp[0] = true;
        for (auto &num : nums) {
            for (int j = target; j >= num; --j) {
                dp[j] = dp[j] || dp[j - num];
            }
        }
        return dp[target];
    }
};

int main() {
    Solution sol;
    vector nums = {1, 5, 11, 5};
    cout << sol.canPartition(nums) << endl;
    return 0;
}