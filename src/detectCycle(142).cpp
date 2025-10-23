//
// Created by Kurna on 25-10-23.
//
#include <iostream>
#include <listnode.hpp>
using namespace std;

class Solution {
   public:
    /*
     * a + b + c = 2 * (a + c)
     * => b = a + c
     * => b - c = a
     */
    ListNode *detectCycle(ListNode *head) {
        if (!head || !head->next) return nullptr;
        ListNode *fast = head->next->next, *slow = head->next;
        while (fast && slow && fast->next) {
            if (fast == slow) {
                ListNode *tmp = head;
                while (tmp != slow) {
                    tmp = tmp->next;
                    slow = slow->next;
                }
                return tmp;
            }
            fast = fast->next->next;
            slow = slow->next;

        }
        return nullptr;
    }
};

class SolutionHackLC {
public:
    ListNode *detectCycle(ListNode *head) {
        while(head) {
            // 按着堆内存分配，如果遇到环则肯定next地址小于head
            if(!less<ListNode *>()(head, head->next)) {
                return head->next;
            }
            head = head->next;
        }
        return nullptr;
    }
};

ListNode *constructWithCycle(const vector<int> &arr, int p);

int main() {
    Solution sol;
    cout << sol.detectCycle(constructWithCycle({3, 2, 0, -4}, 1))->val << endl;
    return 0;
}

ListNode *constructWithCycle(const vector<int> &arr, int p) {
    vector<ListNode *> pos(arr.size());
    auto ln = new ListNode(arr[0]);
    pos[0] = ln;
    for (int i = 1; i < arr.size(); i++) {
        ln->next = new ListNode(arr[i]);
        ln = ln->next;
        pos[i] = ln;
    }
    if (p != -1) {
        pos[arr.size() - 1]->next = pos[p];
    }
    return pos[0];
}