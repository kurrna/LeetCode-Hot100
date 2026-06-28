#
# @lc app=leetcode.cn id=322 lang=python3
#
# [322] 零钱兑换
#
from typing import List
# @lc code=start
class Solution:
    def coinChange(self, coins: List[int], amount: int) -> int:
        max_val = amount + 1
        dp = [float('inf')] * (amount + 1)
        dp[0] = 0
        
        for money in range(1, amount + 1):
             for coin in coins:
                 if coin <= money:
                     dp[money] = min(dp[money], dp[money-coin] + 1)
        
        return dp[amount] if dp[amount] != float('inf') else -1 
        
# @lc code=end

def main():
    sol = Solution()
    coins = [1, 2, 5]
    amount = 11
    print(sol.coinChange(coins, 11))
    
if __name__ == "__main__":
    main()