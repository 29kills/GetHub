//反向迭代器---使用适配器实现其它类型迭代器
#pragma once
#include"MyList.h"

//适配器---适配不同的迭代器
template<class Iterator>//适配器（Iterator--->ListIterator(迭代器)）
struct ReverseIterator
{
	Iterator _it;
	//typename作用是让编译器去找Iterator::Ref类型
	ReverseIterator(Iterator it)
		:_it(it)
	{}
	typename Iterator::Ref operator*()
	{
		Iterator it = _it;
		return *(--it);//调用的是(ListIterator)中重载运算符的--
	}
	typename Iterator::Pre operator->()
	{
		return &(operator*());
	}

	ReverseIterator operator++()//前置
	{
		--_it;
		return *this;
	}

	ReverseIterator operator++(int)//后置
	{
		ReverseIterator tmp(*this);
		--_it;
		return tmp;
	}

	ReverseIterator operator--()
	{
		++_it;
		return *this;
	}
	bool operator != (ReverseIterator<Iterator>& s)
	{
		return _it != s._it;
	}
	bool operator == (ReverseIterator<Iterator>& s)
	{
		return _it == s._it;
	}
};