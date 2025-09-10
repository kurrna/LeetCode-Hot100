//
// Created by Kurna on 25-7-29.
//
#include <iostream>
#include <vector>
#include <deque>

class Solution {
public:
    // using STL
    // std::vector<int> maxSlidingWindow(std::vector<int> &nums, int k) {
    //     std::deque<int> deque;
    //     std::vector<int> ret;
    //     for (int i = 0; i < nums.size(); i++) {
    //         if (!deque.empty() && deque.front() < i - k + 1) {
    //             deque.pop_front();
    //         }
    //         while (!deque.empty() && nums[i] >= nums[deque.back()]) {
    //             deque.pop_back();
    //         }
    //         deque.push_back(i);
    //         if (i >= k - 1) {
    //             ret.push_back(nums[deque.front()]);
    //         }
    //     }
    //     return ret;
    // }
    std::vector<int> maxSlidingWindow(std::vector<int> &nums, int k) {
        std::vector<int> ans;
        static constexpr int MAXN = 1e5 + 1;
        int q[MAXN] = {0};
        int n = nums.size();
        int l = 0, r = -1;
        for (int i = 0; i < n; i++) {
            if (r >= l && q[l] < i - k + 1) l++;
            while (r >= l && nums[i] >= nums[q[r]]) r--;
            q[++r] = i;
            if (i >= k - 1) ans.push_back(nums[q[l]]);
        }
        return ans;
    }
};

int main() {
    Solution sol;
    std::vector arr = {1, 3, -1, -3, 5, 3, 6, 7};
    int k = 3;
    auto ans = sol.maxSlidingWindow(arr, k);
    for (auto it = ans.begin(); it != ans.end(); ++it) {
        std::cout << *it;
        if (std::next(it) != ans.end()) {
            std::cout << ", ";
        } else {
            std::cout << std::endl;
        }
    }
}
