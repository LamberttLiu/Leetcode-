# 题目链接
# 题干
# 解题思路
# 程序实现
```c
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
// 链表逆置函数（头插法），需要熟记掌握
struct ListNode* ListReverse(struct ListNode* head)
{
	struct ListNode* new_head = NULL;
	struct ListNode* temp = NULL;//用于临时存储节点
	if (head == NULL || head->next == NULL)
		return head;
	while (head != NULL)
	{
		temp = head;
		//将 temp 从 head 中摘除
		head = head->next;
		//将 temp 插入到 new_head 的头部
		temp->next = new_head;
		new_head = temp;
	}
	return new_head;
}
// 求链表的表长
int Listsize(struct ListNode* head){
    int size = 0;
    struct ListNode *pList = head;
    while(pList != NULL){
        size++;
        pList = pList->next;
    }
    return size;
}
// 申请动态数组，逐个读取逆置后链表的数据域
int* reversePrint(struct ListNode* head, int* returnSize){
    int len = Listsize(head);
    struct ListNode* newHead = ListReverse(head);
    struct ListNode* temp = newHead;
    * returnSize = len;
    int *returnArr = (int *)malloc(sizeof(int) * len);
    for (int i = 0; i < len; i++){
        returnArr[i] = temp->val;
        temp = temp->next;
    }    
    return returnArr;
}
```