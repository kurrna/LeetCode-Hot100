#
# @lc app=leetcode.cn id=347 lang=python3
#
# [347] 前 K 个高频元素
#
from typing import List
import heapq
# @lc code=start
class Solution:
    def topKFrequent(self, nums: List[int], k: int) -> List[int]:
        cnt = {}
        for n in nums:
            cnt[n] = cnt.get(n, 0) + 1
        heap = []
        for num, freq in cnt.items():
            heapq.heappush(heap, (freq, num))
            if len(heap) > k:
                heapq.heappop(heap)
        return [num for (freq, num) in heap]
        
# @lc code=end

def main():
    sol = Solution()
    nums = [1, 1, 1, 1, 2, 2, 3]
    k = 2
    print(sol.topKFrequent(nums, k))
    
if __name__ == "__main__":
    main()