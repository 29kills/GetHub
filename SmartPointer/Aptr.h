#pragma once
#include<iostream>
using namespace std;
//����ָ��---��һ���ࣺ���캯�����ٿռ䣬���������ͷſռ�
//����1��Ȩ��ת��--->�������Ȩ��ת�Ƹ���һ�����󣬽��ָ��ͬһ��ַ(����ͬһ��Ա)�Ķ���ͷſռ�����
//ȱ�ݣ�Ȩ��ת�ƺ�Ķ��󣬲����ٶ�ת��Ȩ���˵ĳ�Ա���в������������
template<class T>
class Aptr
{
public :
	Aptr(T* ap)
		:_ptr(ap)
	{}
	//ap1(ap)
	Aptr(Aptr<T>& ap)//�������캯��ʵ��Ȩ��ת��
		:_ptr(ap._ptr)//ap����Ȩ��ap1
	{
		ap._ptr=NULL;//ap����Ȩ�ͷ�
	}
	//ap1=ap2;
	Aptr<T>& operator=(Aptr<T>& ap)//��ֵ����������
	{
		if(this != &ap)//���Ǳ���
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
	T& operator*()//���������,���ж�˽�����ݽ��в���
	{
		return *_ptr;
	}
	T* operator->()
	{
		return _ptr;
	}
private : //˽����ֵ�ⲿ����ֱ�ӷ���
	T* _ptr;
};

struct AA
{
	int  aa;
	int  bb;
};

void Aptr_test()
{
	 Aptr<int> ap(new int(2));//����һ������ͬʱ����2��int�ռ�
	 *ap=10;
	 cout << ap.operator*() <<endl;
	 Aptr<int> ap1=ap;//��ap���������ap1(�˴�Ϊǳ������������һ��_ptr�ռ�)
	 //������ظ��ͷ�ptr�Ŀռ䣬���´��󡣿�ʹ��Ȩ��ת�Ʒ�������apȨ��ת�Ƹ�ap1��ap���ڲ���Ȩ��ת�Ʊ���ptr
	 //Ȩ��ת����ȱ�ݣ�Ȩ��ת�ƺ󣬶������ٶ�ת��Ȩ�޵ı���ptr�������������

	 Aptr<int> ap3(new int(2));
	 ap1=ap3;//ap3qȨ��ת��ap1

	 AA *p1=new AA;//AA�൱��һ����(����һ������p1,ͬʱ���ٿռ�)
	 p1->aa=10;
	 p1->bb=20;

	 Aptr<AA> ap2(new AA);
	 ap2->aa=10;//ͨ��������������أ��ٵ���ptr������aa
	 ap2->bb=20;//��ʵ��p2->operator->()->bb��ptr��һ���ṹ�����ͣ�


}