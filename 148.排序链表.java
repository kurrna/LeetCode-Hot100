/*
 * @lc app=leetcode.cn id=148 lang=java
 *
 * [148] 排序链表
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
    public ListNode sortList(ListNode head) {
        if (head == null || head.next == null) {
            return head;
        }
        var slow = head;
        var fast = head;
        while (fast.next != null && fast.next.next != null) {
            slow = slow.next;
            fast = fast.next.next;
        }
        var mid = slow.next;
        slow.next = null;
        var left = sortList(head);
        var right = sortList(mid);
        return merge(left, right);
    }

    private ListNode merge(ListNode l, ListNode r) {
        var dummy = new ListNode();
        var tail = dummy;
        while (l != null && r != null) {
            if (l.val < r.val) {
                tail.next = l;
                l = l.next;
            } else {
                tail.next = r;
                r = r.next;
            }
            tail = tail.next;
        }
        if (l != null) {
            tail.next = l;
        } else {
            tail.next = r;
        }
        return dummy.next;
    }

    public static void main(String[] args) {
        var sol = new Solution();
        var head = new ListNode(4);
        head.next = new ListNode(2);
        head.next.next = new ListNode(1);
        head.next.next.next = new ListNode(3);
        var res = sol.sortList(head);
        while (res != null) {
            System.out.print(res.val + " ");
            res = res.next;
        }
        System.out.println();
    }
}
// @lc code=end

