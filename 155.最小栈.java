/*
 * @lc app=leetcode.cn id=155 lang=java
 *
 * [155] 最小栈
 */

// @lc code=start
import java.util.*;
class MinStack {
    Stack<Integer> stk;
    Stack<Integer> minStk;

    public MinStack() {
        stk = new Stack<>();
        minStk = new Stack<>();
    }
    
    public void push(int val) {
        stk.push(val);
        if (minStk.isEmpty() || val <= minStk.peek()) {
            minStk.push(val);
        }
    }
    
    public void pop() {
        if (stk.pop().equals(minStk.peek())) {
            minStk.pop();
        }
    }
    
    public int top() {
        return stk.peek();
    }
    
    public int getMin() {
        return minStk.peek();
    }
}

class Main {
    public static void main(String[] args) {
        var obj = new MinStack();
        obj.push(-2);
        obj.push(0);
        obj.push(-3);
        System.out.println(obj.getMin()); // return -3
        obj.pop();
        System.out.println(obj.top());    // return 0
        System.out.println(obj.getMin()); // return -2
    }
}

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack obj = new MinStack();
 * obj.push(val);
 * obj.pop();
 * int param_3 = obj.top();
 * int param_4 = obj.getMin();
 */
// @lc code=end

