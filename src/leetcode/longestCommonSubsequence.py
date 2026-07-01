#
# @lc app=leetcode.cn id=1143 lang=python3
#
# [1143] 最长公共子序列
#

# @lc code=start
class Solution:
    def longestCommonSubsequence(self, text1: str, text2: str) -> int:
        if len(text1) < len(text2):
            text1, text2 = text2, text1
        
        m, n = len(text1), len(text2)                                                                                             
        # dp = [[0] * (n + 1) for _ in range(m + 1)]
        dp = [0] * (n + 1)                                             
                                                                                     
        for i in range(1, m + 1):   
            prev = 0                                                                                     
            for j in range(1, n + 1): 
                temp = dp[j]                                                                                            
                if text1[i-1] == text2[j-1]:                                                                                      
                   dp[j] = prev + 1                                                 
                else:                                                                                                             
                   dp[j] = max(dp[j-1], temp)                                         
                prev = temp        
                                                                                                                             
        return dp[n]
        
# @lc code=end

def main():
    sol = Solution()
    text1 = "bl"
    text2 = "yby"
    print(sol.longestCommonSubsequence(text1, text2))
    
if __name__ == "__main__":
    main()