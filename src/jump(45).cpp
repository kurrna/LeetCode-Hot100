//
// Created by Kurna on 25-9-22.
//
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int jump(vector<int> &nums) {
        if (nums.size() == 1) return 0;
        int maxPos = 0, end = 0;
        int count = 0;

        for (int i = 0; i < nums.size() - 1; ++i) {
            if (maxPos >= i) {
                maxPos = max(maxPos, i + nums[i]);
                if (i == end) {
                    end = maxPos;
                    ++count;
                }
            }
        }

        return count;
    }
};

int main() {
    Solution sol;
    vector nums = {2, 3, 1, 1, 4};
    cout << sol.jump(nums) << endl;
    return 0;
}
