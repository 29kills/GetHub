#ifndef __DCLNODE_H__
#define __DCLNODE_H__

typedef int DataType;
typedef struct DCLNode
{
	struct DCLNode* _pNext;
	struct DCLNode* _pPre;
	DataType _data;

}Node, *PNode;



void DCLInit(PNode* ppHead);    //˫������ĳ�ʼ��

void DCLPushBack(PNode pHead, DataType data);   //β��
void DCLPopBack(PNode pHead);        //βɾ
void DCLPushFront(PNode pHead, DataType data);    //ͷ��
void DCLPopFront(PNode pHead);      //ͷɾ
void DCLInsert(PNode pos, DataType data);   //����λ�õĲ���
void DCLErase(PNode pos);       //����λ�õ�ɾ��
void DCLDestroy(PNode* ppHead);  //˫�����������
PNode DCLFind(PNode pHead, DataType data); //����
int DCLEmpty(PNode pHead);//�п�
PNode DCLBuyNode(DataType data);
void DCLPrintList(PNode pHead);
size_t DCLSize(PNode pHead);
void DCLNode_test();//����


#endif