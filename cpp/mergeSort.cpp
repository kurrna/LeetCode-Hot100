//
// Created by Kurna on 25-9-19.
//
#include <iostream>
#include <vector>
using namespace std;

// 时间复杂度O(nlogn)
class MergeSort {
    void merge(vector<int> &arr, int left, int mid, int right) {
        int n1 = mid - left + 1, n2 = right - mid;
        vector<int> L(n1), R(n2);
        for (int i = 0; i < n1; ++i) {
            L[i] = arr[left + i];
        }
        for (int i = 0; i < n2; ++i) {
            R[i] = arr[mid + 1 + i];
        }
        int i = 0, j = 0, k = left;
        while (i < n1 && j < n2) {
            if (L[i] <= R[j]) {
                arr[k++] = L[i++];
            } else {
                arr[k++] = R[j++];
            }
        }
        while (i < n1) arr[k++] = L[i++];
        while (j < n2) arr[k++] = R[j++];
    }

public:
    void mergeSort(vector<int> &arr, int left, int right) {
        if (left < right) {
            int mid = (right - left) / 2 + left;
            mergeSort(arr, left, mid);
            mergeSort(arr, mid + 1, right);
            merge(arr, left, mid, right);
        }
    }
};

void printArray(const vector<int> &arr) {
    for (int num: arr) {
        cout << num << " ";
    }
    cout << endl;
}

int main() {
    MergeSort ms;
    vector arr = {12, 11, 13, 5, 6, 7};
    ms.mergeSort(arr, 0, arr.size() - 1);
    printArray(arr);
    return 0;
}
