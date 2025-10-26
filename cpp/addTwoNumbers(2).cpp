//
// Created by Kurna on 25-10-25.
//
#include <iostream>
#include <listnode.hpp>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
        ListNode *head = nullptr, *tmp = nullptr;
        ListNode *p1 = l1, *p2 = l2;
        int flag = 0;
        while (p1 && p2) {
            int sum = p1->val + p2->val + flag;
            if (sum > 9) {
                flag = 1;
            } else {
                flag = 0;
            }
            if (!head || !tmp) {
                head = new ListNode(sum % 10);
                tmp = head;
            } else {
                tmp->next = new ListNode(sum  % 10);
                tmp = tmp->next;
            }
            p1 = p1->next, p2 = p2->next;
        }
        while (p1) {
            int sum = p1->val + flag;
            if (sum > 9) {
                flag = 1;
            } else {
                flag = 0;
            }
            if (!head || !tmp) {
                head = new ListNode(sum % 10);
                tmp = head;
            } else {
                tmp->next = new ListNode(sum  % 10);
                tmp = tmp->next;
            }
            p1 = p1->next;
        }
        while (p2) {
            int sum = p2->val + flag;
            if (sum > 9) {
                flag = 1;
            } else {
                flag = 0;
            }
            if (!head || !tmp) {
                head = new ListNode(sum % 10);
                tmp = head;
            } else {
                tmp->next = new ListNode(sum  % 10);
                tmp = tmp->next;
            }
            p2 = p2->next;
        }
        if (flag == 1) {
            tmp->next = new ListNode(flag);
        }
        return head;
    }
};

int main() {
    Solution sol;
    auto ans = sol.addTwoNumbers(ListNodeUtils::construct({2, 4, 3}), ListNodeUtils::construct({5, 6, 4}));
    LinkedList ll(ans);
    // 收集链表值到vector
    vector<int> vals;
    for (auto& val : ll) {
        vals.push_back(val);
    }
    // 反转vector以倒序
    reverse(vals.begin(), vals.end());
    // 打印倒序值
    for (auto v : vals) {
        cout << v;
    }
    cout << endl;
    // 清理内存
    ListNodeUtils::destroy(ans);
}