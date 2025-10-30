//
// Created by Kurna on 25-10-30.
//
#include <iostream>
#include <listnode.hpp>
using namespace std;

class Solution {
public:
    ListNode *merge(ListNode *list1, ListNode *list2) {
        auto dummy = new ListNode();
        ListNode *merge = dummy;
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
    ListNode *sortList(ListNode *head) {
        if (!head || !head->next) return head;
        ListNode *slow = head, *fast = head;
        while (fast->next && fast->next->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        ListNode *mid = slow->next;
        slow->next = nullptr;
        return merge(sortList(head), sortList(mid));
    }
};

int main() {
    Solution sol;
    auto input = ListNodeUtils::construct({4, 2, 1, 3});
    auto ans = sol.sortList(input);
    while (ans) {
        cout << ans->val << (ans->next ? ", " : "");
        ans = ans->next;
    }
    cout << endl;
    return 0;
}