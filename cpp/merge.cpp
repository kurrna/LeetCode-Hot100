//
// Created by Kurna on 25-9-11.
//
#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
public:
    std::vector<std::vector<int> > merge(std::vector<std::vector<int> > &intervals) {
        std::vector<std::vector<int> > res;
        std::sort(intervals.begin(), intervals.end(), [](const std::vector<int> &a, std::vector<int> &b) {
            if (a[0] != b[0]) {
                return a[0] < b[0];
            }
            return a[1] < b[1];
        });
        res.push_back(intervals[0]);
        for (int i = 1; i < intervals.size(); i++) {
            if (intervals[i][0] <= res.back()[1]) {
                res.back()[1] = std::max(intervals[i][1], res.back()[1]);
            } else {
                res.push_back(intervals[i]);
            }
        }
        return res;
    }
};

void print2DVector(const std::vector<std::vector<int>>& vec) {
    // 遍历外层向量
    for (const auto& row : vec) {
        std::cout << "[";
        // 遍历内层向量
        for (size_t i = 0; i < row.size(); ++i) {
            std::cout << row[i];
            // 除了最后一个元素，其他元素后加逗号
            if (i != row.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "]\n";
    }
}

int main() {
    Solution sol;
    std::vector<std::vector<int> > intervals = {{1, 3}, {2, 6}, {8, 10}, {15, 18}};
    print2DVector(sol.merge(intervals));
}
