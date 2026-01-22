//
// Created by Kurna on 2026/1/21.
//
#include <iostream>
#include <stack>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = static_cast<int>(temperatures.size());
        vector<int> res;
        stack<int> stk;
        for (int i = 0; i < n; ++i) {
            while (!stk.empty() && temperatures[stk.top()] < temperatures[i]) {
                int idx = stk.top(); stk.pop();
                res[idx] = i - idx;
            }
            res.push_back(0);
            stk.push(i);
        }
        return res;
    }
};

int main() {
    Solution sol;
    vector<int> temperatures = {73, 74, 75, 71, 69, 72, 76, 73};
    auto ans = sol.dailyTemperatures(temperatures);
    for (auto &num : ans) {
        cout << num << " ";
    }
    cout << endl;
    return 0;
}