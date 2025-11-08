#ifdef __GNUC__
#include <bits/stdc++.h>
#else
#include <iostream>
#include <vector>
#endif

class Solution {
public:
    std::vector<std::string> letterCombinations(const std::string& digits) {
        std::vector<std::string> ans;
        if (digits.empty()) return ans;
        int n = static_cast<int>(digits.size());
        std::vector<std::string> mapping = {"",    "",    "abc",  "def", "ghi",
                                            "jkl", "mno", "pqrs", "tuv", "wxyz"};
        std::function<void(std::string&, int)> backtrack =
            [&](std::string &combination, int index) {
                if (index == n) {
                    ans.push_back(combination);
                    return;
                }
                char digit = digits[index];
                const std::string &letters = mapping[digit - '0'];
                for (const char &letter: letters) {
                    combination.push_back(letter);
                    backtrack(combination, index + 1);
                    combination.pop_back();
                }
            };
        std::string combination;
        backtrack(combination, 0);
        return ans;
    }
};

int main() {
    Solution sol;
    auto digits = "23";
    auto ans = sol.letterCombinations(digits);
    for (const auto &combination: ans) {
        std::cout << combination << " ";
    }
    return 0;
}
