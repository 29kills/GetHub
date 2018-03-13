#include<stdio.h>
#include<assert.h>
#include"DCLNode.h"
#include"Queue.h"

void Queue_Init(Queue* q)//初始化队列
{
	DCLInit(q);    //双向链表的初始化
}

void Queue_Puch(Queue* q,const DataType data)//插入
{
	DCLPushBack(*q,data);   //尾插
}
DataType Queue_Front(Queue* q)//取队头
{
	assert(q);
	assert(!DCLEmpty(*q));
	return (*q)->_pNext->_data;
}

int Queue_Empty(Queue* q)//判空
{
	DCLEmpty(*q);
}

void Queue_Pop(Queue* q)//出队列
{
	DCLPopFront(*q); //头删
}
size_t Queue_Size(Queue* q)//求元素个数
{
	DCLSize(*q);
}
void Queue_Delete(Queue* q)//销毁
{
	DCLDestroy(q);  //双向链表的销毁
}

void Queue_test()//测试
{
	Queue q ;//双向链表实现
	Queue_Init(&q);
	Queue_Puch(&q,1);
	Queue_Puch(&q,2);

	printf("%d\n",Queue_Empty(&q));
	printf("%d\n",Queue_Front(&q));

	Queue_Pop(&q);
	printf("%d\n",Queue_Empty(&q));
	printf("%d\n",Queue_Front(&q));
	
	printf("%d\n",Queue_Size(&q));

	Queue_Delete(&q);//销毁
}