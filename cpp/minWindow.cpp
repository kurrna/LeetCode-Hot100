//
// Created by Kurna on 25-8-3.
//
#include <iostream>
#include <cstring>
#include <unordered_map>

class Solution {
public:
    std::unordered_map<char, int> ori, cnt;
    bool check() {
        for (const auto &p : ori) {
            if (cnt[p.first] < p.second) {
                return false;
            }
        }
        return true;
    }
    std::string minWindow(std::string s, std::string t) {
        for (const auto &c : t) {
            ori[c]++;
        }
        int l = 0, r = -1;
        int len = INT_MAX, ansL = -1;
        while (r < static_cast<int>(s.size())) {
            if (ori.find(s[++r]) != ori.end()) {
                cnt[s[r]]++;
            }
            while (check() && l <= r) {
                if (r - l + 1 < len) {
                    len = r - l + 1;
                    ansL = l;
                }
                if (ori.find(s[l]) != ori.end()) {
                    cnt[s[l]]--;
                }
                ++l;
            }
        }
        return ansL == -1 ? std::string() : s.substr(ansL, len);
    }
};

int main() {
    Solution sol;
    std::string s = "ADOBECODEBANC", t = "ABC";
    std::cout << sol.minWindow(s, t) << std::endl;
}