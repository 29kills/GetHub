//栈与队列面试题
//栈---先进后出  队列---先进先出
//1、实现一个栈，要求实现出栈，入栈，min（返回最小值得操作），时间复杂度为O(1)
//解：以空间换时间：用两个栈，一个栈存原值，一个栈存小值。或用一个栈同时存两值，一个原值，一个最小值
//2、两个栈实现一个队列
//解：使用两栈：直接入栈1（或栈1为空，入到栈1中，数据放到栈2中）
//出栈2，栈2不为空出栈，为空，栈1数据放到栈2中后出栈（或直接出栈2）
//3、两个队列实现一个栈
//解：两个队列，入队列到为空的队列中，栈顶即直接取不为空的队头 
//出队列将不为空的队列1 倒置为空的队列2中，再将队列2数据倒回到原队列1中，将最后一个数据出队列
//4、元素入栈出栈的合法性，如入栈序列：1 2 3 4 5 ，出栈序列：4 5 3 2 1 则合法
//出栈的序列：1 2 3 4 5 ，出栈序列为：4 5 2 3 1 则不合法
//5、一个数组实现两个栈
//解：两边向中间生长，或奇偶数划分
#pragma once 
#include<iostream>
#include<assert.h>
#include<queue>
#include<stack>
using namespace std;

//1、实现一个栈，要求实现出栈，入栈，min（返回最小值得操作），时间复杂度为O(1)
//解：以空间换时间：用两个栈，一个栈存原值，一个栈存小值。或用一个栈同时存两值，一个原值，一个最小值
template<class T>
class minstack
{
public :
	void Puch_Back(const T& data)
	{
		_st.push(data);
		if(_minst.empty() || data <= _minst.top()._value)//小于等于入栈，同时统计该数的个数+1
		{
			ValueRef vr;//创建对象
			vr._value = data;//赋值数据
			vr._ref++;//计数+1
			_minst.push(vr);//入栈
		}
	}

	void Pop()//两个栈数据相同计数器--，计数器为1时，出栈
	{
		ValueRef tmp = _minst.top();
		if(_st.top() == tmp._value)
		{
			if(tmp._ref == 1)
			{
				_minst.pop();
			}
			else
			{
				tmp._ref--;
				_minst.pop();
				_minst.push(tmp);//更换新值
			}
		}
		_st.pop();
	}
	T& Top()
	{
		return _st.top();
	}
	T& Min()
	{
		return _minst.top()._value;
	}
	bool Empty()
	{
		return _st.empty();
	}
	size_t Size()
	{
		return _st.size();
	}
protected:
	struct ValueRef//内部类--只能在内部使用
	{
		T _value;//小数据
		size_t _ref;//计数，统计该数的个数
		ValueRef()
			:_ref(0)
		{}
	};
	stack<T> _st;
	stack<ValueRef> _minst;//引用计数
};

void test()
{
	minstack<int> ms;
	ms.Puch_Back(1);
	ms.Puch_Back(2);
	ms.Puch_Back(0);
	ms.Puch_Back(0);
	ms.Puch_Back(0);
	ms.Puch_Back(5);
	cout << ms.Min() << endl;

	cout << ms.Size() << endl;
	while(!ms.Empty())
	{
		cout << ms.Top() << ' ';
		ms.Pop();
	}
}

//2、两个栈实现一个队列
//解：使用两栈：直接入栈1（或栈1为空，入到栈1中，数据放到栈2中）
//出栈2，栈2不为空出栈，为空，栈1数据放到栈2中后出栈（或直接出栈2）
//栈可不为空
template<class T>
class Qstack
{
public :
	void Puch(const T& data)
	{
		s1.push(data);
		//if(s1.empty())//s1为空
		//	s2.push(data);
		//else//其中一个栈为空
		//	s1.push(data);
	}
	void Pop()
	{
		if(s2.empty())//栈2为空
		while(!s1.empty())//s1搬移元素至s2
		{
			s2.push(s1.top());
			s1.pop();
		}
		s2.pop();
	}
	T& Front()
	{
        if(s2.empty())//栈2为空
		while(!s1.empty())//s1搬移元素至s2
		{
			s2.push(s1.top());
			s1.pop();
		}
		return s2.top();
	}
	size_t Size()
	{
		return s1.size()+s2.size();
	}
	bool Empty()
	{
		return s1.empty() && s2.empty();
	}
private :
	stack<T> s1;
	stack<T> s2;
};

