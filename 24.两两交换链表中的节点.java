/*
 * @lc app=leetcode.cn id=24 lang=java
 *
 * [24] 两两交换链表中的节点
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
    public ListNode swapPairs(ListNode head) {
        ListNode dummy = new ListNode(-1, head);
        ListNode watcher = new ListNode(-2, dummy);
        ListNode cur1 = watcher, cur2 = dummy;
        ListNode prev = watcher;
        while (cur1 != null && cur2 != null) {
            prev.next = cur2;
            prev = cur1;
            cur1.next = cur2.next;
            cur2.next = cur1;
            cur1 = cur1.next;
            if (cur1 != null) {
                cur2 = cur1.next;
            }
        }
        return watcher.next;
    }

    public static void main(String[] args) {
        Solution solution = new Solution();
        ListNode head = new ListNode(1, new ListNode(2, new ListNode(3, new ListNode(4))));
        ListNode result = solution.swapPairs(head);
        System.out.print("Swapped Pairs: ");
        while (result != null) {
            System.out.print(result.val + " ");
            result = result.next;
        }
    }
}
// @lc code=end

