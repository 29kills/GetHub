#include<stdio.h>
#include<assert.h>
#include<stdlib.h>
#include"DCLNode.h"

void DCLInit(PNode* ppHead)    //˫������ĳ�ʼ��
{
	*ppHead = DCLBuyNode(0);   //����һ���ڱ���㣬����ֵΪ��
	(*ppHead)->_pNext = (*ppHead);
	(*ppHead)->_pPre = (*ppHead);
}


PNode DCLBuyNode(DataType data)    //�����½��
{
	PNode pNew = (PNode)malloc(sizeof(Node));
	pNew->_data = data;
	pNew->_pNext = NULL;
	pNew->_pPre = NULL;
	return pNew;
}



void DCLPushBack(PNode pHead, DataType data)  //β��
{
	PNode pNew = DCLBuyNode(data);

	PNode pTail = pHead;    //pTail��pHead��ʼ�����ܴ�NULL��ʼ
	PNode cur = pHead;
	
	assert(pHead);  //�����ڱ����

	cur->_pPre->_pNext = pNew ;
	pNew->_pPre = cur->_pPre;
	pNew->_pNext = pHead;
	pHead->_pPre = pNew;
}

void DCLPopBack(PNode pHead)        //βɾ
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


void DCLPushFront(PNode pHead, DataType data)  //ͷ��
{
	PNode pNew = DCLBuyNode(data);
	pHead->_pNext->_pPre = pNew;
	pNew->_pNext = pHead->_pNext;
	pHead->_pNext = pNew;
	pNew->_pPre = pHead;
}


void DCLPopFront(PNode pHead)     //ͷɾ
{
	//assert(pHead);
	PNode del = NULL;
	if (pHead->_pNext == NULL)   //���ٵ���һ��
	{
		printf("˫�������Ѿ�Ϊ�գ�������ɾ��\n");
	}
	del = pHead->_pNext;
	pHead->_pNext = del->_pNext;
	free(del);
}

int DCLEmpty(PNode pHead)//�п�
{
	return pHead->_pNext == pHead;
}

void DCLInsert(PNode pos, DataType data)   //����λ�õĲ���
{
	PNode pNew = DCLBuyNode(data);
	PNode pre = pos->_pPre;
	pre->_pNext = pNew;
	pNew->_pPre = pre;

	pNew->_pNext = pos;
	pos->_pPre = pNew;
}



void DCLErase(PNode pos)       //����λ�õ�ɾ��
{
	PNode pre = NULL;
	PNode next = NULL;

	assert(pos);
	if (pos->_pNext == pos)
	{
		printf("˫�������Ѿ�Ϊ�գ�������ɾ��\n");
	}
	pre = pos->_pPre;
    next = pos->_pNext;
	pre->_pNext = next;
	next->_pPre = pre;

	free(pos);
}



void DCLDestroy(PNode* ppHead)  //˫�����������
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



PNode DCLFind(PNode pHead, DataType data) //����
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
size_t DCLSize(PNode pHead)//Ԫ�ظ���
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
	PNode n;    //������Ϊ�ṹ��ָ������
	PNode find = NULL;
	DCLInit(&n);
	DCLBuyNode(0); 
	printf("β��::");
	DCLPushBack(n, 1);
	DCLPushBack(n, 2);
	DCLPushBack(n, 3);
	DCLPushBack(n, 4);
	DCLPushBack(n, 5);

	//printf("\nβɾ::");
	//DCLPopBack(n);
	//DCLPopBack(n);
	//DCLPopBack(n);

	//printf("\nͷ��::");
	//DCLPushFront(n, 6);
	//DCLPushFront(n, 7);


	//printf("\nͷɾ::");
	//DCLPopFront(n);
	//DCLPopFront(n);

	//printf("\n����λ�õĲ���::");
	//DCLInsert(DCLFind(n, 6), 8);
	//DCLInsert(DCLFind(n, 7), 9);

	//printf("\n����λ�õ�ɾ��::");
	//DCLErase(DCLFind(n, 8));

	//find = DCLFind(n, 3);
	//printf("\n���ҵ��������Ϊ%d�Ľ���ַΪ%p::", find->_data, find);


	//printf("\n˫�����������::\n");
	//DCLDestroy(&n);  
}


