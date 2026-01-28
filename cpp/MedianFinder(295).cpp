#include <vector>
#include <iostream>
#include <stdexcept>

//
// Created by Kurna on 2026/1/24.
//
class MaxHeap {
public:
    MaxHeap() = default;

    void push(int val) {
        data.push_back(val);
        siftUp(data.size() - 1);
    }

    void pop() {
        if (data.empty()) return;
        data[0] = data.back();
        data.pop_back();
        if (!data.empty()) siftDown(0);
    }

    int top() const {
        if (data.empty()) throw std::runtime_error("MaxHeap is empty");
        return data[0];
    }

    size_t size() const { return data.size(); }
    bool empty() const { return data.empty(); }

private:
    std::vector<int> data;

    void siftUp(size_t idx) {
        while (idx > 0) {
            size_t parent = (idx - 1) / 2;
            if (data[parent] >= data[idx]) break;
            std::swap(data[parent], data[idx]);
            idx = parent;
        }
    }

    void siftDown(size_t idx) {
        size_t n = data.size();
        while (true) {
            size_t left = idx * 2 + 1;
            size_t right = idx * 2 + 2;
            size_t largest = idx;
            if (left < n && data[left] > data[largest]) largest = left;
            if (right < n && data[right] > data[largest]) largest = right;
            if (largest == idx) break;
            std::swap(data[idx], data[largest]);
            idx = largest;
        }
    }
};

// Simple min-heap with only necessary operations
class MinHeap {
public:
    MinHeap() = default;

    void push(int val) {
        data.push_back(val);
        siftUp(data.size() - 1);
    }

    void pop() {
        if (data.empty()) return;
        data[0] = data.back();
        data.pop_back();
        if (!data.empty()) siftDown(0);
    }

    int top() const {
        if (data.empty()) throw std::runtime_error("MinHeap is empty");
        return data[0];
    }

    size_t size() const { return data.size(); }
    bool empty() const { return data.empty(); }

private:
    std::vector<int> data;

    void siftUp(size_t idx) {
        while (idx > 0) {
            size_t parent = (idx - 1) / 2;
            if (data[parent] <= data[idx]) break;
            std::swap(data[parent], data[idx]);
            idx = parent;
        }
    }

    void siftDown(size_t idx) {
        size_t n = data.size();
        while (true) {
            size_t left = idx * 2 + 1;
            size_t right = idx * 2 + 2;
            size_t smallest = idx;
            if (left < n && data[left] < data[smallest]) smallest = left;
            if (right < n && data[right] < data[smallest]) smallest = right;
            if (smallest == idx) break;
            std::swap(data[idx], data[smallest]);
            idx = smallest;
        }
    }
};

class MedianFinder {
public:
    MedianFinder() = default;

    void addNum(int num) {
        if (max_heap.empty() || num <= max_heap.top()) {
            max_heap.push(num);
        } else {
            min_heap.push(num);
        }
        // balance sizes: max_heap can have at most one more element
        if (max_heap.size() > min_heap.size() + 1) {
            int v = max_heap.top();
            max_heap.pop();
            min_heap.push(v);
        } else if (min_heap.size() > max_heap.size()) {
            int v = min_heap.top();
            min_heap.pop();
            max_heap.push(v);
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
    MaxHeap max_heap; // lower half (max-heap)
    MinHeap min_heap; // upper half (min-heap)
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