void Qstack_test()
{
	Qstack<int> qs;
	qs.Puch(1);
	qs.Puch(2);
	qs.Puch(3);
	qs.Puch(4);
	qs.Pop();
	qs.Puch(5);
	qs.Puch(6);

	cout << qs.Size() << endl;
	while(!qs.Empty())
	{
		cout << qs.Front() << ' ';
		qs.Pop();
	}
}

//3、两个队列实现一个栈
//解：两个队列，入队列到不为空的队列中，栈顶即直接取不为空的队尾（back） 
//出队列将不为空的队列1 倒置为空的队列2中，再将队列2数据倒回到原队列1中，将最后一个数据出队列
//注：保证有一个队列为空
template<class T>
class Squeue
{
public :
	void Puch(const T& data)//入栈至不为空的队列
	{
		if(!q1.empty())
			q1.push(data);
		else
			q2.push(data);
	}
	void Pop()//将不为空的队列中的数据搬移到为空的队列中，将最后一个数据出队列
	{
		if(q1.empty())//q1为空
		{
			while(q2.size() > 1)
			{
				q1.push(q2.front());
				q2.pop();
			}
			q2.pop();
		}
		else
		{
			while(q1.size() > 1)
			{
				q2.push(q1.front());
				q1.pop();
			}
			q1.pop();
		}
	}
	T& Top()//取不为空的队列的队尾
	{
		if(!q1.empty())
			return q1.back();
		else
			return q2.back();
	}
	bool Empty()
	{
		return q1.empty() && q2.empty();
	}
	size_t Size()
	{
		return q1.size() + q2.size();
	}
private:
	queue<T> q1;
	queue<T> q2;
};

void Squeue_test()
{
	Squeue<int> sq;
	sq.Puch(1);
	sq.Puch(2);
	sq.Puch(3);
	sq.Pop();
	sq.Puch(4);
	sq.Puch(5);

	while(!sq.Empty())
	{
		cout << sq.Top() << ' ';
		sq.Pop();
	}
}

//4、元素入栈出栈的合法性，如入栈序列：1 2 3 4 5 ，出栈序列：4 5 3 2 1 则合法
//出栈的序列：1 2 3 4 5 ，出栈序列为：4 5 2 3 1 则不合法

template<class T>
class checkstack
{
public :
	bool check1(const T* In,const T* Out,const size_t Insize,const size_t Outsize)
	{
		size_t in = 0;
		size_t out = 0;
		if(Insize != Outsize) return false;
		while(out < Outsize)//出栈序列未完全遍历
		{
			//用出栈序列与模仿入栈序列比较---相同出栈
			if(!_s.empty() && _s.top() == Out[out])//出栈序列与模仿入栈栈顶元素相同
			{
				_s.pop();//相同---栈顶出栈
			}
			else//不相同
			{
				//入栈序列与出栈序列比较，不相同入栈序列入栈
				while(in < Insize && In[in] != Out[out])//循环，出栈与入栈元素不匹配---入栈
				{
					_s.push(In[in++]);//入栈序列---入栈
				}
				if(in == Insize)//全入栈---退出循环
					return false;//入栈已走完，但出栈未走完，则不匹配
				else//匹配---退出循环，同时向后退（跳过）
					in++;//出栈与入栈元素相同，入栈向后走
			}
			out++;//出栈序列一直向后走
		}//完全出栈
		return true;
	}

