#include<stdio.h>
#include<assert.h>
#include"DCLNode.h"
#include"Queue.h"

void Queue_Init(Queue* q)//��ʼ������
{
	DCLInit(q);    //˫������ĳ�ʼ��
}

void Queue_Puch(Queue* q,const DataType data)//����
{
	DCLPushBack(*q,data);   //β��
}
DataType Queue_Front(Queue* q)//ȡ��ͷ
{
	assert(q);
	assert(!DCLEmpty(*q));
	return (*q)->_pNext->_data;
}

int Queue_Empty(Queue* q)//�п�
{
	DCLEmpty(*q);
}

void Queue_Pop(Queue* q)//������
{
	DCLPopFront(*q); //ͷɾ
}
size_t Queue_Size(Queue* q)//��Ԫ�ظ���
{
	DCLSize(*q);
}
void Queue_Delete(Queue* q)//����
{
	DCLDestroy(q);  //˫�����������
}

void Queue_test()//����
{
	Queue q ;//˫������ʵ��
	Queue_Init(&q);
	Queue_Puch(&q,1);
	Queue_Puch(&q,2);

	printf("%d\n",Queue_Empty(&q));
	printf("%d\n",Queue_Front(&q));

	Queue_Pop(&q);
	printf("%d\n",Queue_Empty(&q));
	printf("%d\n",Queue_Front(&q));
	
	printf("%d\n",Queue_Size(&q));

	Queue_Delete(&q);//����
}