#include <iostream>
#include <listnode.hpp>
using namespace std;

class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if (!headA || !headB) return nullptr;
        ListNode *pa = headA, *pb = headB;
        while (pa != pb) {
            pa = (pa ? pa->next : headB);
            pb = (pb ? pb->next : headA);
        }
        return pa;
    }
};

int main() {
    // Build two lists with intersection at value 8 like LeetCode sample:
    // A = [4,1] + [8,4,5]
    // B = [5,6,1] + [8,4,5]
    auto [headA, headB] = ListNodeUtils::constructWithIntersection({4,1}, {5,6,1}, {8,4,5});

    Solution sol;
    ListNode* inter = sol.getIntersectionNode(headA, headB);

    if (inter) {
        cout << "Intersection at node with value: " << inter->val << endl;
    } else {
        cout << "No intersection" << endl;
    }

    // Clean up to avoid memory leaks
    ListNodeUtils::destroyTwoWithIntersection(headA, headB, inter);
    return 0;
}