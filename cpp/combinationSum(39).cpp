//
// Created by Kurna on 2025/11/8.
//
#include <bits/stdc++.h>

class Solution {
public:
    // 组合总和（允许重复使用同一个数），返回不重复的组合
    std::vector<std::vector<int>> combinationSum(std::vector<int> &candidates, int target) {
        std::vector<std::vector<int>> ans;
        std::vector<int> path;
        std::sort(candidates.begin(), candidates.end());
        // candidates.erase(std::unique(candidates.begin(), candidates.end()), candidates.end());
        std::function<void(int,int)> dfs = [&](int start, int remain) {
            if (remain == 0) { // 命中目标
                ans.push_back(path);
                return;
            }
            for (int i = start; i < static_cast<int>(candidates.size()); ++i) {
                int x = candidates[i];
                if (x > remain) break; // 剪枝：后面更大，无需继续
                path.push_back(x);
                dfs(i, remain - x);
                path.pop_back();
            }
        };
        dfs(0, target);
        return ans;
    }
};

int main() {
    Solution sol;
    std::vector<int> candidates = {2, 3, 6, 7};
    int target = 7;
    auto ans = sol.combinationSum(candidates, target);
    for (const auto &nums: ans) {
        for (int num: nums) std::cout << num << ' ';
        std::cout << '\n';
    }
    return 0;
}
