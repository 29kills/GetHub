#ifndef __QUEUE_H__

#define __QUEUE_H__

#include"DCLNode.h"
typedef PNode Queue;//ָ��

void Queue_Init(Queue* q);//��ʼ������
void Queue_Puch(Queue* q,const DataType data);//����
DataType Queue_Front(Queue* q);//ȡ��ͷ
int Queue_Empty(Queue* q);//�п�
void Queue_Pop(Queue* q);//������
size_t Queue_Size(Queue* q);//��Ԫ�ظ���
void Queue_Delete(Queue* q);//����
void Queue_test();//����
#endif