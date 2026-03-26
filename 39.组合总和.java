/*
 * @lc app=leetcode.cn id=39 lang=java
 *
 * [39] 组合总和
 */

// @lc code=start
import java.util.*;
class Solution {
    public List<List<Integer>> combinationSum(int[] candidates, int target) {
        List<List<Integer>> res = new ArrayList<>();
        List<Integer> path = new ArrayList<>();
        Arrays.sort(candidates);
        backtrack(candidates, res, path, target, 0, 0);
        return res;
    }

    private void backtrack(int[] candidates, List<List<Integer>> res, List<Integer> path, int target, int sum, int index) {
        if (sum == target) {
            res.add(path.stream().toList());
            return;
        }
        for (int i = index; i < candidates.length; i++) {
            int num = candidates[i];
            if (sum + num > target) {
                break;
            }
            path.add(num);
            backtrack(candidates, res, path, target, sum + num, i);
            path.removeLast();
        }
    }

    public static void main(String[] args) {
        var sol = new Solution();
        var res = sol.combinationSum(new int[]{2, 3, 6, 7}, 7);
        for (var nums : res) {
            nums.stream().forEach(num -> System.out.print(num + " "));
            System.out.println();
        }
    }
}
// @lc code=end

final class Solution2 {
    public List<List<Integer>> combinationSum(int[] candidates, int target) {
        return new MyList(candidates, target);
    }

    static final class MyList extends AbstractList<List<Integer>> {

        final int[] candidates;
        final int target;
        long[][] nextMap;
        int[][] sizeMap;
        long next;
        int size;
        boolean init;

        MyList(int[] candidates, int target) {
            this.candidates = candidates;
            this.target = target;
        }

        void init() {
            nextMap = new long[target + 1][];
            sizeMap = new int[target + 1][];
            for (int i = target; i > 0; i--) {
                nextMap[i] = new long[candidates.length];
                sizeMap[i] = new int[candidates.length];
                Arrays.fill(nextMap[i], -1);
            }
            for (int start = 0; start < candidates.length; start++) {
                int startNext = find(target, start);
                if (startNext > 0) {
                    next |= 1L << start;
                    size += startNext;
                }
            }
        }

        int find(int target, int start) {
            if (nextMap[target][start] != -1) return sizeMap[target][start];
            int newTarget = target - candidates[start];
            if (newTarget == 0) {
                nextMap[target][start] = -2;
                sizeMap[target][start] = 1;
                return 1;
            } else {
                nextMap[target][start] = 0;
                if (newTarget < 0) return 0;
                int size = 0;
                for (int nextStart = start; nextStart < candidates.length; nextStart++) {
                    int nextSize = find(newTarget, nextStart);
                    if (nextSize > 0) {
                        nextMap[target][start] |= 1L << nextStart;
                        size += nextSize;
                    }
                }
                sizeMap[target][start] = size;
                return size;
            }
        }

        @Override
        public List<Integer> get(int index) {
            if (!init) init();
            List<Integer> res = new ArrayList<>();
            long curNext = next;
            int curTarget = target;
            do {
                int j = -1;
                for (int i = 0; i < candidates.length; i++) {
                    if ((curNext & (1L << i)) == 0) continue;
                    int curIndex = index - sizeMap[curTarget][i];
                    j = i;
                    if (curIndex < 0) break;
                    index = curIndex;
                }
                res.add(candidates[j]);
                curNext = nextMap[curTarget][j];
                if (curNext == -2) break;
                curTarget -= candidates[j];
            } while (true);
            return res;
        }

        @Override
        public int size() {
            if (!init) init();
            return size;
        }
    }
}
