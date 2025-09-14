//
// Created by Kurna on 25-9-12.
//
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
public:
    int firstMissingPositive(vector<int> nums) {
        // 去除0和负数
        int n = nums.size();
        for (int &num : nums) {
            if (num <= 0) {
                num = n + 1;
            }
        }
        // 标记
        for (int i = 0; i < n; ++i) {
            if (abs(nums[i]) <= n) {
                if (nums[abs(nums[i]) -1] > 0)
                    nums[abs(nums[i]) -1] = -nums[abs(nums[i])-1];
            }
        }
        for (int i = 0; i < n; ++i) {
            if (nums[i] > 0) {
                return i + 1;
            }
        }
        return n + 1;
    }
};

int main(int argc, char *argv[]) {
    Solution sol;
    vector nums = {3,4,-1,1};
    auto ans = sol.firstMissingPositive(nums);
    cout << ans << endl;
    return 0;
}
