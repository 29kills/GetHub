#pragma once
#include<iostream>

using namespace std;

template<class T>
class AutoPtr
{
public:
	AutoPtr(T* ap)//���캯��
		:_ptr(ap);//��ʼ������
	{}

	~AutoPtr()//����
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