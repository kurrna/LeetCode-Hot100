/*
 * @lc app=leetcode.cn id=160 lang=java
 *
 * [160] 相交链表
 */

// @lc code=start
/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode(int x) {
 *         val = x;
 *         next = null;
 *     }
 * }
 */
class Solution {
    public ListNode getIntersectionNode(ListNode headA, ListNode headB) {
        if (headA == null || headB == null) {
            return null;
        }
        ListNode pA = headA, pB = headB;
        while (pA != pB) {
            pA = pA == null ? headB : pA.next;
            pB = pB == null ? headA : pB.next;
        }
        return pA;
    }

    public static void main(String[] args) {
        Solution solution = new Solution();
        ListNode headA = new ListNode(4, new ListNode(1, new ListNode(8, new ListNode(4, new ListNode(5)))));
        ListNode headB = new ListNode(5, new ListNode(0, new ListNode(1, headA.next.next)));
        ListNode intersectionNode = solution.getIntersectionNode(headA, headB);
        if (intersectionNode != null) {
            System.out.println("相交节点的值: " + intersectionNode.val);
        } else {
            System.out.println("没有相交节点");
        }
    }
}
// @lc code=end

