/*
 * @lc app=leetcode.cn id=207 lang=java
 *
 * [207] 课程表
 */

// @lc code=start
import java.util.*;
class Solution {
    public boolean canFinish(int numCourses, int[][] prerequisites) {
        // 入度数组
        int[] indegree = new int[numCourses];
        // 邻接表
        List<Integer>[] graph = new List[numCourses];
        for (int i = 0; i < numCourses; i++) {
            graph[i] = new ArrayList<>();
        }
        
        // 构建图和入度
        for (var prerequisite : prerequisites) {
            graph[prerequisite[1]].add(prerequisite[0]);
            indegree[prerequisite[0]]++;
        }
        
        // 队列存储入度为0的课程
        Queue<Integer> q = new LinkedList<>();
        for (int i = 0; i < numCourses; i++) {
            if (indegree[i] == 0) {
                q.offer(i);
            }
        }
        
        int count = 0;
        while (!q.isEmpty()) {
            int course = q.poll();
            count++;
            for (int next : graph[course]) {
                indegree[next]--;
                if (indegree[next] == 0) {
                    q.offer(next);
                }
            }
        }
        
        return count == numCourses;
    }

    public static void main(String[] args) {
        var sol = new Solution();
        int numCourses = 2;
        int[][] preprequisites = {{1, 0}};
        System.out.println(sol.canFinish(numCourses, preprequisites));   
    }
}
// @lc code=end

