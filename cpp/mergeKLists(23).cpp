//
// Created by Kurna on 25-10-31.
//
#include <../include/listnode.hpp>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

class Solution {
   public:
    ListNode *mergeKLists(vector<ListNode *> &lists) {
        if (lists.empty()) return nullptr;
        int k = static_cast<int>(lists.size());
        int mid = k / 2;
        return merge(mergeKLists(lists, 0, mid), mergeKLists(lists, mid + 1, k - 1));
    }

    ListNode *mergeKLists(vector<ListNode *> &lists, int l, int r) {
        if (l > r) return nullptr;
        if (l == r) return lists[l];
        int mid = (r - l) / 2 + l;
        return merge(mergeKLists(lists, l, mid), mergeKLists(lists, mid + 1, r));
    }

    ListNode *merge(ListNode *list1, ListNode *list2) {
        auto dummy = new ListNode();
        auto merge = dummy;
        while (list1 && list2) {
            if (list1->val <= list2->val) {
                merge->next = list1;
                list1 = list1->next;
            } else {
                merge->next = list2;
                list2 = list2->next;
            }
            merge = merge->next;
        }
        merge->next = list1 ? list1 : list2;
        return dummy->next;
    }
};

class PriorityQueue {
public:
    struct Status {
        int val;
        ListNode *ptr;
        bool operator < (const Status &rhs) const {
            return val > rhs.val;
        }
    };

    priority_queue <Status> q;

    ListNode *mergeKLists(vector<ListNode *> &lists) {
        for (auto &list : lists) {
            if (list) q.push({list->val, list});
        }
        ListNode head, *tail = &head;
        while (!q.empty()) {
            auto f = q.top(); q.pop();
            tail->next = f.ptr;
            tail = tail->next;
            if (f.ptr->next) q.push({f.ptr->next->val, f.ptr->next});
        }
        return head.next;
    }
};

int main() {
    Solution sol;
    auto input0 = ListNodeUtils::construct({1, 4, 5});
    auto input1 = ListNodeUtils::construct({1, 3, 4});
    auto input2 = ListNodeUtils::construct({2, 6});
    vector input = {input0, input1, input2};
    auto ans = sol.mergeKLists(input);
    while (ans) {
        cout << ans->val << (ans->next ? ", " : "");
        ans = ans->next;
    }
    cout << endl;
    return 0;
}