	bool check2(const T* In,const T* Out,const size_t Insize,const size_t Outsize)
	{
		size_t in = 0;//下标
		size_t out = 0;
		if(Insize != Outsize) return 0;
		while(out < Outsize)
		{
			//入栈,不可一次完全入栈，否则无法处理入栈即出栈问题
			while(in < Insize && In[in] != Out[out])//当前入栈序列不同于出栈序列，注意越界问题
			{
				_s.push(In[in++]);//入栈序列模仿入栈
			}

 			if(!_s.empty() && Out[out] == _s.top())//出栈
			{
			     _s.pop();
			}
			else
			{
				if(in == Insize)//入栈遍历完退出循环-->出栈未遍历完，不合法
					return false;
				else//元素相同，退出循环
					in++;//遍历下一个元素
			}
			out++;//遍历下一个出栈序列
		}
		return true;//出栈序列遍历完，合法
	}

private :
	stack<int> _s;
};

void stack_test()
{
	checkstack<int> cs;
	int In[] = {1,2,3,4,5,6};
	//int Out[] = {6,5,4,3,2,1};

	//int In[] = {1,2,3,4,5};
	int Out[] = {4,5,6,3,1,2};
	//int Out[] = {4,5,3,2,1};
	//int Out[] = {4,5,3,2,1};
	size_t Insize = sizeof(In)/sizeof(In[0]);
	size_t Outsize = sizeof(Out)/sizeof(Out[0]);

	cout << cs.check1(In,Out,Insize,Outsize) << endl;
	cout << cs.check2(In,Out,Insize,Outsize) << endl;


}

//5、一个数组实现两个栈
//解：两边向中间生长，或奇偶数划分
template<class T,size_t N>
class Twostack//一个数组实现两个栈
{
public :
	Twostack()
		:_top1(0)//初始化元素个数
		,_top2(N-1)
	{}
	void Puch(const T& data,size_t swich)
	{
		assert(swich == 1 || swich == 2);//判断栈是否选择正确
		assert(_top1 + N - _top2 <= N);//判断数组是否已满
		if(swich == 1)
		{
			_data[_top1++] = data;
		}
		else 
			_data[_top2--] = data;
	}
	void Pop(const size_t swich)
	{
		assert(swich == 1 || swich == 2);
		if(swich == 1)
		{
			assert(_top1 > 0);
			_top1--;
		}
		else
		{
			assert(_top2 < N-1);
			_top2++;
		}
	}
	T& Top(const size_t swich)
	{
		assert(swich == 1 || swich == 2);
		if(swich == 1)
		{
			assert(_top1 > 0);
			return _data[_top1-1];
		}
		else
		{
			assert(_top2 < N-1);
			return _data[_top2+1];
		}
	}

	size_t Size(const size_t swich)
	{
		assert(swich == 1 || swich == 2);
		return (swich == 1) ? _top1 : N-1-_top2;
	}
	bool Empty(const size_t swich)
	{
		assert(swich == 1 || swich == 2);
		return (swich == 1) ? (_top1 == 0) : (N-1==_top2);
	}
private :
	T _data[N];//存储数据
	size_t _top1;//++
	size_t _top2;//--
};

void Twostack_test()
{
	Twostack<int,10> ts1;
	ts1.Puch(1,1);
	ts1.Puch(2,1);
	ts1.Puch(3,1);
	ts1.Puch(4,2);
	ts1.Puch(5,2);
	ts1.Puch(5,1);
	ts1.Puch(6,2);
	ts1.Puch(6,1);
	ts1.Puch(7,1);
	ts1.Puch(3,2);

	//ts1.Pop(1);
	cout << ts1.Size(1) << endl;
	cout << ts1.Size(2) << endl;
	while(!ts1.Empty(2))
	{
		cout << ts1.Top(2) << ' ';
		ts1.Pop(2);
	}
	cout << endl;
	while(!ts1.Empty(1))
	{
		cout << ts1.Top(1) << ' ';
		ts1.Pop(1);
	}
	cout << endl;
	cout << ts1.Size(1) << endl;
	cout << ts1.Size(2) << endl;
}