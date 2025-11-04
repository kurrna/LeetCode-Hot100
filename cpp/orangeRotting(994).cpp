//
// Created by Kurna on 2025/11/3.
//
#include <bits/stdc++.h>
using namespace std;

class Solution {
    int cnt = 0;
    int dis[10][10] = {0};
    int dir_x[4] = {0, 1, 0, -1};
    int dir_y[4] = {1, 0, -1, 0};
public:
    int orangesRotting(vector<vector<int> > &grid) {
        queue<pair<int, int>> q;
        cnt = 0;
        int ans = 0;
        memset(dis, -1, sizeof(dis));
        int m = static_cast<int>(grid.size()), n = static_cast<int>(grid[0].size());
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 2) {
                    q.emplace(i, j);
                    dis[i][j] = 0;
                } else if (grid[i][j] == 1) {
                    cnt++;
                }
            }
        }
        while (!q.empty()) {
            auto [fst, scd] = q.front(); q.pop();
            for (int i = 0; i < 4; i++) {
                int x = fst + dir_x[i];
                int y = scd + dir_y[i];
                if (x < 0 || x >= m || y < 0 || y >= n || ~dis[x][y] || !grid[x][y]) {
                    continue;
                }
                dis[x][y] = dis[fst][scd] + 1;
                q.emplace(x, y);
                if (grid[x][y] == 1) {
                    cnt--;
                    ans = dis[x][y];
                    if (!cnt) break;
                }
            }
        }
        return cnt ? -1 : ans;
    }
};

int main() {
    Solution sol;
    vector<vector<int> > grid = {
        {2,1,1},{1,1,0},{0,1,1}
    };
    int result = sol.orangesRotting(grid);
    cout << "Minutes until all oranges are rotten: " << result << endl;
    return 0;
}
