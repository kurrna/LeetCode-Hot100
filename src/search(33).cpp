//
// Created by Kurna on 25-9-17.
//
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int search(vector<int> &nums, int target) {
        int l = 0, r = nums.size() - 1;
        while (l <= r) {
            int mid = (r - l) / 2 + l;
            if (nums[mid] == target) return mid;
            if (mid == l) {
                if (nums[r] == target) return r;
                else break;
            } else if (nums[mid] > nums[l]) {
                // 左半有序
                if (nums[mid] > target) {
                    if (nums[l] == target) return l;
                    if (nums[l] > target) l = mid + 1;
                    else r = mid - 1;
                } else l = mid + 1;
            } else {
                // 右半有序
                if (nums[mid] < target) {
                    if (nums[r] == target) return r;
                    if (nums[r] < target) r = mid - 1;
                    else l = mid + 1;
                } else r = mid - 1;
            }
        }
        return -1;
    }
};

int main() {
    Solution sol;
    vector nums = {4,5,6,7,0,1,2};
    int target = 3;
    cout << sol.search(nums, target) << endl;
    return 0;
}
