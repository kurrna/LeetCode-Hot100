//
// Created by Kurna on 2026/1/22.
//
#include <iostream>
#include <utility>
#include <vector>
#include <stack>
using namespace std;

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int n = static_cast<int>(heights.size());
        stack<int> stk;
        int maxArea = 0;
        for (int i = 0; i <= n; ++i) {
            int h = (i == n) ? 0 : heights[i];
            // 维护单调栈，使得栈内元素对应的高度单调递增
            while (!stk.empty() && heights[stk.top()] > h) {
                int height = heights[stk.top()];
                stk.pop();
                int width = stk.empty() ? i : i - stk.top() - 1;
                maxArea = max(maxArea, height * width);
            }
            stk.push(i);
        }
        return maxArea;
    }
};

int main() {
    Solution sol;
    vector<int> heights = {2, 1, 5, 6, 2, 3};
    cout << sol.largestRectangleArea(heights) << endl;
    return 0;
}