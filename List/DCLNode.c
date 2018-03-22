#include<stdio.h>
#include<assert.h>
#include<stdlib.h>
#include"DCLNode.h"

void DCLInit(PNode* ppHead)    //双向链表的初始化
{
	*ppHead = DCLBuyNode(0);   //创建一个哨兵结点，给其值为零
	(*ppHead)->_pNext = (*ppHead);
	(*ppHead)->_pPre = (*ppHead);
}


PNode DCLBuyNode(DataType data)    //创建新结点
{
	PNode pNew = (PNode)malloc(sizeof(Node));
	pNew->_data = data;
	pNew->_pNext = NULL;
	pNew->_pPre = NULL;
	return pNew;
}



void DCLPushBack(PNode pHead, DataType data)  //尾插
{
	PNode pNew = DCLBuyNode(data);

	PNode pTail = pHead;    //pTail从pHead开始，不能从NULL开始
	PNode cur = pHead;
	
	assert(pHead);  //存在哨兵结点

	cur->_pPre->_pNext = pNew ;
	pNew->_pPre = cur->_pPre;
	pNew->_pNext = pHead;
	pHead->_pPre = pNew;
}

void DCLPopBack(PNode pHead)        //尾删
{

	PNode cur = pHead->_pNext;
	PNode pTail = pHead;
	assert(pHead);
	assert(pHead->_pNext != pHead);
	while (cur != pHead)
	{
		pTail = cur;
		cur = cur->_pNext;
	}
	pTail->_pPre->_pNext = pHead;
	pHead->_pPre = pTail->_pPre;
}


void DCLPushFront(PNode pHead, DataType data)  //头插
{
	PNode pNew = DCLBuyNode(data);
	pHead->_pNext->_pPre = pNew;
	pNew->_pNext = pHead->_pNext;
	pHead->_pNext = pNew;
	pNew->_pPre = pHead;
}


void DCLPopFront(PNode pHead)     //头删
{
	//assert(pHead);
	PNode del = NULL;
	if (pHead->_pNext == NULL)   //至少得有一个
	{
		printf("双向链表已经为空，不能再删除\n");
	}
	del = pHead->_pNext;
	pHead->_pNext = del->_pNext;
	free(del);
}

int DCLEmpty(PNode pHead)//判空
{
	return pHead->_pNext == pHead;
}

void DCLInsert(PNode pos, DataType data)   //任意位置的插入
{
	PNode pNew = DCLBuyNode(data);
	PNode pre = pos->_pPre;
	pre->_pNext = pNew;
	pNew->_pPre = pre;

	pNew->_pNext = pos;
	pos->_pPre = pNew;
}



void DCLErase(PNode pos)       //任意位置的删除
{
	PNode pre = NULL;
	PNode next = NULL;

	assert(pos);
	if (pos->_pNext == pos)
	{
		printf("双向链表已经为空，不能再删除\n");
	}
	pre = pos->_pPre;
    next = pos->_pNext;
	pre->_pNext = next;
	next->_pPre = pre;

	free(pos);
}



void DCLDestroy(PNode* ppHead)  //双向链表的销毁
{
	PNode cur = (*ppHead)->_pNext;
	while (cur != *ppHead)
	{
		PNode del = cur;
		cur = cur->_pNext;

		free(del);
	}
	free(*ppHead);
	*ppHead = NULL;
}



PNode DCLFind(PNode pHead, DataType data) //查找
{
	PNode cur = pHead->_pNext;
	while (cur != pHead)
	{
		if (cur->_data == data)
		{
			return cur;
		}
		cur = cur->_pNext;
	}
	return NULL;
}
size_t DCLSize(PNode pHead)//元素个数
{
	PNode cur = pHead;
	size_t count = 0;
	assert(pHead);
	while(cur->_pNext != pHead)
	{
		cur = cur->_pNext;
		count++;
	}
	return count;
}

void DCLNode_test()
{
	PNode n;    //定义结点为结构体指针类型
	PNode find = NULL;
	DCLInit(&n);
	DCLBuyNode(0); 
	printf("尾插::");
	DCLPushBack(n, 1);
	DCLPushBack(n, 2);
	DCLPushBack(n, 3);
	DCLPushBack(n, 4);
	DCLPushBack(n, 5);

	//printf("\n尾删::");
	//DCLPopBack(n);
	//DCLPopBack(n);
	//DCLPopBack(n);

	//printf("\n头插::");
	//DCLPushFront(n, 6);
	//DCLPushFront(n, 7);


	//printf("\n头删::");
	//DCLPopFront(n);
	//DCLPopFront(n);

	//printf("\n任意位置的插入::");
	//DCLInsert(DCLFind(n, 6), 8);
	//DCLInsert(DCLFind(n, 7), 9);

	//printf("\n任意位置的删除::");
	//DCLErase(DCLFind(n, 8));

	//find = DCLFind(n, 3);
	//printf("\n查找到结点数据为%d的结点地址为%p::", find->_data, find);


	//printf("\n双向链表的销毁::\n");
	//DCLDestroy(&n);  
}


