#pragma once
#include<iostream>
//各种智能指针，库中都已实现
#include<memory>
using namespace std;
//std::shared_ptr<int> p1(new int[3]);//实用库中的，

//方法2：防拷贝--->只声明不定义或将拷贝构造设置为私有的，类外不可使用，从而防止进行拷贝构造
//自己设计delete[]问题？？？---ScopedArry
template<class T>
class Scptr
{
public :
	Scptr(T* sp)//构造函数
		:_spr(sp)
	{}
	//运算符重载,进行对私有数据进行操作
	T& operator*()
	{
		return *_spr;
	}
	T* operator->()
	{
		return _spr;
	}
	~Scptr()
	{
		if(_spr)
		delete _spr;
	}
private:
	Scptr(const Scptr<T>& sp);//拷贝构造设置成私有的，防止拷贝
	Scptr<T>& operator=(const Scptr<T>& sp);//赋值运算与重载
private: //私有数值外部不可直接访问
	T* _spr;
};

void Scptr_test()
{
	Scptr<int> sp(new int(2));
	*sp = 1;//sp.operator*()=1;
	cout << *sp << endl;
	//Scptr<int> sp2(sp);//错误拷贝构造为私有，不可拷贝
}
