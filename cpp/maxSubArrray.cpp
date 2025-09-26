//
// Created by Kurna on 25-9-10.
//
#include <iostream>
#include <vector>

class Solution {
public:
    // Dynamic Programming
    int maxSubArray(std::vector<int> &nums) {
        if (nums.size() == 1) {
            return nums[0];
        }
        int ans = INT_MIN;
        int dp[nums.size()];
        for (int i = 0; i < nums.size(); i++) {
            if (i == 0) {
                dp[i] = nums[0];
            } else {
                dp[i] = std::max(dp[i - 1] + nums[i], nums[i]);
            }
            if (dp[i] > ans) {
                ans = dp[i];
            }
        }
        return ans;
    }

    // Divide & Conquer
    struct Status {
        int lSum; // 起点为left的最大子数组和
        int rSum; // 终点为right的最大子数组和
        int mSum; // 最大子段和
        int iSum; // 子段和
    };

    Status pushUp(Status l, Status r) {
        int iSum = l.iSum + r.iSum;
        int lSum = std::max(l.lSum, l.iSum + r.lSum);
        int rSum = std::max(r.rSum, r.iSum + l.rSum);
        int mSum = std::max(l.rSum + r.lSum, std::max(l.mSum, r.mSum));
        return Status{lSum, rSum, mSum, iSum};
    }

    Status get(std::vector<int> &v, int l, int r) {
        if (l == r) {
            return Status{v[l], v[l], v[l], v[l]};
        }
        int m = (l + r) >> 1;
        Status lSub = get(v, l, m);
        Status rSub = get(v, m + 1, r);
        return pushUp(lSub, rSub);
    }

    int maxSubArrayByDC(std::vector<int> &nums) {
        return get(nums, 0, nums.size() - 1).mSum;
    }
};

int main() {
    Solution sol;
    std::vector nums = {-2, -1, -3, 4, -1, 2, 1, -5, 4};
    std::cout << sol.maxSubArrayByDC(nums) << std::endl;
}
