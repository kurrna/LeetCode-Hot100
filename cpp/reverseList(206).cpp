//
// Created by Kurna on 25-10-20.
//
#include <../include/listnode.hpp>
#include <iostream>
using namespace std;

class Solution {
    ListNode *reverseListHelper(ListNode *head, ListNode **tail) {
        if (head->next == nullptr) {
            *tail = head;
            return head;
        }
        ListNode *second = reverseListHelper(head->next, tail);
        second->next = head;
        return head;
    }
public:
    ListNode *reverseList(ListNode *head) {
        if (!head) return nullptr;
        auto **tailptr = new ListNode*;
        reverseListHelper(head, tailptr);
        head->next = nullptr;
        return *tailptr;
    }
};

class ReverseList {
public:
    // Iterative, in-place, O(N) time, O(1) extra space.
    static ListNode* reverseList(ListNode* head) noexcept {
        ListNode* prev = nullptr;
        while (head) {
            // Set head->next to prev and get the original next in one expression.
            ListNode* next = std::exchange(head->next, prev);
            prev = head;
            head = next;
        }
        return prev;
    }

    // Optional: recursive variant (kept for reference; not noexcept because recursion may throw via stack overflow)
    static ListNode* reverseListRecursive(ListNode* head) {
        if (!head || !head->next) return head;
        ListNode* newHead = reverseListRecursive(head->next);
        head->next->next = head;
        head->next = nullptr;
        return newHead;
    }
};

int main() {
    Solution sol;
    auto ans = sol.reverseList(ListNodeUtils::construct({1,2,3,4,5}));
    while (ans->next != nullptr) {
        cout << ans->val << ", ";
        ans = ans->next;
    }
    cout << ans->val << endl;
    return 0;
}