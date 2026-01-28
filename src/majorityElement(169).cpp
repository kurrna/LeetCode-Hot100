//
// Created by Kurna on 2026/1/28.
//
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int majorityElement(vector<int> &nums) {
        int n = static_cast<int>(nums.size());
        return majorityElementHelper(nums, 0, n-1);
    }

    int majorityElementHelper(vector<int> &nums, int l, int r) {
        if (l >= r) {
            return nums[l];
        }
        int mid = (r - l) / 2 + l;
        int left_maj = majorityElementHelper(nums, l, mid);
        int right_maj = majorityElementHelper(nums, mid + 1, r);
        if (left_maj == right_maj) return left_maj;
        int count_left = 0, count_right = 0;
        for (int i = l; i <= r; ++i) {
            if (nums[i] == left_maj) {
                ++count_left;
            } else if (nums[i] == right_maj) {
                ++count_right;
            }
        }
        return count_left > count_right ? left_maj : right_maj;
    }
};

class SolutionRandom {
public:
    int majorityElement(vector<int> &nums) {
        int n = static_cast<int>(nums.size());
        while (true) {
            int candidate = nums[rand() % n];
            int count = 0;
            for (int num : nums) {
                if (num == candidate) {
                    ++count;
                }
            }
            if (count > n / 2) {
                return candidate;
            }
        }
    }
};

// 投票算法
class SolutionBoyerMoore {
public:
    int majorityElement(vector<int> &nums) {
        int count = 0;
        int candidate = 0;
        for (int num : nums) {
            if (count == 0) {
                candidate = num;
            }
            count += (num == candidate) ? 1 : -1;
        }
        return candidate;
    }
};

int main() {
    Solution sol;
    vector<int> nums = {2, 2, 1, 1, 1, 2, 2};
    cout << sol.majorityElement(nums) << endl;
    return 0;
}