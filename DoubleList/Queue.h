#ifndef __QUEUE_H__

#define __QUEUE_H__

#include"DCLNode.h"
typedef PNode Queue;//指针

void Queue_Init(Queue* q);//初始化队列
void Queue_Puch(Queue* q,const DataType data);//插入
DataType Queue_Front(Queue* q);//取队头
int Queue_Empty(Queue* q);//判空
void Queue_Pop(Queue* q);//出队列
size_t Queue_Size(Queue* q);//求元素个数
void Queue_Delete(Queue* q);//销毁
void Queue_test();//测试
#endif