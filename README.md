> javac -d classpath *.java
> java -cp classpath Solution

## 1.两数之和

- 哈希表

## 2.两数相加

- 加一个哑节点

## 3.无重复字符的最长字串

- 用HashSet存储字母，滑动窗口求最大长度

## 4.寻找两个正序数组的中位数

- 将较长的数组放在后面，然后使用二分查找搜索两个数组的分割点：$O(log(min(m, n)))$
  ```java
  // 左侧元素的总数，若为奇数长度则包括中位数
  int totalLeft = (m + n + 1) / 2;
  while (l <= r) {
  	int mid1 = (r - l) / 2 + l;
  	int mid2 = totalLeft - mid1;
  	// mid1 和 mid2 分别是 nums1 和 nums2 两个数组的分割点
  	if (nums1[mid1] < nums2[mid2 - 1]) {
  		l = mid + 1;
  	} else {
  		r = mid - 1;
  	}
  }
  int i = l, j = totalLeft - i;
  // nums1 右侧最小数 nums1[i] >= nums2[j - 1] nums2 左侧最大数
  // nums1 左侧最大数 nums1[i-1] <= nums2[j] nums2 右侧最小数
  // 若为奇数长度，则答案为 max(nums1[i-1], nums2[j-1])
  // 若为偶数长度，则答案为 (max(nums1[i-1], nums2[j-1]) + min(nums1[i], nums2[j])) / 2
  ```

## 5.最长回文子串

- 动态规划
  - dp[i][j]: 表示字串 s[i...j] 是否为回文串
  - dp[j]: 节约空间的一维动态规划数组，dp[j - 1] 即为上一轮循环中的 dp[i+1][j-1]（从尾部开始循环）

## 11.接雨水

- 双指针：每次移动值较小的指针
  - 反证法：如果保持值较小的指针不变，则在剩下的范围内移动较大的指针，其面积都小于移动之前的面积

## 15.三数之和

- 双指针：排序后通过跳过重复的元素来防止出现重复的三元组，注意剪枝

## 17.电话号码的字母组合

- 回溯：使用 char[] 来存储每个数字对应的字母，递归构建组合

## 19.删除链表的倒数第-n-个结点

- 快慢指针：快指针先移动 n 步，然后快指针慢指针同时移动直到快指针到达尾部

## 20.有效的括号

- 栈：左括号压栈，右括号出栈

## 21.合并两个有序链表

- 请输入文字

## 22.括号生成

- 回溯：使用 open 和 close 记录括号状态，开则添加右括号，闭且未达到目标括号对数则添加左括号

## 23.合并 k 个升序链表

- 最小堆：时间复杂度 $O(kn log(k))$

## 24.两两交换链表中的节点

- 哑节点

## 25.k 个一组翻转链表

- 先检查剩余节点个数是否不足 k 个，若足够，则翻转 k 个
  - 翻转链表

    ```java
    ListNode[] reverse(ListNode head, ListNode tail) {
        ListNode cur = head, prev = null;
        while (cur.next != null) {
    	ListNode next = cur.next;
       	cur.next = prev;
    	prev = cur;
    	cur = next;
        }
        return new ListNode[]{tail, next};
    }
    ```

## 31.下一个排列

- 从后往前找第一个导致逆序的数 nums[i]（nums[i] < nums[i+1]），再从后往前找第一个比 nums[i] 大的数 nums[j]，交换这两个数后再使用双指针翻转 nums[i+1] 到结尾即可

## 32.最长有效括号

- 动态规划：dp[i] 表示前 i 个字符中最大有效括号长度

  ```java
  for (int i = 1; i < n; i++) {
      if (s.charAt(i) == ')') {
  	if (i > 0 && s.charAt(i-1) == '(') {
  	    // 结束部分是一个"()"，长度+2
  	    dp[i] = (i >= 2 ? dp[i-2] : 0) + 2;
  	} else if (i - dp[i-1] > 0 && s.charAt(i - dp[i-1] -1) == '(') {
  	    // 结尾部分是一个"))"，那么当 dp[i-dp[i-1]-1] 为 '('
  	    // 那么相当于用一个更大的括号把之前最长的有效括号序列括起来，所以长度+2
  	    // 最后还要加上这个新的大括号序列之前的
  	    dp[i] = dp[i-1] + 2 + (i - dp[i-1] >=2 ? dp[i-dp[i-1]-2] : 0);
  	}
  	maxLen = Math.max(dp[i], maxLen);
      }
  }
  ```
- 栈：保持栈底元素为当前最后一个没有被匹配的右括号下标

  ```java
  stack.push(-1);
  for (int i = 0; i < s.length(); i++) {
      if (s.charAt(i) == '(') {
  	stack.push(i);
      } else {
  	stack.pop();
  	if (stack.isEmpty()) {
  	    // 表示当前右括号为没有匹配的右括号
  	    // 将其脚标放入栈中来表示最后一个没有被匹配的右括号下标
  	    stack.push(i);
  	} else {
  	    // 若不为空则当前有效括号长度为当前下标减去栈顶元素下标
  	    maxLen = Math.max(maxLen, i - stack.peek());
  	}
      }
  }
  ```
