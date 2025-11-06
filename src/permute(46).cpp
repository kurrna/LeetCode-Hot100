//
// Created by Kurna on 2025/11/6.
//
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int> > permute(vector<int> &nums) {
        vector<vector<int> > res;
        sort(nums.begin(), nums.end());
        backtrack2(nums, 0, res);
        return res;
    }

    void backtrack(vector<int> &nums, int start, vector<vector<int> > &res) {
        int n = nums.size();
        if (start == n - 1) {
            res.push_back(nums);
            return;
        }
        vector<int> used;
        for (int i = start; i < n; ++i) {
            if (find(used.begin(), used.end(), nums[i]) != used.end()) {
                continue;
            }
            used.push_back(nums[i]);
            swap(nums[start], nums[i]);
            backtrack(nums, start + 1, res);
            swap(nums[start], nums[i]);
        }
    }

    void backtrack2(vector<int> &nums, int start, vector<vector<int> > &res) {
        int n = nums.size();
        if (start == n - 1) {
            res.push_back(nums);
            return;
        }
        for (int i = start; i < n; ++i) {
            swap(nums[start], nums[i]);
            backtrack2(nums, start + 1, res);
            swap(nums[start], nums[i]);
        }
    }
};

int main() {
    Solution sol;
    auto input = vector<int>{1, 2, 3};
    auto output = sol.permute(input);
    for (const auto &vec: output) {
        for (const auto &num: vec) {
            cout << num << " ";
        }
        cout << endl;
    }
    return 0;
}
