//
// Created by Kurna on 25-9-19.
//
#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
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

class Sort {
public:
    void Merge(vector<int> &arr, int l, int mid, int r) {
        int i = l, j = mid + 1, k = l;
        auto tmp = arr;
        while (i <= mid && j <= r) {
            if (arr[i] <= arr[j]) {
                tmp[k++] = arr[i++];
            } else {
                tmp[k++] = arr[j++];
            }
        }
        if (i > mid) {
            while (k <= r) tmp[k++] = arr[j++];
        } else {
            while (k <= r) tmp[k++] = arr[i++];
        }
        arr = tmp;
    }
    void mergeSort(vector<int> &arr, int l, int r) {
        if (l < r) {
            int mid = (r - l) / 2 + l;
            mergeSort(arr, l, mid);
            mergeSort(arr, mid + 1, r);
            Merge(arr, l, mid, r);
        }
    }
};

int main() {
    auto vectorsEqual = [](const vector<int>& a, const vector<int>& b) {
        return a == b;
    };

    MergeSort ms;
    Sort st;

    // Empty array
    {
        vector<int> arr;
        vector<int> expected = arr;
        sort(expected.begin(), expected.end());
        ms.mergeSort(arr, 0, (int)arr.size() - 1);
        assert(vectorsEqual(arr, expected));
        st.mergeSort(arr, 0, (int)arr.size() - 1);
        assert(vectorsEqual(arr, expected));
    }

    // Single element
    {
        vector<int> arr = {42};
        vector<int> expected = arr;
        sort(expected.begin(), expected.end());
        ms.mergeSort(arr, 0, (int)arr.size() - 1);
        assert(vectorsEqual(arr, expected));
        st.mergeSort(arr, 0, (int)arr.size() - 1);
        assert(vectorsEqual(arr, expected));
    }

    // Already sorted
    {
        vector<int> arr = {1, 2, 3, 4, 5};
        vector<int> expected = arr;
        sort(expected.begin(), expected.end());
        ms.mergeSort(arr, 0, (int)arr.size() - 1);
        assert(vectorsEqual(arr, expected));
        st.mergeSort(arr, 0, (int)arr.size() - 1);
        assert(vectorsEqual(arr, expected));
    }

    // Reverse order
    {
        vector<int> arr = {5, 4, 3, 2, 1};
        vector<int> expected = arr;
        sort(expected.begin(), expected.end());
        ms.mergeSort(arr, 0, (int)arr.size() - 1);
        assert(vectorsEqual(arr, expected));
        arr = {5,4,3,2,1};
        st.mergeSort(arr, 0, (int)arr.size() - 1);
        assert(vectorsEqual(arr, expected));
    }

    // With duplicates
    {
        vector<int> arr = {3, 1, 2, 3, 2, 1, 3};
        vector<int> expected = arr;
        sort(expected.begin(), expected.end());
        ms.mergeSort(arr, 0, (int)arr.size() - 1);
        assert(vectorsEqual(arr, expected));
        arr = {3,1,2,3,2,1,3};
        st.mergeSort(arr, 0, (int)arr.size() - 1);
        assert(vectorsEqual(arr, expected));
    }

    // Multiple randomized cases
    {
        vector<vector<int>> cases = {
            {7},
            {2, 1},
            {4, 5, 1, 3, 2},
            {10, -1, 3, 3, 0, 5},
            {5,5,5,5,5}
        };
        for (auto arr : cases) {
            vector<int> expected = arr;
            sort(expected.begin(), expected.end());

            vector<int> a1 = arr;
            ms.mergeSort(a1, 0, (int)a1.size() - 1);
            assert(vectorsEqual(a1, expected));

            vector<int> a2 = arr;
            st.mergeSort(a2, 0, (int)a2.size() - 1);
            assert(vectorsEqual(a2, expected));
        }
    }

    cout << "All sorting tests passed." << endl;
    return 0;
}
