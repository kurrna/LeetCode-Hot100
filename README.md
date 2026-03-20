> javac -d target *.java
> java -cp target Solution

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
