#
# @lc app=leetcode.cn id=295 lang=python3
#
# [295] 数据流的中位数
#
import heapq
# @lc code=start
class MedianFinder:
    def __init__(self):
        self.left = list()
        self.right = list()

    def addNum(self, num: int) -> None:
        heapq.heappush(self.left, -num)
        max_left = -heapq.heappop(self.left)
        heapq.heappush(self.right, max_left)
        if len(self.right) > len(self.left):
            min_right = heapq.heappop(self.right)
            heapq.heappush(self.left, -min_right)

    def findMedian(self) -> float:
        if len(self.left) > len(self.right):
            return -self.left[0]
        
        return (-self.left[0] + self.right[0]) / 2.0


# Your MedianFinder object will be instantiated and called as such:
# obj = MedianFinder()
# obj.addNum(num)
# param_2 = obj.findMedian()
# @lc code=end

def main():
    sol = MedianFinder()
    sol.addNum(1)
    sol.addNum(3)
    print(sol.findMedian())
    sol.addNum(4)
    print(sol.findMedian())
    
if __name__ == "__main__":
    main()