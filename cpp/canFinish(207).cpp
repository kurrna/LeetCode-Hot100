//
// Created by Kurna on 2025/11/4.
//
#include <bits/stdc++.h>
using namespace std;

// 拓扑排序
class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int> > &prerequisites) {
        int m = prerequisites.size();
        if (!m) return true;
        vector<int> indegrees(numCourses, 0);
        vector<int> outdegrees(numCourses, 0);
        vector<int> output;
        queue<int> q;
        for (const auto &edges : prerequisites) {
            int u = edges[0];
            indegrees[u]++;
            int v = edges[1];
            outdegrees[v]++;
        }
        for (int i = 0; i < numCourses; i++) {
            if (indegrees[i] == 0) {
                q.push(i);
            }
        }
        while (!q.empty()) {
            int v = q.front(); q.pop();
            output.push_back(v);
            auto it = prerequisites.begin();
            while (outdegrees[v]) {
                if ((*it)[1] == v) {
                    int u = (*it)[0];
                    prerequisites.erase(it);
                    outdegrees[v]--;
                    if (--indegrees[u] == 0) {
                        q.push(u);
                    }
                } else {
                    ++it;
                }
            }
        }
        if (output.size() < numCourses) return false;
        return true;
    }
};

// 优化的拓扑排序 Topological sort
class optimizedTopologicalSort {
private:
    vector<vector<int> > edges;
    vector<int> visited;
    bool validation = true;
public:
    void dfs(int u) {
        visited[u] = 1;
        for (int v : edges[u] ) {
            if (visited[v] == 0) {
                dfs(v);
                if (!validation) {
                    return;
                }
            } else if (visited[v] == 1) {
                validation = false;
                return;
            }
        }
        visited[u] = 2;
    }

    bool canFinish(int numCourses, vector<vector<int> >  &prerequisites) {
        edges.resize(numCourses);
        visited.resize(numCourses);
        for (const auto &info :  prerequisites) {
            edges[info[1]].push_back(info[0]);
        }
        for (int i = 0; i <  numCourses && validation; i++) {
            if (!visited[i]) {
                dfs(i);
            }
        }
        return validation;
    }
};


int main() {
    Solution sol;
    vector<vector<int> > input = {{1, 4}, {2, 4}, {3, 1}, {3, 2}};
    cout << sol.canFinish(5, input) << endl;
    return 0;
}
