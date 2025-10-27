#include <iostream>
#include <listnode.hpp>
using namespace std;

class Solution {
   public:
    ListNode *swapPairs(ListNode *head) {
        auto dummy = new ListNode(-1, head);
        ListNode *p = dummy;
        while (p->next && p->next->next) {
            ListNode *first = p->next;
            ListNode *second = first->next;
            ListNode *next = second->next;
            // 重新连接以交换 first 和 second
            p->next = second;
            second->next = first;
            first->next = next;
            // 前进到已经处理过的节点（即 first）
            p = first;
        }
        ListNode *res = dummy->next;
        delete dummy;
        return res;
    }
};

int main() {
    Solution sol;
    auto input = ListNodeUtils::construct({1, 2, 3, 4});
    auto ans = sol.swapPairs(input);
    for (ListNode *cur = ans; cur; cur = cur->next) {
        cout << cur->val;
        if (cur->next) cout << ", ";
    }
    cout << endl;
    return 0;
}