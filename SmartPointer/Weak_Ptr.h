//Wptr������Shared_Ptr����---ģ�岻֧�ַ�����룬��������.h�ļ����ɵ��ô��ļ��е�ģ�庯��
//.h�ļ��е��࣬��������.h�ļ�ֱ��ʹ�ã�����ͬһ�����̲��ɳ�����ͬ������
#pragma once
#include<iostream>
using namespace std ;

//ǰ������
template<class T>
class Wptr1;

template<class T>
class Shptr1
{
	friend class Wptr1<T>;//��Ԫ��
public :
	Shptr1(T* sh = NULL)//ȱʡ����Ϊ��
		:_shr(sh)
		,_count(new size_t(1))//��ʼ��Ϊ1
	{}
	/*
	//�����ò�����ô˿�������͸�ֵ���㺯�������ǵ�������ģ����Ըö���ļ���������ı�
	//sh1(sh)
	Shptr1(const Shptr1<T>& sh)//��������
		:_shr(sh._shr)
		,_count(sh._count)
	{
		(*_count)++;//����+1
	}
	//sh1=sh;
	Shptr1<T>& operator= (const Shptr1<T>& sh)//��ֵ�������غ���
	{
		if(_shr != sh._shr)//��Ϊsh=sh
		{
			if(--(*_count) == 0)//ֻ����һ�Σ���ɾ�����ڴ�ռ䣬�����¿ռ䣬������ԭ�ռ䣬�����¿ռ�
			{
				delete _shr;
				delete _count;
			}
			_shr=sh._shr;
			_count=sh._count;
			(*_count)++;
		}
		return *this;//this���ö���ָ��(��Ϊsh)
	}*/
	//���������
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

	size_t Usercoun()//ȡ������ֵ
	{
		return *_count;
	}

	~Shptr1()//����������
	{
		if(-- (*_count) == 0)//ÿ����һ��-1����Ϊ0ʱ�ͷſռ�
			delete _shr;
	}
private://˽�г�Աֻ�������ڲ�����
	T* _shr;
	size_t* _count;//���ж���Ӧ����һ����������������Ϊָ��
};

//������---����ı�����������ֵ����������ָͨ��
//Wptr��Ҫ���ڴ���ѭ���������⣬����ָ���򴦶�����󣬲�ֱ�Ӷ�����󣬶�����Shptr�������
template<class T>
class Wptr1//���ڴ���ѭ����������
{
public :
	Wptr1() 
		:_Wp(NULL)
	{}

	Wptr1(const Shptr1<T>& wp)//�������캯��(��Shptr��Ϊ����)
		:_Wp(wp._shr)
	{}
	Wptr1<T>& operator = (const Shptr1<T>& wp)
	{
		_Wp=wp._shr;
		return *this;
	}
	//������������غ���ʵ�ʲ�δʹ�õ�
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
	//ָ����---ʹ������ָ��
	//����ѭ������---Shptr����
	//Shptr<ListNode> Next;
	//Shptr<ListNode> perv;

	//���ѭ������---Wptr����
	Wptr1<ListNode1> Next;
	Wptr1<ListNode1> perv;	
	  
	~ListNode1()
	{
		cout << "~ListNode()" << endl ;
	}
};

void Weak_Ptr_test()
{
	//����ֱ��ʵ��Wptr������󣬷������?
	cout << "Wptr:"<< endl;
	Shptr1<ListNode1> list1 ( new ListNode1);
	Shptr1<ListNode1> list2 ( new ListNode1);

 	cout << list1.Usercoun() << endl ;//��ӡ������ֵ
	cout << list2.Usercoun() << endl ;//����ʱ������+1

	list1->Next = list2;//�ڵ�����
	list2->perv = list1;//����ʱ����������1
	//����֮��Ķ��󣨽ڵ㣩�е�ָ�����໥�������ڵ�ռ�����ͷ�
    cout << list1.Usercoun() << endl ;//������ֵΪ1
	cout << list2.Usercoun() << endl ;//������ֵΪ1
	list1->_data = 6;
	cout << list1->_data << endl;
}
