#pragma once
#include<iostream>
using namespace std;

//简单的智能指针

template<class T>
class Smart//智能指针类
{
public :
	Smart(T* data)//构造同时初始化
		:_ptr(data)	
	{}
	T& operator*()//防指针的*运算
	{
		return *_ptr;//返回数据
	}
	T* operator->()
	{
		return _ptr;//返回地址
	}
	~Smart()
	{
		if(_ptr)
			delete _ptr;
	}
private:
	T* _ptr;
};

struct Cell
{
	int _x;
	int _y;
};
void Smart_test()
{
	//指针---不能自动释放空间
	int *p = new int(0);
	cout << *p << endl;

	//防指针---智能指针---自动调用析构，释放空间
	Smart<int> s(new int(1));
	cout << *s << endl;
	
	Smart<int> s2(new int);
	*s2 = 2;
	cout << *s2 << endl;

	Smart<Cell> s3(new Cell);//结构体类型
	s3->_x = 3;//编译处理方法实际是s3->->_x,实现的
	s3->_y = 4;
	cout << s3->_x << endl;

	/*未处理拷贝问题---多个指针(对象)指向同一地址，导致同一空间多次释放问题
	  s2 = s;//s2也指向s地址空间，导致s两次析构，出错
	  解决方法：
	  1、管理权转移，带有缺陷的设计---->看Sptr.h文件
	  2、防拷贝，简单粗暴-------------->看Scoped_Ptr.h文件
	  3、引用计数，实用更复杂---------->看Shared_Ptr文件
	  4、解决(3)循环引用问题，弱指针------>看Weak_Ptr.h文件
	*/

	/*各种智能指针，库中都已实现
      #include<memory>//头文件
      std::shared_ptr<int> p1(new int[3]);//使用库中的
	  C++11还可使用boost中的方法
	  boost::shared_ptr<int> p1(new int[3]);//使用库中的
	  */
}