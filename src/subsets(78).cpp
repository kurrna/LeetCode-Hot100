//
// Created by Kurna on 2025/11/7.
//
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> subsets(vector<int> &nums) {
        vector<vector<int>> res;
        vector<int> path;
        backtrack(nums, 0, path, res);
        return res;
    }
    void backtrack(vector<int> &nums, int start, vector<int> &path, vector<vector<int>> &res) {
        res.push_back(path);
        for (int i = start; i < static_cast<int>(nums.size()); ++i) {
            path.push_back(nums[i]);
            backtrack(nums, i + 1, path, res);
            path.pop_back();
        }
    }
};

class SolutionByIteration {
    vector<int> t;
    vector<vector<int>> ans;
public:
    vector<vector<int>> subsets(vector<int> &nums) {
        int n = static_cast<int>(nums.size());
        for (int mask = 0; mask < (1 << n); ++mask) {
            t.clear();
            for (int i = 0; i < n; ++i) {
                if (mask & (1 << i)) {
                    t.push_back(nums[i]);
                }
            }
            ans.push_back(t);
        }
        return ans;
    }
};

int main() {
    Solution sol;
    vector<int> input = {1, 2, 3};
    auto ans = sol.subsets(input);
    for (auto &subset : ans) {
        cout << "[";
        for (int i = 0; i < static_cast<int>(subset.size()); ++i) {
            cout << subset[i];
            if (i < static_cast<int>(subset.size()) - 1) cout << ", ";
        }
        cout << "]" << endl;
    }
    return 0;
}