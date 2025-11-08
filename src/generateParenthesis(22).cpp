//
// Created by Kurna on 2025/11/8.
//
#include <bits/stdc++.h>

class Solution {
public:
    std::vector<std::string> generateParenthesis(int n) {
        std::vector<std::string> ans;
        // 原代码用 std::string s(2*n, 0); 产生 2*n 个 '\0'，会导致结果含空字符，这里改为空串并预留容量。
        std::string path;
        path.reserve(2 * n);

#if __cplusplus == 202302L
        // C++23: 使用 explicit object parameter (this auto self) 实现递归，不需要 std::function
        auto dfs = [&, n](this auto self, int open, int close) {
            // open: 已放置 '(' 的数量；close: 已放置 ')' 的数量
            if (open == n && close == n) {
                // 长度达到 2*n
                ans.emplace_back(path);
                return;
            }
            // 还能放 '('
            if (open < n) {
                path.push_back('(');
                self(open + 1, close);
                path.pop_back();
            }
            // 只能在 close < open 时放 ')'
            if (close < open) {
                path.push_back(')');
                self(open, close + 1);
                path.pop_back();
            }
        };
        dfs(0, 0);
#else
        std::function<void(int, int)> dfs = [&](int open, int close) {
            if (open == n && close == n) {
                ans.emplace_back(path);
                return;
            }
            if (open < n) {
                path.push_back('(');
                dfs(open + 1, close);
                path.pop_back();
            }
            if (close < open) {
                path.push_back(')');
                dfs(open, close + 1);
                path.pop_back();
            }
        };
        dfs(0, 0);
#endif
        return ans;
    }
};

class Solution2 {
    std::shared_ptr<std::vector<std::string> > cache[100] = {nullptr};

public:
    std::shared_ptr<std::vector<std::string> > generate(int n) {
        if (cache[n] != nullptr) return cache[n];
        if (n == 0) {
            cache[0] = std::make_shared<std::vector<std::string> >(std::vector<std::string>{""});
        } else {
            auto result = std::make_shared<std::vector<std::string> >();
            for (int i = 0; i != n; ++i) {
                auto lefts = generate(i);
                auto rights = generate(n - 1 - i);
                for (const auto &left: *lefts)
                    for (const auto &right: *rights)
                        result->emplace_back(("(" + left + ")").append(right));
            }
            cache[n] = result;
        }
        return cache[n];
    }

    std::vector<std::string> generateParenthesis(int n) {
        return *generate(n);
    }
};

int main() {
    Solution2 sol;
    int n = 3;
    for (auto ans = sol.generateParenthesis(n); const auto &s: ans) {
        std::cout << s << '\n';
    }
    std::cout << std::endl;
    return 0;
}
