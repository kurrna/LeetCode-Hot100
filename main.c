#include <stdio.h>
#include <stdlib.h>

#include "twoSum.h"

// 测试用例函数
void test_twoSum()
{
    printf("==== 测试两数之和 ====\n");
    int nums[] = {2, 7, 11, 15};
    int target = 9;
    int returnSize;

    int *result = twoSum(nums, 4, target, &returnSize);
    if (result)
    {
        printf("结果: [%d, %d]\n", result[0], result[1]);
        free(result); // 释放动态分配的内存
    }
    else
    {
        printf("未找到解\n");
    }
}

int main()
{
    // 运行所有测试用例
    test_twoSum();
    // printf("hello world\n");

    return 0;
}