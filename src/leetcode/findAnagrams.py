#
# @lc app=leetcode.cn id=438 lang=python3
#
# [438] 找到字符串中所有字母异位词
#

from typing import List

# @lc code=start
class Solution:
    def findAnagrams(self, s: str, p: str) -> List[int]:
        ans = []
        p_count = [0] * 26
        s_count = [0] * 26
        for c in p:
            p_count[ord(c) - ord('a')] += 1
        for i in range(len(s)):
            s_count[ord(s[i]) - ord('a')] += 1
            if i >= len(p):
                s_count[ord(s[i - len(p)]) - ord('a')] -= 1
            if s_count == p_count:
                ans.append(i - len(p) + 1)
        return ans
        
# @lc code=end

def main():
    sol = Solution()
    s = "cbaebabacd"
    p = "abc"
    print(sol.findAnagrams(s, p))
    
if __name__ == "__main__":
    main()