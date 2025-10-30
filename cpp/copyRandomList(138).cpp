//
// Created by Kurna on 25-10-29.
//
#include <iostream>
#include <unordered_map>
#include <vector>
#include <optional>
#include <string>
#include <sstream>
#include <limits>
using namespace std;

class Node {
public:
    int val;
    Node *next;
    Node *random;

    explicit Node(int _val) : val(_val), next(nullptr), random(nullptr) {}
};

class Solution {
public:
    // 现代 C++ 两趟哈希表写法：
    // 1) 第一趟按 next 克隆所有节点，建立 old->new 映射；
    // 2) 第二趟利用映射补齐 random。
    Node *copyRandomList(Node *head) {
        if (!head) return nullptr;
        unordered_map<Node*, Node*> mp;
        mp.reserve(128);

        // 第一趟：克隆线性 next 链并建立映射
        Node* dummy = new Node(0);
        Node* tail = dummy;
        for (Node* p = head; p; p = p->next) {
            Node* q = new Node(p->val);
            tail->next = q;
            tail = q;
            mp[p] = q;
        }

        // 第二趟：补齐 random 指针
        for (Node* p = head; p; p = p->next) {
            Node* q = mp[p];
            q->random = p->random ? mp[p->random] : nullptr;
        }

        Node* ans = dummy->next;
        delete dummy;
        return ans;
    }
};

class SolutionWithLowerSpaceComplexity {
public:
    Node* copyRandomList(Node* head) {
        if (head == nullptr) {
            return nullptr;
        }
        for (Node* node = head; node != nullptr; node = node->next->next) {
            Node* nodeNew = new Node(node->val);
            nodeNew->next = node->next;
            node->next = nodeNew;
        }
        for (Node* node = head; node != nullptr; node = node->next->next) {
            Node* nodeNew = node->next;
            nodeNew->random = (node->random != nullptr) ? node->random->next : nullptr;
        }
        Node* headNew = head->next;
        for (Node* node = head; node != nullptr; node = node->next) {
            Node* nodeNew = node->next;
            node->next = node->next->next;
            nodeNew->next = (nodeNew->next != nullptr) ? nodeNew->next->next : nullptr;
        }
        return headNew;
    }
};

// ===== 测试辅助：把 [[val,randomIndex/null],...] 的表示与链表互相转换 =====
// 输入表示：pair<val, randomIndex>，其中 randomIndex = -1 表示 null
static Node* buildRandomList(const vector<pair<int,int>>& spec) {
    if (spec.empty()) return nullptr;
    vector<Node*> nodes;
    nodes.reserve(spec.size());
    for (auto [v, _] : spec) nodes.push_back(new Node(v));
    for (size_t i = 0; i + 1 < nodes.size(); ++i) nodes[i]->next = nodes[i+1];
    for (size_t i = 0; i < spec.size(); ++i) {
        int ridx = spec[i].second;
        nodes[i]->random = (ridx >= 0 && static_cast<size_t>(ridx) < nodes.size()) ? nodes[ridx] : nullptr;
    }
    return nodes.front();
}

static vector<pair<int, optional<size_t>>> serializeRandomList(Node* head) {
    // 建立索引映射 newIndex: pointer -> index
    unordered_map<Node*, size_t> idx;
    idx.reserve(128);
    size_t i = 0;
    for (Node* p = head; p; p = p->next) idx[p] = i++;

    vector<pair<int, optional<size_t>>> out;
    out.reserve(i);
    for (Node* p = head; p; p = p->next) {
        if (p->random == nullptr) out.emplace_back(p->val, nullopt);
        else out.emplace_back(p->val, idx[p->random]);
    }
    return out;
}

static string toLeetCodeFormat(const vector<pair<int, optional<size_t>>>& a) {
    // 生成如 [[7,null],[13,0],...] 的字符串
    ostringstream oss;
    oss << "[";
    for (size_t i = 0; i < a.size(); ++i) {
        oss << "[" << a[i].first << ",";
        if (a[i].second.has_value()) oss << *a[i].second; else oss << "null";
        oss << "]";
        if (i + 1 < a.size()) oss << ",";
    }
    oss << "]";
    return oss.str();
}

static bool equalByStructure(Node* a, Node* b) {
    // 比较 val 序列及 random 的指向相对索引是否一致
    unordered_map<Node*, size_t> ia, ib;
    size_t i = 0;
    for (Node* p = a; p; p = p->next) ia[p] = i++;
    i = 0;
    for (Node* p = b; p; p = p->next) ib[p] = i++;

    Node* pa = a; Node* pb = b;
    while (pa && pb) {
        if (pa->val != pb->val) return false;
        size_t ra = pa->random ? ia[pa->random] : numeric_limits<size_t>::max();
        size_t rb = pb->random ? ib[pb->random] : numeric_limits<size_t>::max();
        if (ra != rb) return false;
        pa = pa->next; pb = pb->next;
    }
    return pa == nullptr && pb == nullptr;
}

static void freeList(Node* head) {
    while (head) {
        Node* tmp = head;
        head = head->next;
        delete tmp;
    }
}

int main() {
    // 用题面样例：head = [[7,null],[13,0],[11,4],[10,2],[1,0]]
    vector<pair<int,int>> spec = {
        {7, -1}, {13, 0}, {11, 4}, {10, 2}, {1, 0}
    };

    Node* head = buildRandomList(spec);

    Solution sol;
    Node* copied = sol.copyRandomList(head);

    // 序列化并打印，便于人工对比
    auto srcSer = serializeRandomList(head);
    auto dstSer = serializeRandomList(copied);

    cout << "input  : " << toLeetCodeFormat(srcSer) << "\n";
    cout << "output : " << toLeetCodeFormat(dstSer) << "\n";

    // 结构等价性校验 + 深拷贝地址不同性抽查
    bool sameStruct = equalByStructure(head, copied);
    bool deepCopy = (head != copied); // 至少头指针不同；更严格可逐一比较地址映射

    cout << (sameStruct && deepCopy ? "PASS" : "FAIL") << "\n";

    // 释放内存（原链表 + 拷贝链表）
    freeList(head);
    freeList(copied);

    return sameStruct && deepCopy ? 0 : 1;
}