//
// Created by Kurna on 2025/11/11.
//
#include <bits/stdc++.h>
using namespace std;

class Solution {
    bool isPalindrome(const string &s, int left, int right) {
        while (left < right) {
            if (s[left++] != s[right--]) {
                return false;
            }
        }
        return true;
    }

public:
    vector<vector<string> > partition(string s) {
        int n = static_cast<int>(s.size());
        if (n == 1) {
            return {{s}};
        }
        vector<vector<string> > ans;
        vector<string> path;

        function<void(int, int, int)> backtrack = [&](int l, int r, int index)-> void {
            for (int i = index; i < n; i++) {
                if (isPalindrome(s, l, i)) {
                    path.push_back(s.substr(l, i - l + 1));
                    if (i == r) {
                        ans.push_back(path);
                    } else {
                        backtrack(i + 1, r, i + 1);
                    }
                    path.pop_back();
                }
            }
        };
        backtrack(0, n - 1, 0);
        return ans;
    }
};

// 用动态规划预处理回文串
class SolutionDPPre {
    vector<vector<bool> > f;
    vector<vector<string> > ans;
public:
    vector<vector<string> > partition(const string &s) {
        int n = static_cast<int>(s.size());
        f.assign(n, vector(n, true));
        vector<string> path;

        for (int i = n - 1; i >= 0; i--)
            for (int j = i + 1; j < n; j++)
                if (f[i][j])
                    f[i][j] = (s[i] == s[j]) && f[i + 1][j - 1];


        function<void(int)> dfs = [&](int i)-> void {
            if (i == n) {
                ans.push_back(path);
                return;
            }
            for (int j = i; j < n; j++) {
                if (f[i][j]) {
                    path.push_back(s.substr(i, j - i + 1));
                    dfs(j + 1);
                    path.pop_back();
                }
            }
        };
        dfs(0);
        return ans;
    }
};

int main() {
    SolutionDPPre sol;
    string s = "aab";
    auto ans = sol.partition(s);
    for (const auto &vec: ans) {
        for (const auto &str: vec) {
            cout << str << " ";
        }
        cout << endl;
    }
    return 0;
}
