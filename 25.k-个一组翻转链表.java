/*
 * @lc app=leetcode.cn id=25 lang=java
 *
 * [25] K 个一组翻转链表
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
    public ListNode reverseKGroup(ListNode head, int k) {
        ListNode dummy = new ListNode(-1, head);
        ListNode pre = dummy, tail = dummy;
        while (tail.next != null) {
            for (int i = 0; i < k && tail != null; i++) {
                tail = tail.next;
            }
            if (tail == null) {
                break;
            }
            ListNode next = tail.next;
            ListNode[] reversed = reverse(pre.next, tail);
            pre.next = reversed[0];
            reversed[1].next = next;
            pre = reversed[1];
            tail = pre;
        }

        return dummy.next;
    }

    private ListNode[] reverse(ListNode head, ListNode tail) {
        ListNode pre = null, cur = head;
        while (pre != tail) {
            ListNode next = cur.next;
            cur.next = pre;
            pre = cur;
            cur = next;
        }
        return new ListNode[]{tail, head};
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        ListNode head = new ListNode(1, new ListNode(2, new ListNode(3, new ListNode(4, new ListNode(5)))));
        var res = sol.reverseKGroup(head, 2);
        while (res.next != null) {
            System.out.print(res.val + " ");
            res = res.next;
        }
        System.out.println(res.val);
    }
}
// @lc code=end

