//
// Created by Kurna on 25-9-22.
//
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    bool canJump(vector<int> &nums) {
        int max = 0;
        for (int i = 0; i < nums.size(); ++i) {
            if (max < i) return false;
            if (i + nums[i] >= nums.size() - 1) return true;
            if (i + nums[i] > max) max = i + nums[i];
        }
        return false;
    }
};

int main() {
    Solution sol;
    vector nums = {3, 2, 1, 0, 4};
    cout << sol.canJump(nums) << endl;
    return 0;
}
