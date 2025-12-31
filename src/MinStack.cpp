//
// Created by Kurna on 2025/12/31.
//
#include <iostream>
#include <vector>
#include <stdexcept>

class MinStack {
    std::vector<int> data;
    std::vector<int> mins; // mins.back() is current minimum

public:
    MinStack() = default;

    void push(int val) {
        data.push_back(val);
        if (mins.empty() || val <= mins.back()) {
            mins.push_back(val);
        }
    }

    void pop() {
        if (data.empty()) return; // no-op on empty stack
        int topVal = data.back();
        data.pop_back();
        if (!mins.empty() && topVal == mins.back()) {
            mins.pop_back();
        }
    }

    int top() {
        if (data.empty()) throw std::runtime_error("top() called on empty stack");
        return data.back();
    }

    int getMin() {
        if (mins.empty()) throw std::runtime_error("getMin() called on empty stack");
        return mins.back();
    }
};

int main() {
    MinStack minStk;
    minStk.push(-2);
    minStk.push(0);
    minStk.push(-3);
    std::cout << minStk.getMin() << "\n"; // -3
    minStk.pop();
    std::cout << minStk.top() << "\n";    // 0
    std::cout << minStk.getMin() << std::endl; // -2
    return 0;
}
