//
// Created by Kurna on 2026/1/21.
//
#include <iostream>
#include <queue>
#include <regex>
#include <vector>
using namespace std;

string operator*(int lhs, const string &rhs) {
    string res;
    for (int j = 0; j < lhs; ++j) res += rhs;
    return res;
}

class Solution {
public:
    string decodeString(string &s) {
        stack<int> count_stk;
        stack<string> string_stk;
        string current_string;
        int k = 0;
        for (char &ch : s) {
            if (isdigit(ch)) {
                k = k * 10 + ch - '0';
            } else if (ch == '[') {
                count_stk.push(k);
                string_stk.push(current_string);
                current_string = "";
                k = 0;
            } else if (ch == ']') {
                string temp = string_stk.top(); string_stk.pop();
                int repeat_times = count_stk.top(); count_stk.pop();
                for (int i = 0; i < repeat_times; ++i) {
                    temp += current_string;
                }
                current_string = temp;
            } else {
                current_string += ch;
            }
        }
        return current_string;
    }
};

int main() {
    Solution sol;
    string s = "3[a2[c]]";
    cout << sol.decodeString(s) << endl;
    return 0;
}
