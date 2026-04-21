/*
 * @lc app=leetcode.cn id=138 lang=java
 *
 * [138] 随机链表的复制
 */

// @lc code=start
/*
// Definition for a Node.
class Node {
    int val;
    Node next;
    Node random;

    public Node(int val) {
        this.val = val;
        this.next = null;
        this.random = null;
    }
}
*/
import java.util.*;
class Solution {
    public Node copyRandomList(Node head) {
        Map<Node, Node> hm = new HashMap<>();
        Node curr = head;
        Node dull = new Node(-1);
        Node it = dull;
        while (curr != null) {
            it.next = new Node(curr.val);
            it = it.next;
            hm.put(curr, it);
            curr = curr.next;
        }
        curr = head;
        it = dull.next;
        while (curr != null) {
            it.random = hm.get(curr.random);
            curr = curr.next;
            it = it.next;
        }
        return dull.next;
    }

    public static void main(String[] args) {
        var sol = new Solution();
        var head = new Node(7);
        head.next = new Node(13);
        head.next.next = new Node(11);
        head.next.next.next = new Node(10); 
        head.next.next.next.next = new Node(1);
        head.random = null;
        head.next.random = head;
        head.next.next.random = head.next.next.next.next;
        head.next.next.next.random = head.next.next;
        head.next.next.next.next.random = head;
        var res = sol.copyRandomList(head);
        printRandomNodes(res);
    }

    private static void printRandomNodes(Node head) {
        var curr = head;
        while (curr != null) {
            System.out.println(curr.val + " -> " + (curr.random == null ? "null" : curr.random.val));
            curr = curr.next;
        }
    }
}
// @lc code=end

