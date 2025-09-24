//
// Created by Kurna on 25-9-23.
//
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
using namespace std;

class Solution {
    unordered_map<char, int> lastChPos;

public:
    vector<int> partitionLabels(string s) {
        for (int i = s.size() - 1; i >= 0; --i) {
            if (!lastChPos[s[i]]) {
                lastChPos[s[i]] = i;
            }
        }
        vector<int> res;
        int l = 0, r = 0;
        for (int i = 0; i < s.size(); ++i) {
            r = max(r, lastChPos[s[i]]);
            if (i == r) {
                res.push_back(r - l + 1);
                l = r + 1;
            }
        }
        return res;
    }
};

int main() {
    Solution sol;
    string s = "qiejxqfnqceocmy";
    auto ans = sol.partitionLabels(s);
    for (auto x: ans) {
        cout << x << " ";
    }
    cout << endl;
    return 0;
}
