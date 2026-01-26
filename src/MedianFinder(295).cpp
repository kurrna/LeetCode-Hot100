#include <queue>
#include <vector>
#include <functional>
#include <iostream>

//
// Created by Kurna on 2026/1/24.
//
class MedianFinder {
public:
    MedianFinder()
        : min_heap([](int a, int b) { return a > b; }) // lambda comparator for min-heap
    {
    }

    void addNum(int num) {
        if (max_heap.empty() || num <= max_heap.top()) {
            max_heap.push(num);
        } else {
            min_heap.push(num);
        }
        if (max_heap.size() > min_heap.size() + 1) {
            min_heap.push(max_heap.top());
            max_heap.pop();
        } else if (min_heap.size() > max_heap.size()) {
            max_heap.push(min_heap.top());
            min_heap.pop();
        }
    }

    double findMedian() {
        if (max_heap.empty() && min_heap.empty()) return 0.0;
        if (max_heap.size() == min_heap.size()) {
            return (static_cast<double>(max_heap.top()) + static_cast<double>(min_heap.top())) / 2.0;
        }
        return max_heap.top();
    }

private:
    // max-heap for the lower half
    std::priority_queue<int> max_heap;
    // min-heap for the upper half, use std::function with a lambda comparator as requested
    std::priority_queue<int, std::vector<int>, std::function<bool(int, int)> > min_heap;
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */

int main() {
    MedianFinder mf;
    mf.addNum(1);
    std::cout << "Median after adding 1: " << mf.findMedian() << "\n"; // 1
    mf.addNum(2);
    std::cout << "Median after adding 2: " << mf.findMedian() << "\n"; // 1.5
    mf.addNum(3);
    std::cout << "Median after adding 3: " << mf.findMedian() << "\n"; // 2
    mf.addNum(4);
    std::cout << "Median after adding 4: " << mf.findMedian() << "\n"; // 2.5
    mf.addNum(5);
    std::cout << "Median after adding 5: " << mf.findMedian() << "\n"; // 3
    return 0;
}
