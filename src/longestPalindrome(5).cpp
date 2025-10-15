//
// Created by Kurna on 25-10-15.
//
#include <iostream>
#include <vector>
using namespace std;

class Solution {
   public:
    string longestPalindrome(string s) {
        int max_len = 0;
        string ans_str;
        for (int i = 0; i < 2 * s.size() - 1; ++i) {
            string tmp;
            int k = i & 1 ? 0 : 1;
            for (int j = 1; j <= min((i+1)/2, static_cast<int>(s.size() - 1 - i/2)); ++j) {
                if (s[(i+1)/2 - j] != s[i/2 + j]) break;
                k += 2;
            }
            if (k > max_len) {
                max_len = k;
                ans_str = i & 1 ? s.substr((i+1)/2 - k/2,k) : s.substr(i / 2 - (k - 1) / 2, k);
            }
        }
        return ans_str;
    }
};

class SolutionByDP {
public:
    string longestPalindrome(string s) {
        vector dp(s.size(), vector(s.size(), false));
        int max_len = 1, pos = 0;
        for (int j = 0; j < s.size(); ++j) {
            for (int i = 0; i < j; ++i) {
                if (s[i] == s[j]) {
                    if (j - i <= 2 || dp[i+1][j-1]) {
                        dp[i][j] = true;
                    }
                    if (dp[i][j] && j - i + 1 > max_len) {
                        max_len = j - i + 1;
                        pos = i;
                    }
                }
            }
        }
        return s.substr(pos, max_len);
    }
};

class SolutionManacher {
public:
    string longestPalindrome(string s) {
        if (s.empty()) return "";
        // 预处理：插入分隔符，避免奇偶长度区分
        string t = "#";
        for (char c : s) {
            t += c;
            t += "#";
        }
        int n = t.size();
        vector<int> p(n, 0); // p[i]: 以i为中心的回文半径
        int center = 0, right = 0, max_len = 0, start = 0;
        for (int i = 0; i < n; ++i) {
            int mirror = 2 * center - i;
            if (i < right)
                p[i] = min(right - i, p[mirror]);
            // 尝试扩展
            int a = i + p[i] + 1, b = i - p[i] - 1;
            while (a < n && b >= 0 && t[a] == t[b]) {
                ++p[i];
                ++a;
                --b;
            }
            // 更新中心和右边界
            if (i + p[i] > right) {
                center = i;
                right = i + p[i];
            }
            // 记录最大长度
            if (p[i] > max_len) {
                max_len = p[i];
                start = (i - max_len) / 2;
            }
        }
        return s.substr(start, max_len);
    }
};

int main() {
    Solution sol;
    auto s = "bb";
    cout << sol.longestPalindrome(s) << endl;
    return 0;
}