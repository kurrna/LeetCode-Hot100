#
# @lc app=leetcode.cn id=763 lang=python3
#
# [763] 划分字母区间
#
from typing import List
# @lc code=start
class Solution:
    def partitionLabels(self, s: str) -> List[int]:
        ans = []
        last = {c: i for i, c in enumerate(s)}
        cur = start = end = 0
        while end < len(s) and cur < len(s):
            end = max(last[s[cur]], cur)
            for j in range(start, end + 1):
                if last[s[j]] > end:
                    cur = j
                    break
                if j == end: 
                    ans.append(end - start + 1)
                    cur = start = end + 1
        return ans
# @lc code=end

def main():
    sol = Solution()
    s = "ababcbacadefegdehijhklij"
    print(sol.partitionLabels(s))
    
if __name__ == "__main__":
    main()