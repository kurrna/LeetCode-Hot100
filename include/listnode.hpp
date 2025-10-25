#pragma once
#include <vector>
#include <cassert>
#include <utility>   // for std::pair
#include <tuple>     // for std::tuple
#include <iterator> // for std::forward_iterator_tag

#define LIST_NODE
#ifdef LIST_NODE

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    explicit ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class ListNodeUtils {
public:
    // Construct a singly-linked list from a vector of ints.
    // Returns the head of the new list, or nullptr if the input is empty.
    static ListNode *construct(const std::vector<int>& arr) {
        if (arr.empty()) return nullptr;
        auto *head = new ListNode(arr[0]);
        ListNode *tail = head;
        for (size_t i = 1; i < arr.size(); ++i) {
            assert(tail != nullptr); // defensive: tail should never be null here
            tail->next = new ListNode(arr[i]);
            tail = tail->next;
        }
        return head;
    }

    // Optionally, add a helper to delete a list created by construct to avoid leaks.
    static void destroy(ListNode *head) {
        while (head) {
            ListNode *next = head->next;
            delete head;
            head = next;
        }
    }

    // Build two singly-linked lists that share the same tail (an actual intersection by node address).
    // aPrefix: values unique to list A before the intersection
    // bPrefix: values unique to list B before the intersection
    // commonTail: values for the shared tail starting at the intersection node
    // Returns {headA, headB}. If commonTail is empty, lists do not intersect.
    static std::pair<ListNode*, ListNode*> constructWithIntersection(
        const std::vector<int>& aPrefix,
        const std::vector<int>& bPrefix,
        const std::vector<int>& commonTail);

    // LeetCode-style builder using skip indices into the final lists to designate where the intersection starts.
    // Given full values for A and B, create lists so that A's node at index skipA is the intersection with B's node at index skipB.
    // Returns {headA, headB, intersection} (intersection may be nullptr if indices are invalid).
    static std::tuple<ListNode*, ListNode*, ListNode*> constructWithIntersectionByIndex(
        const std::vector<int>& aVals,
        const std::vector<int>& bVals,
        int skipA,
        int skipB);

    // Safely destroy two lists that share a common tail. Provide the intersection pointer to avoid double free.
    static void destroyTwoWithIntersection(ListNode* headA, ListNode* headB, ListNode* intersection);

    // Demo helper: construct a sample pair of intersecting lists, print brief info, and return {headA, headB, intersection}.
    // This is useful for small local tests.
    static std::tuple<ListNode*, ListNode*, ListNode*> demoConstructIntersection();
};

class ListIterator {
public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = int;
    using difference_type = std::ptrdiff_t;
    using pointer = int*;
    using reference = int&;

    ListIterator(ListNode* node) : current(node) {}

    reference operator*() const { return current->val; }
    pointer operator->() const { return &current->val; }

    ListIterator& operator++() {
        current = current->next;
        return *this;
    }

    ListIterator operator++(int) {
        ListIterator tmp = *this;
        ++(*this);
        return tmp;
    }

    bool operator==(const ListIterator& other) const {
        return current == other.current;
    }

    bool operator!=(const ListIterator& other) const {
        return !(*this == other);
    }

private:
    ListNode* current;
};

class LinkedList {
    ListNode* head;
public:
    explicit LinkedList(ListNode* h) : head(h) {}
    ListIterator begin() { return {head}; }
    ListIterator end() { return {nullptr}; }
};

#endif LIST_NODE

