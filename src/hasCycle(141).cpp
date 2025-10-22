//
// Created by Kurna on 25-10-22.
//
#include <iostream>
#include <listnode.hpp>
#include <unordered_set>
using namespace std;

class Solution {
   public:
    bool hasCycle(ListNode *head) {
        unordered_set<ListNode *> hs;
        while (head) {
            auto it = hs.find(head);
            if (it != hs.end()) {
                return true;
            }
            hs.insert(head);
            head = head->next;
        }
        return false;
    }
};

class SolutionByReverse {
public:
    bool hasCycle(ListNode *head) {
        if (!head || !head->next) return false;
        ListNode *original = head;
        ListNode *prev = nullptr;
        while (head->next) {
            ListNode *temp = head->next;
            head->next = prev;
            prev = head;
            head = temp;
        }
        if (original == head) return true;
        return false;
    }
};

class SolutionByFastSlowPtr {
public:
    bool hasCycle(ListNode *head) {
        if (!head || !head->next) return false;
        ListNode *fast = head->next->next, *slow = head->next;
        while (fast && slow && fast->next) {
            if (fast == slow) return true;
            fast = fast->next->next;
            slow = slow->next;
        }
        return false;
    }
};

ListNode *constructWithCycle(const vector<int> &arr, int p);

int main() {
    SolutionByFastSlowPtr sol;
    cout << sol.hasCycle(constructWithCycle({3, 2, 0, -4}, 1)) << endl;
    return 0;
}

ListNode *constructWithCycle(const vector<int> &arr, int p)  {
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