#pragma once
#include<iostream>
using namespace std;
//智能指针---是一个类：构造函数开辟空间，析构函数释放空间
//方法1：权限转移--->将对象的权限转移给另一个对象，解决指向同一地址(共用同一成员)的多次释放空间问题
//缺陷：权限转移后的对象，不可再对转移权限了的成员进行操作，否则崩溃
template<class T>
class Aptr
{
public :
	Aptr(T* ap)
		:_ptr(ap)
	{}
	//ap1(ap)
	Aptr(Aptr<T>& ap)//拷贝构造函数实现权限转移
		:_ptr(ap._ptr)//ap管理权给ap1
	{
		ap._ptr=NULL;//ap管理权释放
	}
	//ap1=ap2;
	Aptr<T>& operator=(Aptr<T>& ap)//赋值运算与重载
	{
		if(this != &ap)//不是本身
		{
			if(_ptr)
				delete _ptr;
			_ptr = ap._ptr;
			ap._ptr = NULL;
		}
		return *this;
	}

	~Aptr()
	{
		cout << _ptr << endl;
		delete _ptr;
	}
	T& operator*()//运算符重载,进行对私有数据进行操作
	{
		return *_ptr;
	}
	T* operator->()
	{
		return _ptr;
	}
private : //私有数值外部不可直接访问
	T* _ptr;
};

struct AA
{
	int  aa;
	int  bb;
};

void Aptr_test()
{
	 Aptr<int> ap(new int(2));//建立一个对象，同时开辟2个int空间
	 *ap=10;
	 cout << ap.operator*() <<endl;
	 Aptr<int> ap1=ap;//将ap拷贝构造给ap1(此处为浅拷贝，即共用一个_ptr空间)
	 //会进行重复释放ptr的空间，导致错误。可使用权限转移方法，将ap权限转移给ap1，ap不在操作权限转移变量ptr
	 //权限转移有缺陷：权限转移后，对象不能再对转移权限的变量ptr操作，否则崩溃

	 Aptr<int> ap3(new int(2));
	 ap1=ap3;//ap3q权限转给ap1

	 AA *p1=new AA;//AA相当与一个类(创建一个对象p1,同时开辟空间)
	 p1->aa=10;
	 p1->bb=20;

	 Aptr<AA> ap2(new AA);
	 ap2->aa=10;//通过调用运算符重载，再调用ptr最后调用aa
	 ap2->bb=20;//其实是p2->operator->()->bb（ptr是一个结构体类型）


}