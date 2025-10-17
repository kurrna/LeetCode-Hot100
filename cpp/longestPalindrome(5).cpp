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
    // Manacher算法：线性时间查找最长回文子串
    // 核心思想：利用回文的对称性，避免重复扩展
    string longestPalindrome(string s) {
        if (s.empty()) return "";
        // Step 1: 预处理字符串，插入分隔符'#'，统一奇偶回文处理
        // 例如：abc -> #a#b#c#
        string t = "#";
        for (char c : s) {
            t += c;
            t += "#";
        }
        int n = t.size();
        vector<int> p(n, 0); // p[i]: 以t[i]为中心的回文半径（不含自身）
        int center = 0, right = 0; // 当前回文的中心和右边界
        int max_len = 0, start = 0; // 最长回文长度和起始位置
        // Step 2: 主循环，遍历每个中心
        for (int i = 0; i < n; ++i) {
            int mirror = 2 * center - i; // i关于center的对称点
            // Step 3: 初始化p[i]
            if (i < right)
                p[i] = min(right - i, p[mirror]); // 利用对称性减少扩展
            // Step 4: 尝试向两边扩展
            int a = i + p[i] + 1, b = i - p[i] - 1;
            while (a < n && b >= 0 && t[a] == t[b]) {
                ++p[i];
                ++a;
                --b;
            }
            // Step 5: 更新center和right
            if (i + p[i] > right) {
                center = i;
                right = i + p[i];
            }
            // Step 6: 记录最长回文
            if (p[i] > max_len) {
                max_len = p[i];
                // 计算原字符串中的起始位置
                start = (i - max_len) / 2;
            }
        }
        // Step 7: 返回最长回文子串
        return s.substr(start, max_len);
    }
};

int main() {
    SolutionManacher sol;
    auto s = "bcacbbd";
    cout << sol.longestPalindrome(s) << endl;
    return 0;
}