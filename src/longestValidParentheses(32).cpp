//
// Created by Kurna on 25-10-11.
//
#include <iostream>
#include <stack>
#include <vector>
using namespace std;

class Solution {
   public:
    int longestValidParentheses(string s) {
        vector bitmap(s.size(), false);
        stack<int> st;
        int l = 0, len = 0, ans = 0;
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == '(')
                st.push(i);
            else {
                if (st.empty())
                    bitmap[i] = true;
                else
                    st.pop();
            }
        }
        while (!st.empty()) {
            bitmap[st.top()] = 1;
            st.pop();
        }
        for (int i = 0; i < s.length(); ++i) {
            if (bitmap[i]) {
                len = 0;
                continue;
            }
            len++;
            ans = max(len, ans);
        }
        return ans;
    }
};

class SolutionByDP {
   public:
    int longestValidParentheses(string s) {
        vector dp(s.size(), 0);
        int ans = 0;
        for (int i = 1; i < s.length(); i++) {
            if (s[i] == ')') {
                if (s[i - 1] == '(') {
                    dp[i] = (i >= 2 ? dp[i - 2] : 0) + 2;
                } else if (i - dp[i - 1] > 0 && s[i - dp[i - 1] - 1] == '(') {
                    dp[i] = dp[i - 1] + ((i - dp[i - 1]) >= 2 ? dp[i - dp[i - 1] - 2] : 0) + 2;
                }
                ans = max(ans, dp[i]);
            }
        }
        return ans;
    }
};

int main() {
    SolutionByDP sol;
    string s = "(()";
    cout << sol.longestValidParentheses(s) << endl;
    return 0;
}