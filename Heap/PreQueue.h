#pragma once 
#include"heap.h"
//注：堆不是适配器,堆属于一种算法
//Compare指明数据排序的优先级
//时间复杂度O(lgN)
//优先级队列
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
		_prequeue.Pop();//调用Heap中的Pop函数
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
	PreQueue<int> pq;//大的优先级高
	pq.Puch(1);
	pq.Puch(3);
	pq.Puch(2);
	pq.Puch(5);
	cout << pq.Top() << endl;//取栈顶
	pq.Pop();
	cout << pq.Top()<< endl;
	cout << "Empty():" << pq.Empty() << endl;
	cout << "size():"<< pq.Size() << endl;

	PreQueue<int,Less<int>> pq2;//数据小的优先级高
	pq2.Puch(1);
	pq2.Puch(3);
	pq2.Puch(2);
	pq2.Puch(5);

	cout << pq2.Top() << endl;//取栈顶
	pq2.Pop();
	cout << pq2.Top()<< endl;
}