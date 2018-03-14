//Wptr不可与Shared_Ptr分离---模板不支持分离编译，所以其它.h文件不可调用此文件中的模板函数
//.h文件中的类，可在其它.h文件直接使用，所以同一个工程不可出现相同的类名
#pragma once
#include<iostream>
using namespace std ;

//前置声明
template<class T>
class Wptr1;

template<class T>
class Shptr1
{
	friend class Wptr1<T>;//友元类
public :
	Shptr1(T* sh = NULL)//缺省设置为空
		:_shr(sh)
		,_count(new size_t(1))//初始化为1
	{}
	/*
	//弱引用不会调用此拷贝构造和赋值运算函数，而是调用自身的，所以该对象的计数器不会改变
	//sh1(sh)
	Shptr1(const Shptr1<T>& sh)//拷贝构造
		:_shr(sh._shr)
		,_count(sh._count)
	{
		(*_count)++;//计数+1
	}
	//sh1=sh;
	Shptr1<T>& operator= (const Shptr1<T>& sh)//赋值运算重载函数
	{
		if(_shr != sh._shr)//不为sh=sh
		{
			if(--(*_count) == 0)//只共用一次，则删除旧内存空间，共用新空间，否则保留原空间，共用新空间
			{
				delete _shr;
				delete _count;
			}
			_shr=sh._shr;
			_count=sh._count;
			(*_count)++;
		}
		return *this;//this即该对象指针(变为sh)
	}*/
	//运算符重载
	T& operator*()
	{
		return *_shr;
	}
	T* operator->()
	{
		return _shr;
	}
	T& operator[](const size_t n)
	{
		return _shr[n];
	}

	size_t Usercoun()//取计数器值
	{
		return *_count;
	}

	~Shptr1()//析构，销毁
	{
		if(-- (*_count) == 0)//每调用一次-1，当为0时释放空间
			delete _shr;
	}
private://私有成员只能在类内部访问
	T* _shr;
	size_t* _count;//所有对象应共用一个计数器，所以设为指针
};

//弱引用---不会改变对象计数器的值，类似于普通指针
//Wptr主要用于处理循环引用问题，用于指针域处定义对象，不直接定义对象，而是用Shptr定义对象
template<class T>
class Wptr1//用于处理循环引用问题
{
public :
	Wptr1() 
		:_Wp(NULL)
	{}

	Wptr1(const Shptr1<T>& wp)//拷贝构造函数(以Shptr作为类型)
		:_Wp(wp._shr)
	{}
	Wptr1<T>& operator = (const Shptr1<T>& wp)
	{
		_Wp=wp._shr;
		return *this;
	}
	//以下运算符重载函数实际并未使用到
	T& operator*()
	{
		return *_Wp;
	}
	T* operator->()
	{
		return _Wp;
	}
private :
	T* _Wp;
};

struct ListNode1
{
	int _data;
	//指针域---使用智能指针
	//存在循环引用---Shptr对象
	//Shptr<ListNode> Next;
	//Shptr<ListNode> perv;

	//解决循环引用---Wptr对象
	Wptr1<ListNode1> Next;
	Wptr1<ListNode1> perv;	
	  
	~ListNode1()
	{
		cout << "~ListNode()" << endl ;
	}
};

void Weak_Ptr_test()
{
	//不可直接实用Wptr定义对象，否则出错?
	cout << "Wptr:"<< endl;
	Shptr1<ListNode1> list1 ( new ListNode1);
	Shptr1<ListNode1> list2 ( new ListNode1);

 	cout << list1.Usercoun() << endl ;//打印计数器值
	cout << list2.Usercoun() << endl ;//创建时计数器+1

	list1->Next = list2;//节点链接
	list2->perv = list1;//链接时计数器不加1
	//链接之后的对象（节点）中的指针域不相互依赖，节点空间可以释放
    cout << list1.Usercoun() << endl ;//计数器值为1
	cout << list2.Usercoun() << endl ;//计数器值为1
	list1->_data = 6;
	cout << list1->_data << endl;
}
