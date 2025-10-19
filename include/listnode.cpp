// filepath: c:\Users\Kurna\Desktop\hot100\include\listnode.cpp
#include <listnode.hpp>
#include <vector>
#include <tuple>
#include <utility>
#include <cassert>

// Helper to append a vector to an existing list and return new tail.
static ListNode* appendValues(ListNode* tail, const std::vector<int>& vals) {
    for (size_t i = 0; i < vals.size(); ++i) {
        ListNode* node = new ListNode(static_cast<int>(vals[i]));
        if (tail) {
            tail->next = node;
        }
        tail = node;
    }
    return tail;
}

std::pair<ListNode*, ListNode*> ListNodeUtils::constructWithIntersection(
    const std::vector<int>& aPrefix,
    const std::vector<int>& bPrefix,
    const std::vector<int>& commonTail) {

    // Build shared tail first (if any)
    ListNode* sharedHead = nullptr;
    ListNode* sharedTail = nullptr;
    if (!commonTail.empty()) {
        sharedHead = new ListNode(commonTail[0]);
        sharedTail = sharedHead;
        for (size_t i = 1; i < commonTail.size(); ++i) {
            sharedTail->next = new ListNode(commonTail[i]);
            sharedTail = sharedTail->next;
        }
    }

    // Build A prefix
    ListNode* headA = nullptr;
    ListNode* tailA = nullptr;
    if (!aPrefix.empty()) {
        headA = new ListNode(aPrefix[0]);
        tailA = headA;
        for (size_t i = 1; i < aPrefix.size(); ++i) {
            tailA->next = new ListNode(aPrefix[i]);
            tailA = tailA->next;
        }
    }
    // Attach shared tail to A
    if (headA == nullptr) {
        headA = sharedHead;
    } else {
        tailA->next = sharedHead;
    }

    // Build B prefix
    ListNode* headB = nullptr;
    ListNode* tailB = nullptr;
    if (!bPrefix.empty()) {
        headB = new ListNode(bPrefix[0]);
        tailB = headB;
        for (size_t i = 1; i < bPrefix.size(); ++i) {
            tailB->next = new ListNode(bPrefix[i]);
            tailB = tailB->next;
        }
    }
    // Attach shared tail to B
    if (headB == nullptr) {
        headB = sharedHead;
    } else {
        tailB->next = sharedHead;
    }

    return {headA, headB};
}

std::tuple<ListNode*, ListNode*, ListNode*> ListNodeUtils::constructWithIntersectionByIndex(
    const std::vector<int>& aVals,
    const std::vector<int>& bVals,
    int skipA,
    int skipB) {

    // Build A fully
    ListNode* headA = nullptr;
    ListNode* tailA = nullptr;
    if (!aVals.empty()) {
        headA = new ListNode(aVals[0]);
        tailA = headA;
        for (size_t i = 1; i < aVals.size(); ++i) {
            tailA->next = new ListNode(aVals[i]);
            tailA = tailA->next;
        }
    }

    // Find intersection node in A by index
    ListNode* intersection = nullptr;
    if (skipA >= 0) {
        int idx = 0;
        for (ListNode* p = headA; p != nullptr; p = p->next, ++idx) {
            if (idx == skipA) { intersection = p; break; }
        }
    }

    // If intersection index invalid, just build independent B and return no intersection
    if (!intersection) {
        ListNode* headB = nullptr;
        ListNode* tailB = nullptr;
        if (!bVals.empty()) {
            headB = new ListNode(bVals[0]);
            tailB = headB;
            for (size_t i = 1; i < bVals.size(); ++i) {
                tailB->next = new ListNode(bVals[i]);
                tailB = tailB->next;
            }
        }
        return {headA, headB, nullptr};
    }

    // Build B prefix up to skipB (exclusive), then attach intersection
    ListNode* headB = nullptr;
    ListNode* tailB = nullptr;
    if (skipB <= 0) {
        headB = intersection; // B starts from intersection directly
    } else {
        // Ensure there are at least skipB items for B's prefix; if not, we still create prefix of available items
        int built = 0;
        if (!bVals.empty()) {
            headB = new ListNode(bVals[0]);
            tailB = headB;
            built = 1;
            while (built < skipB && static_cast<size_t>(built) < bVals.size()) {
                tailB->next = new ListNode(bVals[built]);
                tailB = tailB->next;
                ++built;
            }
        }
        if (headB == nullptr) {
            // No prefix possible, B begins at intersection regardless of requested skipB
            headB = intersection;
        } else {
            tailB->next = intersection;
        }
    }

    return {headA, headB, intersection};
}

void ListNodeUtils::destroyTwoWithIntersection(ListNode* headA, ListNode* headB, ListNode* intersection) {
    // Delete unique prefix of A
    while (headA && headA != intersection) {
        ListNode* nxt = headA->next;
        delete headA;
        headA = nxt;
    }
    // Delete unique prefix of B
    while (headB && headB != intersection) {
        ListNode* nxt = headB->next;
        delete headB;
        headB = nxt;
    }
    // Delete the shared tail once
    if (intersection) {
        destroy(intersection);
    }
}

