//ջ�����������
//ջ---�Ƚ����  ����---�Ƚ��ȳ�
//1��ʵ��һ��ջ��Ҫ��ʵ�ֳ�ջ����ջ��min��������Сֵ�ò�������ʱ�临�Ӷ�ΪO(1)
//�⣺�Կռ任ʱ�䣺������ջ��һ��ջ��ԭֵ��һ��ջ��Сֵ������һ��ջͬʱ����ֵ��һ��ԭֵ��һ����Сֵ
//2������ջʵ��һ������
//�⣺ʹ����ջ��ֱ����ջ1����ջ1Ϊ�գ��뵽ջ1�У����ݷŵ�ջ2�У�
//��ջ2��ջ2��Ϊ�ճ�ջ��Ϊ�գ�ջ1���ݷŵ�ջ2�к��ջ����ֱ�ӳ�ջ2��
//3����������ʵ��һ��ջ
//�⣺�������У�����е�Ϊ�յĶ����У�ջ����ֱ��ȡ��Ϊ�յĶ�ͷ 
//�����н���Ϊ�յĶ���1 ����Ϊ�յĶ���2�У��ٽ�����2���ݵ��ص�ԭ����1�У������һ�����ݳ�����
//4��Ԫ����ջ��ջ�ĺϷ��ԣ�����ջ���У�1 2 3 4 5 ����ջ���У�4 5 3 2 1 ��Ϸ�
//��ջ�����У�1 2 3 4 5 ����ջ����Ϊ��4 5 2 3 1 �򲻺Ϸ�
//5��һ������ʵ������ջ
//�⣺�������м�����������ż������
#pragma once 
#include<iostream>
#include<assert.h>
#include<queue>
#include<stack>
using namespace std;

//1��ʵ��һ��ջ��Ҫ��ʵ�ֳ�ջ����ջ��min��������Сֵ�ò�������ʱ�临�Ӷ�ΪO(1)
//�⣺�Կռ任ʱ�䣺������ջ��һ��ջ��ԭֵ��һ��ջ��Сֵ������һ��ջͬʱ����ֵ��һ��ԭֵ��һ����Сֵ
template<class T>
class minstack
{
public :
	void Puch_Back(const T& data)
	{
		_st.push(data);
		if(_minst.empty() || data <= _minst.top()._value)//С�ڵ�����ջ��ͬʱͳ�Ƹ����ĸ���+1
		{
			ValueRef vr;//��������
			vr._value = data;//��ֵ����
			vr._ref++;//����+1
			_minst.push(vr);//��ջ
		}
	}