- 使用 left 计算左括号数量，right 计算右括号数量

  - 从左到右遍历，若 right 大于 left 则归零，若相等则更新 maxLen
  - 从右到左遍历，若 left 大于 right 则归零，若相等则更新 maxLen

## 33.搜索旋转排序数组

- 修改版二分查找：若nums[left] <= nums[mid]则，说明左段有序，检查target是否在左段；反之则右段有序，检查target是否在右段

## 34.在排序数组中查找元素的起始与结束位置

- 两次二分查找

## 35.搜索插入位置

- 二分查找

## 37.解数独

- 回溯：遍历数独每一个格子，用9个数字都试一遍后用'.'回溯
  - 剪枝：在填数字前先检查是否该格子这个数字是否有效
- 启发式算法（MRV）：优先从剩余的可能填法最少的那个格子开始

## 39.组合总和

- 回溯

## 40.组合总和-ii

- 回溯：使用 `if (i > index + 1 && candidates[i] == candidates[i-1]) continue;`来进行剪枝和去重

## 41.缺失的第一个正数

- 先遍历一遍把所有小于1的数设置为n+1；再遍历一遍，若有[1,n]内的数 nums[i]，则将 nums[nums[i]-1]设置为负数；最后遍历一遍，第一个不为负数的数位置加1即为所求

## 42.接雨水

- 动态规划：从左边遍历一遍维护一个 leftMax 数组，leftMax[i] 表示从左边起前 i 个位置高度最大值，再从右边遍历创建一个 rightMax 数组，然后下标 i 处能接的雨水量等于Math.min(leftMax[i], rightMax[i]) - height[i]
- 双指针：优化了上面的做法，左边的指针维护一个 leftMax 变量，右边的指针维护 rightMax，移动对应min(leftMax, rightMax)较小的一个对应的指针直到两个指针相遇

## 45.跳跃游戏-ii

- 贪心算法：使用两个变量分别计算当前下标对应元素所能跳到的最远位置和当前cnt步数能到达的最远位置，每次超过当前步数所能到达的最大位置则cnt+1，直到到达终点

## 46.全排列

- 回溯：用一个数组记录用过的数

## 47.全排列-ii

- 搜索回溯：相比于46题，本题需要对排列去重，因此要进行剪枝
  - `if (visited[i] || (i > 0 && nums[i-1] == nums[i] && !visited[i-1])) continue;`
    意思是当我们遇到重复的数字时，只允许他们以固定的相对顺序出现，最后一个条件 `!visited[i-1]`表示在回溯树中同层剪枝，表示同回溯层中如果前面的结果相同就跳过
  - `if (visited[i] || (i > 0 && nums[i-1] == nums[i] && visited[i-1])) continue;`
    两种剪枝最后答案相同，但是前者优于这种，因为，前者为同层剪枝，这种为非同层剪枝，在进入子树时才进行剪枝，时机较晚，性能更差

## 48.旋转图像

- 顺时针旋转90°：将矩阵分为四个区域，遍历单个区域内的点，每个点跟其他区域里的点交换位置，对于点 matrix[row][col]，其旋转 90°后对应点为 matrix[col][n-row-1]，因此对于点 matrix[i][j]，其余三个对应点分别为 matrix[j][n - i -1]、matrix[n - i - 1][n - j - 1]、matrix[n - j - 1][i]
  ```java
  for (int i = 0; i < n / 2; i++) {
      for (int j = 0; j < (n + 1) / 2; j++) {
  	int temp = matrix[i][j];
  	matrix[i][j] = matrix[n - 1 - j][i];
  	matrix[n - 1 - j][i] = matrix[n - 1 - i][n - 1 - j];
  	matrix[n - 1 - i][n - 1 - j] = matrix[j][n - 1 - i];
  	matrix[j][n - 1 - i] = temp;
      }
  }
  ```

## 49.字母异位词分组

- 将单词排序后当作哈希表的 key，分组后的list当作哈希表的 value

## 50.pow(x, n)

- 快速幂：注意边界条件（-2147483648的负数仍为-2147483648，因此要用long）
  ```java
  double quickMul(int x, long n) {
      if (n == 0) return 1.0;
      double y = quickMul(x, n);
      return n % 2 == 0 ? y * y : y * y * x;
  }
  ```

## 51.n皇后

- 回溯：遍历格子，若有效则填'Q'，递归调用检查下一行后'.'回溯
  - 剪枝：横竖左对角右对角

## 52.n皇后-ii

- 回溯：使用位运算优化有效性判断

## 53.最大子数组和

- 动态规划：当前子数组和 pre = max(dp[i] + nums[i], nums[i])，最大子数组和 maxSum = max(maxSum, pre)
