#pragma once
#include<iostream>
#include<algorithm>
#include<functional>
#include<vector>
#include<string>
using namespace std;

//����3�����ü���--->ͨ������ķ����������Ƿ��ͷſռ�(Ȩ�ޱ���)
//ȱ�ݣ����ӣ�δ����ѭ����������(ָ�뻥ָ����˫������ѭ�����õ��¿ռ��޷��ͷ�)

//����ɾ����----����delete[]����(ͨ���º���ʵ��)
template<class T>
struct Delete//��ͨ�ͷ�
{
	void operator()(T* data)
	{
	    delete data;
	}
};

template<class T>
struct DeleteArry//�����ͷ�
{
	void operator()(T* data)
	{
	    delete []data;
	}
};
//�ر��ļ�
class Fclose
{
public:
	void operator()(FILE *f)//ͨ��������������ʵ�ַº���
	{
		cout << "Fclose" << endl ;
		fclose(f);
	}
};
//�Լ���ʵ��һ��free()ɾ����
struct Free
{
};

//ǰ������
template<class T>
class Wptr;

//����Ϊģ��Del����ȷ��ɾ���ķ�����ȱʡֵΪDelete
template<class T,class Del = Delete<T>>
class Shptr
{
	friend class Wptr<T>;//��Ԫ��
public :
	Shptr(T* sh = NULL)//ȱʡ����Ϊ��
		:_shr(sh)
		,_count(new size_t(1))//��ʼ��Ϊ1
	{}

	//sh1(sh)
	Shptr(const Shptr<T>& sh)//��������
		:_shr(sh._shr)
		,_count(sh._count)
	{
		(*_count)++;//����+1
	}
	//sh1=sh;
	Shptr<T>& operator= (const Shptr<T>& sh)//��ֵ�������غ���
	{
		if(_shr != sh._shr)//��Ϊsh=sh
		{
			if(--(*_count) == 0)//ֻ����һ�Σ���ɾ�����ڴ�ռ䣬�����¿ռ䣬������ԭ�ռ䣬�����¿ռ�
			{
				_del(_shr);//����Del���͵��ö�Ӧ��ɾ���࣬ʵ���ͷſռ�
				//delete _shr;
				delete _count;
			}
			_shr=sh._shr;
			_count=sh._count;
			(*_count)++;
		}
		return *this;//this���ö���ָ��(��Ϊsh)
	}
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

	~Shptr()//����������
	{
		if(-- (*_count) == 0)//ÿ����һ��-1����Ϊ0ʱ�ͷſռ�
			_del(_shr);//����Del���͵��ö�Ӧ��ɾ���࣬���ҵ��ö�Ӧ���е����������(),ʵ���ͷſռ�
	}
private://˽�г�Աֻ�������ڲ�����
	T* _shr;
	size_t* _count;//���ж���Ӧ����һ����������������Ϊָ��
	Del _del;//ɾ����ʽ
};

template<class T>
class Wptr//���ڴ���ѭ����������
{
public :
	Wptr() 
		:_Wp(NULL)
	{}

	Wptr(const Shptr<T>& wp)//�������캯��(��Shptr��Ϊ����)
		:_Wp(wp._shr)
	{}
	Wptr<T>& operator = (const Shptr<T>& wp)
	{
		_Wp=wp._shr;
		return *this;
	}
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

struct ListNode
{
	int _data;
	//ָ����---ʹ������ָ��
	//����ѭ������---Shptr����
	Shptr<ListNode> Next;
	Shptr<ListNode> perv;

	//���ѭ������---Wptr����
	//Wptr<ListNode> Next;
	//Wptr<ListNode> perv;	
	  
	~ListNode()
	{
		cout << "~ListNode()" << endl ;
	}
};

void Shptr_list_test()//˫���������
{
	cout << "Shptr:"<< endl;
	Shptr<ListNode> list1 ( new ListNode);
	Shptr<ListNode> list2 ( new ListNode);

	cout << list1.Usercoun() << endl ;//��ӡ������ֵ
	cout << list2.Usercoun() << endl ;//��ӡ������ֵ

	//�������䵼��ѭ����������
	list1->Next=list2;//�ڵ�����
	list2->perv=list1;//����ʱ������+1
	//����֮��Ķ��󣨽ڵ㣩�е�ָ�����໥�������½ڵ�ռ䲻���ͷ�
    cout << list1.Usercoun() << endl ;//������ֵΪ2
	cout << list2.Usercoun() << endl ;
}

void Shptr_test()//��������
{
	Shptr<int> sh(new int(2));
	*sh = 2;//��дsh.operator*()
	cout << sh.operator*() <<endl;

	Shptr<int> sh1(sh);//����
	*sh1 = 3;
	cout << sh1.operator*() <<endl;

	Shptr<int> sh2(new int(2));
	sh2.operator*()=3;
	sh1 = sh2; //sh2�ĵļ�������Ϊ2��ԭsh1�����٣�sh1ָ��sh2
	cout << sh1.operator*() <<endl;

	string *arr = new string[3];//��ͬ��string arr[3];//����string���ͣ���ֱ��д���߱ȽϺ�
	arr[0] = "123";
	cout <<"arr[0]=" <<arr[0] << endl;

	Shptr<string,DeleteArry<string>> sh3(new string[3]);//3��string����
	sh3[0] = "123";//�������ص�[]������ʵ�ֳ�ʼ��
	cout << sh3[0] << endl;

	Shptr<int,DeleteArry<int>> sh4(new int[3]);
	sh4[0] = 1;//�������ص�[]������ʵ�ֳ�ʼ��
	cout << sh4[0] << endl;

    Shptr<FILE,Fclose> sp4(fopen("readm.txt","w"));//�ر��ļ�
}


