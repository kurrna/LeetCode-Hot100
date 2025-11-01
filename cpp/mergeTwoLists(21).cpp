//
// Created by Kurna on 25-10-24.
//
#include <iostream>
#include <listnode.hpp>
using namespace std;

class Solution {
   public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode *p1 = list1, *p2 = list2;
        ListNode* head;
        if (p1 == nullptr && p2 == nullptr) return nullptr;
        if (p1 == nullptr) return p2;
        if (p2 == nullptr) return p1;
        if (p1->val < p2->val) {
            head = new ListNode(p1->val);
            p1 = p1->next;
        } else {
            head = new ListNode(p2->val);
            p2 = p2->next;
        }
        ListNode *tmp = head, *newP = nullptr;
        while (p1 != nullptr && p2 != nullptr) {
            if (p1->val < p2->val) {
                newP = new ListNode(p1->val);
                p1 = p1->next;
            } else {
                newP = new ListNode(p2->val);
                p2 = p2->next;
            }
            tmp->next = newP;
            tmp = newP;
        }
        if (p1) {
            tmp->next = p1;
        } else {
            tmp->next = p2;
        }
        return head;
    }
};

int main() {
    Solution sol;
    auto ans =
        sol.mergeTwoLists(ListNodeUtils::construct({1, 2, 3}), ListNodeUtils::construct({4, 5}));
    cout << "{";
    while (ans->next) {
        cout << ans->val << ", ";
        ans = ans->next;
    }
    cout << ans->val << "}" << endl;
    return 0;
}