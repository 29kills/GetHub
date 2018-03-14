#pragma once
#include<iostream>
#include"Copy.h"
using namespace std;
//像数组，顺序表等存储结构 他的原身就是一个迭代器
template<class T>
class myvector//顺序表
{
public :
	typedef T* Iterator;//必须是公有类型，否则外部不能使用
	typedef const T* const_Iterator;
	myvector()
		:_start(0)
		,_finish(0)
		,_end(0)
	{}
	void Puch_Back(const T& data)//尾插
	{
		Inserve(End(),data);//插入
	}

	 Iterator Erase(Iterator pos)//删除
	{
		//如何处理迭代器失效问题
		//判断位置合法
		assert(pos <= _finish);
		//Iterator begin = pos + 1;
		//while(pos < _finish)
		//{
		//	*(begin-1) = *begin;
		//}
		Iterator begin = pos ;
		Iterator next = pos + 1;//从后一个数据开始向前移动
		while(next < _finish)//移动数据
		{
			*begin++ = *next++;
		}
	    _finish--;
		return pos;//返回当前位置
	}
	void Inserve(Iterator pos,const T& data)//插入
	{
		//注意扩容导致迭代器失效问题（pos变为NULL）
		//扩容后指向新的地址，pos地址失效
		int gap = pos - _start;//计算相对位置
		if(_finish == _end)//已满
		{
			size_t size = Capacity();
			size_t newsize = size > 0 ? size*2 : 3;
			Expand(newsize);//增容--pos位置失效
		}
		pos = _start + gap;//pos重新找到对应位置		
		assert(pos <= _finish);//合法位置
		Iterator end = _finish - 1;//标记最后一个数据的位置
		while(end >= pos)//搬移数据
		{
			*end = *--end;
		}
		_finish++;
		*pos = data;
	}

	void Resize(size_t count,const T& val = T())//val为缺省参数（有则传，无则不处理）
	{
		//1先扩容--后根据情况是否初始化新增空间
		//count < size--更新finish
		//cout > size---需赋值成val和更新finish
		size_t size = Size();//获取原来元素个数
		Expand(count);//增容

		Iterator cur = _start + size;//指向对应需初始化的第一个位置（原对应finish）
		_finish = _start + count;//新的数据位置
		if(count > size)
		{
			while(cur < _finish)//初始化
			{
				*(cur++) = val; 
			}
		}
	}
	void Reserve(size_t count)//仅扩容
	{
		//扩容
		Expand(count);//增容
	}
	size_t Size()//求元素个数
	{
		return _finish - _start;//指针相减=元素个数
	}
	size_t Capacity()//求容量
	{
		return _end - _start;
	}
	void Expand(size_t count)//增容
	{
		size_t size = Size();
		size_t capacity = Capacity();
		if(count > capacity)
		{
			T* tmp = new T[count];//T[count]--开辟count个空间,T(count)--开辟一个空间初始化为count
			if(_start)
			    __TypeCopy(tmp,_start,size);//个数size（应该使用深拷贝）
		    delete []_start;//销毁
			_start = tmp;
			_finish = _start + size;
			_end = _start + count;
		}
	}
	void Print()
	{
		Iterator tmp = _start;
		while(tmp < _finish)
		{
			cout << *tmp++ << ' ';
		}
		cout << endl;
	}
	Iterator Begin()
	{
		return _start;
	}
	Iterator End()
	{
		return _finish;
	}

	const_Iterator Begin() const
	{
		return _start;
	}
	const_Iterator End() const
	{
		return _finish;
	}
	T& operator[](const size_t n)
	{
		return _start[n];
	}
private :
	Iterator _start;//头指针(数据头)
    Iterator _finish;//数据尾（存数据）
	Iterator _end;//最大尾（容量）
};

template<class T>
void print_vector(const myvector<T>& V1)
{
	myvector<int>::const_Iterator v = V1.Begin();
	while(v != V1.End())
	{
		//*v = 4;//const迭代器不可修改
		cout << *v << ' ';
		v++;
	}
	cout << endl;
}

template<class T>
void Erase_vector(myvector<T>& V1)
{
	myvector<int>::Iterator v = V1.Begin();
	T* tmp =  V1.End();
	while(v != V1.End())//顺序表的数据地址会发生变化，链表的数据地址不会发生变化
	{
		if(*v%2 == 0)
		   v = V1.Erase(v);//删除跳过了3怎么处理
		else
		++v;
	}
	cout << endl;
}


void myvector_test()
{
	size_t i = 0;
	myvector<int> V1;
	V1.Puch_Back(1);
	V1.Puch_Back(2);
	V1.Puch_Back(3);
	V1.Puch_Back(4);
	V1.Puch_Back(6);
	V1.Puch_Back(3);
	V1.Puch_Back(5);
	V1.Puch_Back(8);

	V1.Print();
	Erase_vector(V1);
	V1.Print();

	V1.Erase(V1.Begin());//删除
	V1.Erase(V1.End());//删除
	V1.Print();


	//V1.Erase(V1.End());//删除
	//print_vector(V1);

	cout << "size=" << V1.Size() << endl;
	cout << "容量：" << V1.Capacity() << endl;

	V1.Reserve(8);
	cout << "size=" << V1.Size() << endl;
	cout << "容量：" << V1.Capacity() << endl;

	
	V1.Resize(10,6);
	i =  V1.Size();
	cout << "size=" << V1.Size() << endl;
	cout << "容量：" << V1.Capacity() << endl;

	for(i = 0;i < V1.Size();i++)
	{
		printf("V1[%d]=%d ",i,V1[i]);//调用重载的[]函数
	}
	cout << endl;

	print_vector(V1);
	
}