	void Pop()//����ջ������ͬ������--��������Ϊ1ʱ����ջ
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
				_minst.push(tmp);//������ֵ
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
	struct ValueRef//�ڲ���--ֻ�����ڲ�ʹ��
	{
		T _value;//С����
		size_t _ref;//������ͳ�Ƹ����ĸ���
		ValueRef()
			:_ref(0)
		{}
	};
	stack<T> _st;
	stack<ValueRef> _minst;//���ü���
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

//2������ջʵ��һ������
//�⣺ʹ����ջ��ֱ����ջ1����ջ1Ϊ�գ��뵽ջ1�У����ݷŵ�ջ2�У�
//��ջ2��ջ2��Ϊ�ճ�ջ��Ϊ�գ�ջ1���ݷŵ�ջ2�к��ջ����ֱ�ӳ�ջ2��
//ջ�ɲ�Ϊ��
template<class T>
class Qstack
{
public :
	void Puch(const T& data)
	{
		s1.push(data);
		//if(s1.empty())//s1Ϊ��
		//	s2.push(data);
		//else//����һ��ջΪ��
		//	s1.push(data);
	}
	void Pop()
	{
		if(s2.empty())//ջ2Ϊ��
		while(!s1.empty())//s1����Ԫ����s2
		{
			s2.push(s1.top());
			s1.pop();
		}
		s2.pop();
	}
	T& Front()
	{
        if(s2.empty())//ջ2Ϊ��
		while(!s1.empty())//s1����Ԫ����s2
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

//3����������ʵ��һ��ջ
//�⣺�������У�����е���Ϊ�յĶ����У�ջ����ֱ��ȡ��Ϊ�յĶ�β��back�� 
//�����н���Ϊ�յĶ���1 ����Ϊ�յĶ���2�У��ٽ�����2���ݵ��ص�ԭ����1�У������һ�����ݳ�����
//ע����֤��һ������Ϊ��
template<class T>
class Squeue
{
public :
	void Puch(const T& data)//��ջ����Ϊ�յĶ���
	{
		if(!q1.empty())
			q1.push(data);
		else
			q2.push(data);
	}
	void Pop()//����Ϊ�յĶ����е����ݰ��Ƶ�Ϊ�յĶ����У������һ�����ݳ�����
	{
		if(q1.empty())//q1Ϊ��
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
	T& Top()//ȡ��Ϊ�յĶ��еĶ�β
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

//4��Ԫ����ջ��ջ�ĺϷ��ԣ�����ջ���У�1 2 3 4 5 ����ջ���У�4 5 3 2 1 ��Ϸ�
//��ջ�����У�1 2 3 4 5 ����ջ����Ϊ��4 5 2 3 1 �򲻺Ϸ�

template<class T>
class checkstack
{
public :
	bool check1(const T* In,const T* Out,const size_t Insize,const size_t Outsize)
	{
		size_t in = 0;
		size_t out = 0;
		if(Insize != Outsize) return false;
		while(out < Outsize)//��ջ����δ��ȫ����
		{
			//�ó�ջ������ģ����ջ���бȽ�---��ͬ��ջ
			if(!_s.empty() && _s.top() == Out[out])//��ջ������ģ����ջջ��Ԫ����ͬ
			{
				_s.pop();//��ͬ---ջ����ջ
			}
			else//����ͬ
			{
				//��ջ�������ջ���бȽϣ�����ͬ��ջ������ջ
				while(in < Insize && In[in] != Out[out])//ѭ������ջ����ջԪ�ز�ƥ��---��ջ
				{
					_s.push(In[in++]);//��ջ����---��ջ
				}
				if(in == Insize)//ȫ��ջ---�˳�ѭ��
					return false;//��ջ�����꣬����ջδ���꣬��ƥ��
				else//ƥ��---�˳�ѭ����ͬʱ����ˣ�������
					in++;//��ջ����ջԪ����ͬ����ջ�����
			}
			out++;//��ջ����һֱ�����
		}//��ȫ��ջ
		return true;
	}

	bool check2(const T* In,const T* Out,const size_t Insize,const size_t Outsize)
	{
		size_t in = 0;//�±�
		size_t out = 0;
		if(Insize != Outsize) return 0;
		while(out < Outsize)
		{
			//��ջ,����һ����ȫ��ջ�������޷�������ջ����ջ����
			while(in < Insize && In[in] != Out[out])//��ǰ��ջ���в�ͬ�ڳ�ջ���У�ע��Խ������
			{
				_s.push(In[in++]);//��ջ����ģ����ջ
			}

 			if(!_s.empty() && Out[out] == _s.top())//��ջ
			{
			     _s.pop();
			}
			else
			{
				if(in == Insize)//��ջ�������˳�ѭ��-->��ջδ�����꣬���Ϸ�
					return false;
				else//Ԫ����ͬ���˳�ѭ��
					in++;//������һ��Ԫ��
			}
			out++;//������һ����ջ����
		}
		return true;//��ջ���б����꣬�Ϸ�
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

//5��һ������ʵ������ջ
//�⣺�������м�����������ż������
template<class T,size_t N>
class Twostack//һ������ʵ������ջ
{
public :
	Twostack()
		:_top1(0)//��ʼ��Ԫ�ظ���
		,_top2(N-1)
	{}
	void Puch(const T& data,size_t swich)
	{
		assert(swich == 1 || swich == 2);//�ж�ջ�Ƿ�ѡ����ȷ
		assert(_top1 + N - _top2 <= N);//�ж������Ƿ�����
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
	T _data[N];//�洢����
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