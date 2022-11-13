#define     HASH_SIZE   100

// 创建哈希表
// 元素定义
typedef struct
{
    int key;   // 键
    int value; // 值
} HashData;

// 二维哈希链表元素定义
typedef struct
{
    HashData *pNode; // 当前值
    HashNode *pNext; // 下一个指针，指针的自引用
} HashNode;

// 哈希表定义
typedef struct
{
    int iNodeSize;        // 存入元素个数
    HashNode **pHashHead; // Hash表指针
} HashTable;

// 函数一：哈希表初始化
bool HashTableInit(HashTable **pHashTable)
{
    (*pHashTable) = (HashTable *)malloc(sizeof(HashTable));
    if (NULL == (*pHashTable))
        return false;

    (*pHashTable)->iNodeSize = 0;
    (*pHashTable)->pHashHead = (HashNode **)malloc(sizeof(HashNode *) * HASH_SIZE);
    if (NULL == (*pHashTable)->pHashHead)
        return false;

    memset((*pHashTable)->pHashHead, 0x00, sizeof(HashNode *) * HASH_SIZE);
    return true;
}

//函数二：哈希表元素插入
//1，遇到相同的元素，则更新 value 值
bool hashTableInsert(struct Hash_Table* pHashTable, int key, int value){
    long                    iKey        = 0;
    struct Hash_Node*       pTmpNode    = NULL;
    struct HashListNode*    pNode       = NULL;

    pNode = (struct HashListNode*)malloc(sizeof(struct HashListNode));
    if(NULL == pNode) return false;
    pNode->key = key;
    pNode->val = value;

    iKey = (long)key;
    iKey = ABS(iKey) % HASH_SIZE;
    if(NULL == pHashTable->pHashHead[iKey])
    {
        pHashTable->pHashHead[iKey] = (struct Hash_Node*)malloc(sizeof(struct Hash_Node));
        if(NULL == pHashTable->pHashHead[iKey]) return false;

        pHashTable->pHashHead[iKey]->pNode = pNode;
        pHashTable->pHashHead[iKey]->pNext = NULL;
    }
    else
    {
        pTmpNode = pHashTable->pHashHead[iKey];
        while((NULL != pTmpNode) && (NULL != pTmpNode->pNext))
        {
            if(key == pTmpNode->pNode->key)
            {
                pTmpNode->pNode->val = value;
                return true;
            }
            pTmpNode = pTmpNode->pNext;
        }

        if(key == pTmpNode->pNode->key)
        {
            pTmpNode->pNode->val = value;
            return true;
        }
        else
        {
            pTmpNode->pNext = (struct Hash_Node*)malloc(sizeof(struct Hash_Node));
            if(NULL == pTmpNode->pNext) return false;

            pTmpNode = pTmpNode->pNext;
            pTmpNode->pNode = pNode;
            pTmpNode->pNext = NULL;
        }
    }
    pHashTable->iNodeSize += 1;
    return true;
}

//函数三：取出哈希表元素
struct Hash_Node* getHashNode(struct Hash_Table* pHashTable, int key){
    long                iKey        = 0;
    struct Hash_Node*   pTmpNode    = NULL;
    
    iKey = (long)key;
    iKey = ABS(iKey) % HASH_SIZE;
    pTmpNode = pHashTable->pHashHead[iKey];

    while(NULL != pTmpNode)
    {
        if((NULL != pTmpNode->pNode) && (key == pTmpNode->pNode->key))
        {
            return pTmpNode;
        }
        else
        {
            pTmpNode = pTmpNode->pNext;
        }
    }

    return NULL;
}

//函数四：hash表元素删除
bool hashTableDel(struct Hash_Table* pHashTable, int key){
    long                iKey        = 0;
    struct Hash_Node*   pTmpNode    = NULL;
    struct Hash_Node*   pNextNode   = NULL;

    if(NULL == pHashTable) return false;

    iKey = (long)key;
    iKey = ABS(iKey) % HASH_SIZE;
    pTmpNode = pHashTable->pHashHead[iKey];

    while(NULL != pTmpNode)
    {
        if((NULL != pTmpNode->pNode) && (key == pTmpNode->pNode->key))
        {
            pNextNode = pTmpNode->pNext;
            free(pTmpNode->pNode);
            pTmpNode->pNode = NULL;
            pTmpNode->pNext = pNextNode;
            pHashTable->iNodeSize -= 1;
            break;
        }
        else
        {
            pTmpNode = pTmpNode->pNext;
        }
    }

    return true;
}

//函数五：Hash表的释放
void freeHashTable(struct Hash_Table* pHashTable){
    int                 i           = 0;
    struct Hash_Node*   pTmpNode    = NULL;
    struct Hash_Node*   pNextNode   = NULL;

    if(NULL == pHashTable) return;

    for(i = 0; i < HASH_SIZE; i++)
    {
        pTmpNode = pHashTable->pHashHead[i];
        while(NULL != pTmpNode)
        {
            pNextNode = pTmpNode->pNext;
            if(NULL != pTmpNode->pNode)
            {
                free(pTmpNode->pNode);
                pTmpNode->pNode = NULL;
            }
            free(pTmpNode);
            pTmpNode = pNextNode;
        }
        pHashTable->pHashHead[i] = NULL;
    }
    return;
}

int majorityElement(int* nums, int numsSize){
    int     i       = 0;
    int     iRet    = 0;

    struct Hash_Node*       pTmpNode        = NULL;
    struct Hash_Table*      pHashTable      = NULL;

    if(false == hashTableInit(&pHashTable)) return -1;

    if(NULL == nums) return -1;
    if(numsSize < 2) return nums[0];

    for(i = 0; i < numsSize; i++)
    {
        pTmpNode = getHashNode(pHashTable, nums[i]);
        if(NULL == pTmpNode)
        {
             hashTableInsert(pHashTable, nums[i], 1);
        }
        else
        {
            pTmpNode->pNode->val += 1;

            if(pTmpNode->pNode->val > (numsSize / 2))
            {
                iRet = nums[i];
                break;
            }
        }
    }

    freeHashTable(pHashTable);
    pHashTable = NULL;
    return iRet;
}

