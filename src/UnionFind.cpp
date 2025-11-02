//
// Created by Kurna on 2025/11/2.
//
#include <bits/stdc++.h>
using namespace std;

class UnionFind {
private:
    vector<int> parent;
    vector<int> rank;

public:
    UnionFind(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        // 初始化：每个元素的父节点是自身
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    // 查找父节点并压缩路径
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    // 按秩合并两个集合
    bool unite(int x, int y) {
        int rootX = find(x), rootY = find(y);
        if (rootX == rootY) return false;

        if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX; // 秩大的作为根
        } else if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY; // 秩大的作为根
        } else {
            // 秩相等时，任意合并（这里选rootX作为新根）
            parent[rootY] = rootX;
            rank[rootX]++; // 只有此时秩才会增加
        }
        return true;
    }
};

// 判断无向图是否存在环
bool hasCycle(const vector<pair<int, int> > &edges, int n) {
    auto uf = UnionFind(n);
    for (const auto &[fst, snd]: edges) {
        int u = fst, v = snd;
        if (uf.find(u) == uf.find(v)) {
            return true;
        }
        uf.unite(u, v);
    }
    return false;
}

int main() {
    // 示例1：存在环的图
    int n1 = 3; // 3个顶点
    vector<pair<int, int> > edges1 = {{0, 1}, {1, 2}, {0, 2}};
    cout << "图1" << (hasCycle(edges1, n1) ? "存在环" : "不存在环") << endl;

    // 示例2：不存在环的图
    int n2 = 4; // 4个顶点
    vector<pair<int, int> > edges2 = {{0, 1}, {1, 2}, {2, 3}};
    cout << "图2" << (hasCycle(edges2, n2) ? "存在环" : "不存在环") << endl;

    return 0;
}
