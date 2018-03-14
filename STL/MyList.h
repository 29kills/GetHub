#pragma once 
#include<assert.h>
#include"Iterator.h"
template <class T>
struct _ListNode//双向链表
{
	 T _data;
	_ListNode<T>* _prev;
	_ListNode<T>* _next;
	_ListNode(const T& x)
		:_data(x)
		,_prev(NULL)
		,_next(NULL)
	{}
};

//迭代器---是一种容器的接口，用于访问容器中的元素，提供对对象的间接访问
template<class T,class ref,class pre>
struct ListIterator
{
	typedef _ListNode<T> Node;
	typedef ListIterator<T,ref,pre> Self;
	typedef ref Ref;
	typedef pre Pre;
	Node* _node;
	ListIterator(Node* node)//构造
		:_node(node)
	{}
	//运算符重载
	ref operator*()//返回数据
	{
		return _node->_data;
	}
	pre operator->()//返回地址
	{
		return &(_node->_data);
	}
	Self& operator++()//前置++(迭代器)
	{
		_node = _node->_next;
		return *this;//迭代器
	}
	Self& operator++(int)//后置++(迭代器)
	{
		Self tmp(*this);//保存当前位置
		_node = _node->_next;//后移
		return tmp;
	}
	Self& operator--()//前置--(迭代器)
	{
		_node = _node->_prev;
		return *this;//迭代器
	}
	Self& operator--(int)//后置--(迭代器)
	{
		Self tmp(*this)
		_node = _node->_prev;
		return tmp;//迭代器
	}

	bool operator!=(const Self& s)
	{
		return _node != s._node;
	}
	bool operator==(const Self& s)
	{
		return _node == s._node;
	}
};

template<class T>
class mylist//容器
{
	typedef _ListNode<T> Node;//Node是原始类型，不需重载运算符
public :
	typedef ListIterator<T,T&,T*> Iterator;//Iterator是自定义类型，运算符需重载
	typedef ListIterator<T,const T&,const T*> const_Iterator;//运算符需重载
	typedef ReverseIterator<Iterator> RIterator;//反向迭代器
	typedef ReverseIterator<const_Iterator> const_RIterator;//反向

	RIterator RBegin()
	{
		return End();
		//return ((RIterator)(End()._node));
	}
	RIterator REnd()
	{
		return Begin();
	}

	const_RIterator RBegin()const 
	{
		return End();
	}
	const_RIterator REnd()const
	{
		return Begin();//调用const修饰的Begin
	}

	const_Iterator Begin()const//不许修改
	{
		return const_Iterator(_head->_next);
	}

	const_Iterator End()const 
	{
		return const_Iterator(_head);
	}

	Iterator Begin() 
	{
		return Iterator(_head->_next);//返回头节点的下一个
	}

	Iterator End()
	{
		return Iterator(_head);//最后一个元素也应进入，所以用_head
	}

	mylist()//构造
		:_head(new Node(T()))//构造一个头节点(传一个缺省参数)
	{
		_head->_prev = _head;//指向自己
		_head->_next = _head;
	}

	void Insert(Iterator pos,const T& x)//pos位置插入
	{
		//注意pos类型
		Node* cur = pos._node;
		Node* prev = cur->_prev;
		Node* newNode = new Node(x);

		newNode->_next = cur;
		cur->_prev = newNode;

		newNode->_prev = prev;
		prev->_next = newNode;
		
	}
	Iterator Erase(Iterator& pos)//删除(使用引用处理迭代器失效)
	{
		assert(pos != End());//头不可删（无节点）
		Node* next = (pos._node)->_next;
		Node* prev = pos._node->_prev;

		prev->_next = next;
		next->_prev = prev;

		delete pos._node;
		pos = prev;//指向当前位置（删除的位置）
		return Iterator(next);//返回当前节点，处理迭代器失效问题
		//注意返回类型
	}
	void PopBack()//尾删
	{
		Erase(Iterator(End()._node->_prev));//End()是取下一个
	}

	void PushFront(const T& data)//头插
	{
		Insert(Begin(),data);
	}

	void PushBack(const T& data)//尾插
	{
		Insert(End(),data);//pos位置插入
	}

protected :
	Node* _head;
};

void print_mylist(const mylist<int>& L2)
{
	mylist<int>::const_Iterator it = L2.Begin();//const 迭代器
	while(it != L2.End())
	{
		cout << *it << ' ';
		++it;
	}
	cout << endl;
}

void print_erase(mylist<int>& L1)
{
	mylist<int>::Iterator it = L1.Begin();//普通迭代器
	while(it != L1.End())
	{
		if(*it%2==0)
	       L1.Erase(it);//返回当前位置可不用接收，迭代器不会失效
		++it;
	}
	cout << endl;
}
template<class T>
void print_RIterator(const mylist<T>& L1)
{
	mylist<int>::const_RIterator Re = L1.RBegin();//反向迭代器
	//mylist<int>::RIterator Re = L1.RBegin();//反向迭代器
	while(Re != L1.REnd())
	{
		//*Re = 5;//const修饰不可修改
		cout << *Re << ' ';
		Re++;//调用后置++重载运算符函数
	}
	cout << endl;
}
void mylist_test()
{
	mylist<int> L1;
	L1.PushBack(1);
	L1.PushBack(2);
	L1.PushBack(3);
	print_RIterator(L1);

	L1.PopBack();
	L1.PushFront(4);
	print_mylist(L1);
	print_erase(L1);
	print_mylist(L1);

}