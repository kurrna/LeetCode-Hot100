/*
 * @lc app=leetcode.cn id=2 lang=java
 *
 * [2] 两数相加
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
    public ListNode addTwoNumbers(ListNode l1, ListNode l2) {
        ListNode dummy = new ListNode(0);
        dummy.next = l1;
        ListNode p1 = l1, p2 = l2, prev = dummy;
        int carry = 0;
        while (p1 != null || p2 != null) {
            int x = (p1 != null) ? p1.val : 0;
            int y = (p2 != null) ? p2.val : 0;
            int sum = x + y + carry;
            carry = sum / 10;
            if (p1 != null) {
                p1.val = sum % 10;
                prev = p1;
                p1 = p1.next;
            } else {
                prev.next = new ListNode(sum % 10);
                prev = prev.next;
            }
            if (p2 != null) {
                p2 = p2.next;
            }
        }
        if (carry > 0) {
            prev.next = new ListNode(carry);
        }
        return dummy.next;
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        ListNode l1 = new ListNode(2, new ListNode(4, new ListNode(3)));
        ListNode l2 = new ListNode(5, new ListNode(6, new ListNode(4)));
        ListNode result = sol.addTwoNumbers(l1, l2);
        while (result != null) {
            System.out.print(result.val + " ");
            result = result.next;
        }
    }
}
// @lc code=end

