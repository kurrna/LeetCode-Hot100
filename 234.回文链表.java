/*
 * @lc app=leetcode.cn id=234 lang=java
 *
 * [234] 回文链表
 */

// @lc code=start
/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode() {}
 *     ListNode(int val) { this.val = val; }
 *     ListNode(int val, ListNode next) { this.val = val; this.next = next; }
 * }
 */
class Solution {
    public boolean isPalindrome(ListNode head) {
        if (head == null || head.next == null) return true;
        ListNode dummy = new ListNode(-1, head);
        ListNode fast = dummy, slow = dummy;
        while (fast.next != null) {
            slow = slow.next;
            fast = fast.next;
            if (fast.next != null) {
                fast = fast.next;
            } else {
                break;
            }
        }
        ListNode prev = slow.next;
        ListNode next = slow.next.next;
        prev.next = null;
        slow.next = null;
        while (next != null) {
            var nx = next.next;
            next.next = prev;
            prev = next;
            next = nx;
        }
        ListNode cur = head;
        while (fast != null && cur != null) {
            if (fast.val != cur.val) {
                return false;
            }
            fast = fast.next;
            cur = cur.next;
        }
        return true;
    }

    public static void main(String[] args) {
        var sol = new Solution();
        var head = new ListNode(1, new ListNode(3, new ListNode(2, new ListNode(1))));
        System.out.println(sol.isPalindrome(head));
    }
}
// @lc code=end

