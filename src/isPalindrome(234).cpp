//
// Created by Kurna on 25-10-21.
// Modern C++ implementation for LeetCode 234: Palindrome Linked List

#include <iostream>
#include <listnode.hpp>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

class Solution {
public:
    // Reverse a linked list and return new head
    ListNode* reverseList(ListNode* head) {
        ListNode *prev = nullptr;
        while (head) {
            ListNode* next = head->next;
            head->next = prev;
            prev = head;
            head = next;
        }
        return prev;
    }

    // Main algorithm: O(n) time, O(1) extra space
    bool isPalindrome(ListNode* head) {
        if (!head || !head->next) return true;

        // 1) Find middle (slow will point to middle)
        ListNode* slow = head;
        ListNode* fast = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }

        // 2) For odd length, move slow one step to start of second half
        if (fast) { // fast != nullptr -> odd length
            slow = slow->next;
        }

        // 3) Reverse second half
        ListNode* second = reverseList(slow);
        ListNode* p1 = head;
        ListNode* p2 = second;
        bool flag = true;
        while (p2) {
            if (p1->val != p2->val) { flag = false; break; }
            p1 = p1->next;
            p2 = p2->next;
        }

        // 4) Restore (optional) the second half to keep original list structure
        reverseList(second);
        return flag;
    }
};

int main() {
    Solution sol;

    auto run = [&](const vector<int>& vals) {
        ListNode* head = ListNodeUtils::construct(vals);
        bool res = sol.isPalindrome(head);
        cout << "[";
        for (size_t i = 0; i < vals.size(); ++i) {
            if (i) cout << ",";
            cout << vals[i];
        }
        cout << "] -> " << (res ? "true" : "false") << endl;
        ListNodeUtils::destroy(head);
    };

    // Tests
    run({});                 // empty list -> true
    run({1});                // single node -> true
    run({1,2,2,1});          // even palindrome -> true
    run({1,2,3,2,1});        // odd palindrome -> true
    run({1,2,3,4});          // not palindrome -> false

    return 0;
}