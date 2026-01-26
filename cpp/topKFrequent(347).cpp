//
// Created by Kurna on 2026/1/23.
//
#include <functional>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
public:
    void maxHeapify(vector<pair<int, int>>& heap, int index, int heapSize) {
        int largest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (left < heapSize && heap[left].second > heap[largest].second) {
            largest = left;
        }
        if (right < heapSize && heap[right].second > heap[largest].second) {
            largest = right;
        }
        if (largest != index) {
            swap(heap[index], heap[largest]);
            maxHeapify(heap, largest, heapSize);
        }
    }

    void buildMaxHeap(vector<pair<int, int>>& heap) {
        int heapSize = heap.size();
        for (int i = heapSize / 2 - 1; i >= 0; --i) {
            maxHeapify(heap, i, heapSize);
        }
    }

    vector<int> topKFrequent(vector<int>& nums, int k) {
        vector res(k, 0);
        unordered_map<int, int> countMap;
        for (int &num : nums) {
            countMap[num]++;
        }
        vector<pair<int, int>> heap;
        for (auto &[fst, snd] : countMap) {
            heap.emplace_back(fst, snd);
        }
        auto cmp = [](const pair<int,int>& a, const pair<int,int>& b){
            return a.second < b.second;
        };
        priority_queue maxHeap(cmp, std::move(heap));
        for (int i = 0; i < k && !maxHeap.empty(); ++i) {
            res[i] = maxHeap.top().first;
            maxHeap.pop();
        }
        return res;
    }
};

int main() {
    Solution sol;
    vector<int> nums = {1,1,1,2,2,3};
    int k = 2;
    vector<int> result = sol.topKFrequent(nums, k);
    for (int num : result) {
        cout << num << " ";
    }
    return 0;
}