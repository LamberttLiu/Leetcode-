# 题目链接
[剑指 Offer 03. 数组中重复的数字](https://leetcode.cn/problems/shu-zu-zhong-zhong-fu-de-shu-zi-lcof/)

# 题干
找出数组中重复的数字。
在一个长度为 n 的数组 nums 里的所有数字都在 0～n-1 的范围内。数组中某些数字是重复的，但不知道有几个数字重复了，也不知道每个数字重复了几次。请找出数组中任意一个重复的数字。

# 示例
```txt
输入：
[2, 3, 1, 0, 2, 5, 3]
输出：2 或 3 
```
# 解题思路
```c
int cmp(const void *a,const void *b){
    return (*(int*)a - *(int*)b);
}

int findRepeatNumber(int* nums, int numsSize){
    qsort(nums, numsSize, sizeof(int), cmp);
    int iFast = 1, iSlow = 0;
    int ret;
    while(iFast < numsSize && iSlow < numsSize){
        if (nums[iFast] == nums[iSlow]){
            ret = nums[iFast];
            break;
        } else {
            iFast++;
            iSlow++;
        }
    }
    return ret;
}
```