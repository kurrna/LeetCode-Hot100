//
// Created by Kurna on 25-9-11.
//
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    void reverseRange(vector<int> &nums, int start, int end) {
        while (start < end) {
            swap(nums[start], nums[end]);
            start++;
            end--;
        }
    }
    void rotate(vector<int> &nums, int k) {
        k %= nums.size();
        reverseRange(nums, nums.size() - k, nums.size() - 1);
        reverseRange(nums, 0, nums.size() - 1);
        reverseRange(nums, k, nums.size() - 1);
    }
};

int main() {
    Solution  sol;
    vector nums = {1, 2, 3, 4, 5, 6, 7};
    sol.rotate(nums, 3);
    for (int i = 0; i < nums.size(); ++i) {
        if (i != nums.size() - 1) cout << nums[i] << ",";
        else cout << nums[i] << endl;
    }
}