#
# @lc app=leetcode.cn id=394 lang=python3
#
# [394] 字符串解码
#

# @lc code=start
class Solution:
    def decodeString(self, s: str) -> str:
        num_stk, str_stk = [], []
        cur_str, cur_num = "", 0
        for c in s:
            if c.isdigit():
                cur_num = cur_num * 10 + int(c)
            elif c == '[':
                num_stk.append(cur_num)
                str_stk.append(cur_str)
                cur_num, cur_str = 0, ""
            elif c == ']':
                repeat = num_stk.pop()
                prev = str_stk.pop()
                cur_str = prev + cur_str * repeat
            else:
                cur_str += c
        return cur_str
            
        
# @lc code=end

def main():
    sol = Solution()
    s = "3[a]2[bc]"
    print(sol.decodeString(s))
    
if __name__ == "__main__":
    main()