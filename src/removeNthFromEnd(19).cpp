#include <iostream>
#include <listnode.hpp>
#include <vector>
using namespace std;

class Solution {
   public:
    ListNode *removeNthFromEnd(ListNode *head, int n) {
        if (!head) return nullptr;
        ListNode *prev = nullptr, *cur = head, *next = head->next;
        vector<ListNode *> st;
        st.push_back(nullptr);
        while (cur) {
            st.push_back(cur);
            cur = cur->next;
        }
        if (n == 1) st.push_back(nullptr);
        for (int i = 0; i < n - 2; i++) {
            st.pop_back();
        }
        next = st.back();
        st.pop_back();
        st.pop_back();
        prev = st.back();
        if (prev == nullptr)
            head = next;
        else
            prev->next = next;

        return head;
    }
};

class SolutionByDoublePtr {
   public:
    ListNode *removeNthFromEnd(ListNode *head, int n) {
        auto *dummy = new ListNode(-1, head);
        ListNode *front = head, *back = head, *prev = dummy;
        for (int i = 0; i < n; i++) {
            front = front->next;
        }
        while (front) {
            front = front->next;
            prev = back;
            back = back->next;
        }
        if (prev->val == -1) head = back->next;
        else prev->next = back->next;
        return head;
    }
};

int main() {
    Solution sol;
    auto input = ListNodeUtils::construct({1, 2, 3, 4, 5});
    auto ans = sol.removeNthFromEnd(input, 2);
    while (ans->next) {
        cout << ans->val << ", ";
        ans = ans->next;
    }
    cout << ans->val << endl;
    return 0;
}