//
// Created by Kurna on 25-9-28.
//
#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

class Solution {
public:
    bool wordBreak(string s, vector<string> &wordDict) {
        auto wordDictSet = unordered_set<string>();
        for (auto word: wordDict) {
            wordDictSet.insert(word);
        }
        auto dp = vector<bool>(s.size() + 1);
        dp[0] = true;
        for (int i = 1; i <= s.size(); i++) {
            for (int j = 0; j < i; ++j) {
                if (dp[j] && wordDictSet.find(s.substr(j, i - j)) != wordDictSet.end()) {
                    dp[i] = true;
                    break;
                }
            }
        }
        return dp[s.size()];
    }
    // 或者
    bool wordBreak0(string s, vector<string> &wordDict) {
        vector<bool> dp(s.size() + 1);
        dp[0] = true;
        for (int i = 1; i <= s.size(); ++i) {
            for (const auto &word : wordDict) {
                if (i >= word.size()) {
                    auto subStr = s.substr(i - word.size(), word.size());
                    if (subStr == word) {
                        dp[i] = dp[i - word.size()];
                    }
                }
                if (dp[i]) break;
            }
        }
        return dp.back();
    }
};

int main() {
    Solution sol;
    string s = "leetCode";
    vector<string> wordDict = {"leet", "code"};
    cout << sol.wordBreak(s, wordDict) << endl;
    return 0;
}
