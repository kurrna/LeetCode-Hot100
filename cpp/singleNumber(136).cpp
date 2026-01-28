//
// Created by Kurna on 2026/1/28.
//
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int singleNumber(vector<int> &nums) {
        int min_num = *min(nums.begin(), nums.end());
        int offset = 0;
        if (min_num < 0) {
            offset = -min_num;
        }
        vector<int> bit_count(32, 0);
        for (int num : nums) {
            int adjusted_num = num + offset;
            for (int i = 0; i < 32; ++i) {
                bit_count[i] += (adjusted_num >> i) & 1;
            }
        }
        int result = 0;
        for (int i = 0; i < 32; ++i) {
            if (bit_count[i] % 2 != 0) {
                result |= (1 << i);
            }
        }
        return result - offset;
    }
};

class Solution2 {
public:
    int singleNumber(vector<int> &nums) {
        int result = 0;
        for (int num : nums) {
            result ^= num;
        }
        return result;
    }
};

int main() {
    Solution sol;
    vector<int> nums = {4, 1, 2, 1, 2};
    cout << sol.singleNumber(nums) << endl; // Output: 4
    return 0;
}