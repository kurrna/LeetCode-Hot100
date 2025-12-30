//
// Created by Kurna on 2025/12/30.
//
#include <iostream>
#include <stack>
#include <string>

class Solution {
public:
    bool isValid(const std::string &s) {
        int len = s.length();
        if (len % 2 != 0) {
            return false;
        }
        std::stack<char> stk;
        for (char c : s) {
            if (c == '(' || c == '{' || c == '[') {
                stk.push(c);
            } else {
                if (stk.empty() || !matches(stk.top(), c)) {
                    return false;
                }
                stk.pop();
            }
        }
        return stk.empty();
    }

    static bool matches(char open, char close) {
        return (open == '(' && close == ')') ||
               (open == '{' && close == '}') ||
               (open == '[' && close == ']');
    }
};

int main() {
    Solution sol;
    std::string s;
    std::cin >> s;
    std::cout << sol.isValid(s) << std::endl;
    return 0;
}