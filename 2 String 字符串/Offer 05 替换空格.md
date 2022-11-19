# 题目链接
[剑指Offer 05 替换空格](https://leetcode.cn/problems/ti-huan-kong-ge-lcof/?favorite=xb9nqhhg)

# 题干
请实现一个函数，把字符串 s 中的每个空格替换成"%20"。

# 示例：
```bash
输入：s = "We are happy."
输出："We%20are%20happy."
```

# 解题思路
经典数组“插入”题目，属于数组“增删改查”四大主要操作。
由于插入的值与原值的大小完全不同，有两种做法，一种是动态申请，“另起炉灶”；另一种是静态数组，“原地插入”。相比较第一种做法，原地插入的时间复杂度会很高。

# 程序实现
## 动态申请解法：
本题采取动态申请解法，主要分三步骤：
1. 统计原来字符串的空格数量；
2. 申请一个新的内存，长度是原有的长度加上两倍新的空格数量；
3. 分配快慢双指针，慢指针指向原数组，快指针指向现在数组，出现空格时候，快指针多移动两格并完成赋值。

```c
// 统计空格数量
int countSpace(char *s){
    int len = strlen(s);
    int count = 0;
    for(int i = 0; i < len; i++){
        if(*(s+i) == ' '){
            count++;
        }
    }
    return count;
}
// 动态申请内存，快慢指针填充值
char* replaceSpace(char* s){
    int len = strlen(s);
    int newLen = len + countSpace(s) * 2;
    char *str = (char *)malloc(sizeof(char) * newLen + 1);
    int iSlow = 0, iFast = 0;
    while (iSlow < len){
        if(s[iSlow] == ' '){
            str[iFast] = '%';
            str[iFast + 1] = '2';
            str[iFast + 2] = '0';
            iFast += 2;
        } else {
            str[iFast] = s[iSlow];
        }
        ++iSlow;
        ++iFast;
    }
    str[newLen] = '\0';
    return str;
}
```