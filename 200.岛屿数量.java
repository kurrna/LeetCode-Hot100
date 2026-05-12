/*
 * @lc app=leetcode.cn id=200 lang=java
 *
 * [200] 岛屿数量
 */

// @lc code=start
class Solution {
    public int numIslands(char[][] grid) {
        int m = grid.length;
        if (m == 0) return 0;
        int n = grid[0].length;
        var obj = new UnionFind(m * n);

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == '1') {
                    obj.addCount();
                    int idx = i * n + j;
                    if (j + 1 < n && grid[i][j+1] == '1') {
                        int rightIdx = idx + 1;
                        obj.union(idx, rightIdx);
                    }
                    if (i + 1 < m && grid[i+1][j] == '1') {
                        int downIdx = idx + n;
                        obj.union(idx, downIdx);
                    }
                }
            }
        }

        return obj.getCount();
    }

    public static void main(String[] args) {
        var sol = new Solution();
        char[][] grid = {
            {'1', '1', '1', '1', '0'},
            {'1', '1', '0', '1', '0'},
            {'1', '1', '0', '0', '0'},
            {'0', '0', '0', '0', '0'}
        };
        System.out.println(sol.numIslands(grid));
    }
}

class UnionFind {
    int[] parent;
    int count;

    public UnionFind(int n) {
        parent = new int[n];
        count = 0;
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    public int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    public void union(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX == rootY) return;
        parent[rootX] = rootY;
        count--;
    }

    public void addCount() {
        count++;
    }

    public int getCount() {
        return count;
    }
}
// @lc code=end

