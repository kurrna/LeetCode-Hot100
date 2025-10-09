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

class SolutionByBinarySearch {
public:
    int lengthOfLIS(vector<int> &nums) {
        int len = 1, n = static_cast<int>(nums.size());
        if (n == 0) return 0;
        vector d(n + 1, 0);
        d[len] = nums[0];
        for (int i = 1; i < n; ++i) {
            if (nums[i] > d[len]) {
                d[++len] = nums[i];
            } else {
                int l = 1, r = len, pos = 0;
                while (l <= r) {
                    int mid = (l + r) >>1;
                    if (d[mid] < nums[i]) {
                        pos = mid;
                        l = mid + 1;
                    } else {
                        r = mid - 1;
                    }
                }
                d[pos + 1] = nums[i];
            }
        }
        return len;
    }
};

int main() {
    Solution sol;
    vector nums = {1,3,6,7,9,4,10,5,6};
    cout << sol.lengthOfLIS(nums) << endl;
    return 0;
}