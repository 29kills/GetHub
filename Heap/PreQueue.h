#pragma once 
#include"heap.h"
//ע���Ѳ���������,������һ���㷨
//Compareָ��������������ȼ�
//ʱ�临�Ӷ�O(lgN)
//���ȼ�����
template<class T,class Compare = Greater<T>>
class PreQueue
{
public:
	void Puch(const T& data)
	{
		_prequeue.Puch(data);
	}
	void Pop()
	{
		_prequeue.Pop();//����Heap�е�Pop����
	}
	T& Top()
	{
		return _prequeue.Top();
	}
	size_t Size()
	{
		return _prequeue.Size();
	}
	bool Empty()
	{
		return _prequeue.Empty();
	}
private:
	Heap<T,Compare> _prequeue;
};

void PreQueue_test()
{
	PreQueue<int> pq;//������ȼ���
	pq.Puch(1);
	pq.Puch(3);
	pq.Puch(2);
	pq.Puch(5);
	cout << pq.Top() << endl;//ȡջ��
	pq.Pop();
	cout << pq.Top()<< endl;
	cout << "Empty():" << pq.Empty() << endl;
	cout << "size():"<< pq.Size() << endl;

	PreQueue<int,Less<int>> pq2;//����С�����ȼ���
	pq2.Puch(1);
	pq2.Puch(3);
	pq2.Puch(2);
	pq2.Puch(5);

	cout << pq2.Top() << endl;//ȡջ��
	pq2.Pop();
	cout << pq2.Top()<< endl;
}