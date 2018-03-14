#pragma once
#include<iostream>
#include<algorithm>
#include<functional>
#include<vector>
#include<string>
using namespace std;

//方法3：引用计数--->通过计算的方法来决定是否释放空间(权限保留)
//缺陷：复杂，未处理循环引用问题(指针互指：如双向链表，循环引用导致空间无法释放)

//定制删除器----处理delete[]问题(通过仿函数实现)
template<class T>
struct Delete//普通释放
{
	void operator()(T* data)
	{
	    delete data;
	}
};

template<class T>
struct DeleteArry//数组释放
{
	void operator()(T* data)
	{
	    delete []data;
	}
};
//关闭文件
class Fclose
{
public:
	void operator()(FILE *f)//通过操作符的重载实现仿函数
	{
		cout << "Fclose" << endl ;
		fclose(f);
	}
};
//自己再实现一个free()删除器
struct Free
{
};

//前置声明
template<class T>
class Wptr;

//类作为模板Del用于确定删除的方法，缺省值为Delete
template<class T,class Del = Delete<T>>
class Shptr
{
	friend class Wptr<T>;//友元类
public :
	Shptr(T* sh = NULL)//缺省设置为空
		:_shr(sh)
		,_count(new size_t(1))//初始化为1
	{}

	//sh1(sh)
	Shptr(const Shptr<T>& sh)//拷贝构造
		:_shr(sh._shr)
		,_count(sh._count)
	{
		(*_count)++;//计数+1
	}
	//sh1=sh;
	Shptr<T>& operator= (const Shptr<T>& sh)//赋值运算重载函数
	{
		if(_shr != sh._shr)//不为sh=sh
		{
			if(--(*_count) == 0)//只共用一次，则删除旧内存空间，共用新空间，否则保留原空间，共用新空间
			{
				_del(_shr);//根据Del类型调用对应的删除类，实现释放空间
				//delete _shr;
				delete _count;
			}
			_shr=sh._shr;
			_count=sh._count;
			(*_count)++;
		}
		return *this;//this即该对象指针(变为sh)
	}
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

	~Shptr()//析构，销毁
	{
		if(-- (*_count) == 0)//每调用一次-1，当为0时释放空间
			_del(_shr);//根据Del类型调用对应的删除类，并且调用对应类中的重载运算符(),实现释放空间
	}
private://私有成员只能在类内部访问
	T* _shr;
	size_t* _count;//所有对象应共用一个计数器，所以设为指针
	Del _del;//删除方式
};

template<class T>
class Wptr//用于处理循环引用问题
{
public :
	Wptr() 
		:_Wp(NULL)
	{}

	Wptr(const Shptr<T>& wp)//拷贝构造函数(以Shptr作为类型)
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
	//指针域---使用智能指针
	//存在循环引用---Shptr对象
	Shptr<ListNode> Next;
	Shptr<ListNode> perv;

	//解决循环引用---Wptr对象
	//Wptr<ListNode> Next;
	//Wptr<ListNode> perv;	
	  
	~ListNode()
	{
		cout << "~ListNode()" << endl ;
	}
};

void Shptr_list_test()//双向链表测试
{
	cout << "Shptr:"<< endl;
	Shptr<ListNode> list1 ( new ListNode);
	Shptr<ListNode> list2 ( new ListNode);

	cout << list1.Usercoun() << endl ;//打印计数器值
	cout << list2.Usercoun() << endl ;//打印计数器值

	//以下两句导致循环引用问题
	list1->Next=list2;//节点链接
	list2->perv=list1;//链接时计数器+1
	//链接之后的对象（节点）中的指针域相互依赖导致节点空间不会释放
    cout << list1.Usercoun() << endl ;//计数器值为2
	cout << list2.Usercoun() << endl ;
}

void Shptr_test()//计数测试
{
	Shptr<int> sh(new int(2));
	*sh = 2;//或写sh.operator*()
	cout << sh.operator*() <<endl;

	Shptr<int> sh1(sh);//拷贝
	*sh1 = 3;
	cout << sh1.operator*() <<endl;

	Shptr<int> sh2(new int(2));
	sh2.operator*()=3;
	sh1 = sh2; //sh2的的计数器变为2，原sh1被销毁，sh1指向sh2
	cout << sh1.operator*() <<endl;

	string *arr = new string[3];//等同于string arr[3];//三个string类型，但直接写后者比较好
	arr[0] = "123";
	cout <<"arr[0]=" <<arr[0] << endl;

	Shptr<string,DeleteArry<string>> sh3(new string[3]);//3个string类型
	sh3[0] = "123";//调用重载的[]函数，实现初始化
	cout << sh3[0] << endl;

	Shptr<int,DeleteArry<int>> sh4(new int[3]);
	sh4[0] = 1;//调用重载的[]函数，实现初始化
	cout << sh4[0] << endl;

    Shptr<FILE,Fclose> sp4(fopen("readm.txt","w"));//关闭文件
}


