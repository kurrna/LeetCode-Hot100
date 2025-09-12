//
// Created by Kurna on 25-9-11.
//
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> productExceptSelf(vector<int> &nums) {
        vector<int> ans;
        int R = 1;
        // 构造左前缀积数组
        for (int i = 0; i < nums.size(); ++i) {
            if (i == 0) ans.push_back(1);
            else ans.push_back(ans.back() * nums[i - 1]);
        }
        // 从右开始循环更新右前缀数组
        for (int i = nums.size() - 1; i >= 0; --i) {
            ans[i] = R * ans[i];
            R *= nums[i];
        }
        return ans;
    }
};

int main() {
    Solution sol;
    vector nums = {1, 2, 3, 4};
    auto ans = sol.productExceptSelf(nums);
    for (auto it = ans.begin(); it != ans.end(); ++it) {
        cout << *it;
        if (it != ans.end() - 1) {
            cout << ", ";
        }
    }
    return 0;
}
