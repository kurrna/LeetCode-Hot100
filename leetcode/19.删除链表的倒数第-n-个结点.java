/*
 * @lc app=leetcode.cn id=19 lang=java
 *
 * [19] 删除链表的倒数第 N 个结点
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
import java.util.*;
class Solution {
    public ListNode removeNthFromEnd(ListNode head, int n) {
        ListNode dummy = new ListNode(-1, head);
        ListNode fast = dummy, slow = dummy;
        for (int i = 0; i < n; i++) {
            fast = fast.next;
        }
        while (fast.next != null) {
            fast = fast.next;
            slow = slow.next;
        }
        slow.next = slow.next.next;
        return dummy.next;
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        List<ListNode> testCases = new ArrayList<>();
        testCases.add(new ListNode(1, new ListNode(2, new ListNode(3, new ListNode(4, new ListNode(5))))));
        testCases.add(new ListNode(1, new ListNode(2)));
        int[] ns = {2, 1};
        for (int i = 0; i < testCases.size(); i++) {
            ListNode result = sol.removeNthFromEnd(testCases.get(i), ns[i]);
            printList(result);
        }
    }

    private static void printList(ListNode head) {
        while (head != null) {
            System.out.print(head.val + " ");
            head = head.next;
        }
        System.out.println();
    }
}
// @lc code=end

