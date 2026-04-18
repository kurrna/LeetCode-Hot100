/*
 * @lc app=leetcode.cn id=128 lang=java
 *
 * [128] 最长连续序列
 */

// @lc code=start
import java.util.*;

class Solution {
    public int longestConsecutive(int[] nums) {
        if (nums == null || nums.length == 0) return 0;

        Set<Integer> numSet = new HashSet<>();
        for (int num : nums) {
            numSet.add(num);
        }
        int longestStreak = 1;
        for (int num : numSet) {
            // 剪枝：只有当 num-1 不存在时，才从 num 开始向后找连续序列
            if (!numSet.contains(num - 1)) {
                int currentNum = num;
                int currentStreak = 1;

                while (numSet.contains(currentNum + 1)) {
                    currentNum++;
                    currentStreak++;
                }

                longestStreak = Math.max(longestStreak, currentStreak);
            }
        }
        return longestStreak;

        // Map<Integer, Integer> map = new HashMap<>();
        // for (int i = 0; i < nums.length; i++) {
        //     map.put(nums[i], i);
        // }

        // UnionFind uf = new UnionFind(nums.length);

        // for (int num : nums) {
        //     if (map.containsKey(num + 1)) {
        //         int idx1 = map.get(num);
        //         int idx2 = map.get(num + 1);
        //         uf.union(idx1, idx2);
        //     }
        // }

        // return uf.getMaxSize();


        // Arrays.sort(nums);
        // int maxLen = 1;
        // int currentLen = 1;
        // for (int i = 1; i < nums.length; i++) {
        //     if (nums[i] == nums[i - 1]) {
        //         continue;
        //     } else if (nums[i] == nums[i - 1] + 1) {
        //         currentLen++;
        //     } else {
        //         maxLen = Math.max(maxLen, currentLen);
        //         currentLen = 1;
        //     }
        // }
        // return Math.max(maxLen, currentLen);
    }

    public static void main(String[] args) {
        var sol = new Solution();
        int[] nums = {100, 4, 200, 1, 3, 2};
        System.out.println(sol.longestConsecutive(nums)); // 输出 4 ✔
    }
}

class UnionFind {
    int[] parent;
    int[] size;   // 真正的连通块大小
    int maxSize;  // 最大大小

    public UnionFind(int n) {
        parent = new int[n];
        size = new int[n];
        maxSize = 1;
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            size[i] = 1;
        }
    }

    public int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]); // 路径压缩
        }
        return parent[x];
    }

    public void union(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX == rootY) return;

        // 小集合挂到大集合上
        if (size[rootX] < size[rootY]) {
            parent[rootX] = rootY;
            size[rootY] += size[rootX];
            maxSize = Math.max(maxSize, size[rootY]);
        } else {
            parent[rootY] = rootX;
            size[rootX] += size[rootY];
            maxSize = Math.max(maxSize, size[rootX]);
        }
    }

    public int getMaxSize() {
        return maxSize;
    }
}
// @lc code=end

