//
// Created by Kurna on 25-10-28.
//
#include <iostream>
#include <listnode.hpp>
using namespace std;

class Solution {
public:
    // 反转一个子链表，并返回新的头节点
    ListNode* reverse(ListNode* head, ListNode* tail) {
        ListNode* prev = nullptr;
        if (tail) {
            prev = tail->next;
        }
        ListNode* curr = head;
        ListNode* stop_node = prev;

        while (curr != stop_node) {
            ListNode* next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        return tail;
    }

    ListNode* reverseKGroup(ListNode* head, int k) {
        if (!head || k == 1) {
            return head;
        }

        auto* dummy = new ListNode(-1, head);
        ListNode* prev = dummy;

        while (head) {
            ListNode* tail = prev;
            // 检查剩余部分是否有k个节点
            for (int i = 0; i < k; ++i) {
                tail = tail->next;
                if (!tail) {
                    // 节点数不足k，直接返回
                    return dummy->next;
                }
            }
            ListNode* next_group_head = tail->next;
            // 反转k个节点
            ListNode* reversed_head = reverse(head, tail);

            // 把子链表重新接回原链表
            prev->next = reversed_head;
            // 此时的 head 节点在反转后变成了当前组的尾部
            head->next = next_group_head;

            // 为下一次循环做准备
            prev = head;
            head = next_group_head;
        }

        return dummy->next;
    }
};

int main() {
    Solution sol;
    auto input = ListNodeUtils::construct({1, 2, 3, 4, 5});
    auto ans = sol.reverseKGroup(input, 2);
    // auto ans = sol.reverseList(input);
    while (ans) {
        cout << ans->val << (ans->next ? ", " : "");
        ans = ans->next;
    }
    cout << endl;
    return 0;
}