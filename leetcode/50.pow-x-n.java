/*
 * @lc app=leetcode.cn id=50 lang=java
 *
 * [50] Pow(x, n)
 */

// @lc code=start
class Solution {
    public double myPow(double x, int n_original) {
        Long n = (long) n_original;
        if (n < 0) {
            x = 1 / x;
            n = -n;
        }
        double res = 1.0;
        double current_product = x;
        for (Long i = n; i > 0; i /= 2) {
            if ((i % 2) == 1) {
                res *= current_product;
            }
            current_product *= current_product;
        }
        return res;
    }

    public static void main(String[] args) {
        var sol = new Solution();
        double x = 2.00000;
        int n = Integer.MIN_VALUE;
        var res = sol.myPow(x, n);
        System.out.println(String.format("%.5f", res));
    }
}
// @lc code=end

