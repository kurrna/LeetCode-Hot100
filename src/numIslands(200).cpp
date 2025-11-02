//
// Created by Kurna on 2025/11/2.
//
#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>
using namespace std;

class SolutionDFS {
public:
    void dfs(vector<vector<char >> &grid, int i, int j) {
        int nr = static_cast<int>(grid.size());
        int nc = static_cast<int>(grid[0].size());

        grid[i][j] = '0';
        if (i - 1 >= 0 && grid[i-1][j] == '1') dfs(grid, i - 1, j);
        if (i + 1 < nr && grid[i+1][j] == '1') dfs(grid, i + 1, j);
        if (j - 1 >= 0 && grid[i][j-1] == '1') dfs(grid, i, j - 1);
        if (j + 1 < nc && grid[i][j+1] == '1') dfs(grid, i, j + 1);
    }

    int numIslands(vector<vector<char> > &grid) {
        int nr = static_cast<int>(grid.size());
        if (!nr) return 0;
        int nc = static_cast<int>(grid[0].size());
        int num_islands = 0;
        for (int i = 0; i < nr; i++) {
            for (int j = 0; j < nc; j++) {
                if (grid[i][j] == '1') {
                    ++num_islands;
                    dfs(grid, i, j);
                }
            }
        }
        return num_islands;
    }
};

class SolutionBFS {
public:
    int numIslands(vector<vector<char>>& grid) {
        int nr = grid.size();
        if (!nr) return 0;
        int nc = grid[0].size();

        int num_islands = 0;
        for (int r = 0; r < nr; ++r) {
            for (int c = 0; c < nc; ++c) {
                if (grid[r][c] == '1') {
                    ++num_islands;
                    grid[r][c] = '0';
                    queue<pair<int, int>> neighbors;
                    neighbors.emplace(r, c);
                    while (!neighbors.empty()) {
                        auto [fst, snd] = neighbors.front();
                        neighbors.pop();
                        int row = fst, col = snd;
                        if (row - 1 >= 0 && grid[row-1][col] == '1') {
                            neighbors.emplace(row-1, col);
                            grid[row-1][col] = '0';
                        }
                        if (row + 1 < nr && grid[row+1][col] == '1') {
                            neighbors.emplace(row+1, col);
                            grid[row+1][col] = '0';
                        }
                        if (col - 1 >= 0 && grid[row][col-1] == '1') {
                            neighbors.emplace(row, col-1);
                            grid[row][col-1] = '0';
                        }
                        if (col + 1 < nc && grid[row][col+1] == '1') {
                            neighbors.emplace(row, col+1);
                            grid[row][col+1] = '0';
                        }
                    }
                }
            }
        }
        return num_islands;
    }
};

class UnionFind {
private:
    vector<int> parent;
    vector<int> rank;
    int count;
public:
    explicit UnionFind(vector<vector<char> > &grid) {
        count = 0;
        int m = grid.size();
        int n = grid[0].size();
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == '1') {
                    parent.push_back(i * n + j);
                    ++count;
                } else {
                    parent.push_back(-1);
                }
                rank.push_back(0);
            }
        }
    }

    int find(int i) {
        if (parent[i] != i) {
            parent[i] = find(parent[i]);
        }
        return parent[i];
    }

    void unite(int x, int y) {
        int rootx = find(x);
        int rooty = find(y);
        if (rootx != rooty) {
            if (rank[rootx] < rank[rooty]) {
                swap(rootx, rooty);
            }
            parent[rooty] = rootx;
            if (rank[rootx] == rank[rooty]) rank[rootx] += 1;
            --count;
        }
    }

    int getCount() const {
        return count;
    }
};

class SolutionUnion {
public:
    int numIslands(vector<vector<char> > &grid) {
        int m = grid.size();
        if (!m) return 0;
        int n = grid[0].size();

        UnionFind uf(grid);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == '1') {
                    grid[i][j]  = '0';
                    if (i - 1 >= 0 && grid[i-1][j] == '1') uf.unite(i * n + j, (i-1) * n + j);
                    if (i + 1 < m && grid[i+1][j] == '1') uf.unite(i * n + j, (i+1) * n + j);
                    if (j - 1 >= 0 && grid[i][j-1] == '1') uf.unite(i * n + j, i * n + (j-1));
                    if (j + 1 < n && grid[i][j+1] == '1') uf.unite(i * n + j, i * n + (j+1));
                }
            }
        }
        return uf.getCount();
    }
};

int main() {
    SolutionUnion sol;
    vector<vector<char> > input =
    {
        {'1', '1', '1', '1', '0'},
        {'1', '1', '0', '1', '0'},
        {'1', '1', '0', '0', '0'},
        {'0', '0', '0', '0', '0'}
    };
    cout << sol.numIslands(input) << endl;
    return 0;
}
