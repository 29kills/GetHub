#pragma once
#include<iostream>

using namespace std;

template<class T>
class AutoPtr
{
public:
	AutoPtr(T* ap)//构造函数
		:_ptr(ap);//初始化对象
	{}

	~AutoPtr()//析构
	{
		delete ptr;
	}
private:
	T* ptr;
}

void AutoPtr_test(void)
{
	AutoPtr<int> ap(new int(2));

}