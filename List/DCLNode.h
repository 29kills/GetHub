#ifndef __DCLNODE_H__
#define __DCLNODE_H__

typedef int DataType;
typedef struct DCLNode
{
	struct DCLNode* _pNext;
	struct DCLNode* _pPre;
	DataType _data;

}Node, *PNode;



void DCLInit(PNode* ppHead);    //双向链表的初始化

void DCLPushBack(PNode pHead, DataType data);   //尾插
void DCLPopBack(PNode pHead);        //尾删
void DCLPushFront(PNode pHead, DataType data);    //头插
void DCLPopFront(PNode pHead);      //头删
void DCLInsert(PNode pos, DataType data);   //任意位置的插入
void DCLErase(PNode pos);       //任意位置的删除
void DCLDestroy(PNode* ppHead);  //双向链表的销毁
PNode DCLFind(PNode pHead, DataType data); //查找
int DCLEmpty(PNode pHead);//判空
PNode DCLBuyNode(DataType data);
void DCLPrintList(PNode pHead);
size_t DCLSize(PNode pHead);
void DCLNode_test();//测试


#endif