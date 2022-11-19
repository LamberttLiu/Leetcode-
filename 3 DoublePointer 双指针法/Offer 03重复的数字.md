# 题目链接
[剑指 Offer 03. 数组中重复的数字](https://leetcode.cn/problems/shu-zu-zhong-zhong-fu-de-shu-zi-lcof/)

# 题干
找出数组中重复的数字。
在一个长度为 `n` 的数组 `nums` 里的所有数字都在 `0～n-1` 的范围内。数组中某些数字是重复的，但不知道有几个数字重复了，也不知道每个数字重复了几次。请找出数组中任意一个重复的数字。

# 示例
```txt
输入：
[2, 3, 1, 0, 2, 5, 3]
输出：2 或 3
```
# 解题思路
有三种方法：
- 第一种，使用**哈希散列**，对数组每个元素进行遍历，然后构建一个哈希表，再对哈希表迭代，查找`Value > 1`的key值，并返回。
- 第二种，使用**双指针**：直接排序，使用双指针遍历，快慢指针同步向前移动，一旦发现快指针所指的值和慢指针所指的值发生了相同，就把那个相同的值返回。
- 第三种，是在**双指针**的基础上进行了优化，直接使用**单指针**即可，如果该指针所指的值和这个指针下一个值相同，那么就把这个相同的值返回。

考虑哈希的实现开销较大，这里使用**双指针法**和**单指针法**。

# 程序实现
- 1. 双指针法
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

- 2. 单指针法
```c
int cmp(const void *a,const void *b){
    return (*(int*)a - *(int*)b);
}

int findRepeatNumber(int* nums, int numsSize){
    qsort(nums, numsSize, sizeof(int), cmp);
    int i = 0;
    int ret;
    while(i < numsSize - 1){
        if (nums[i] == nums[i + 1]){
            ret = nums[i];
            break;
        } 
        i++;
    }
    return ret;
}
```

## 类似的题目
- [1446. 连续字符](https://leetcode.cn/problems/consecutive-characters/)