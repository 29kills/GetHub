//���������---ʹ��������ʵ���������͵�����
#pragma once
#include"MyList.h"

//������---���䲻ͬ�ĵ�����
template<class Iterator>//��������Iterator--->ListIterator(������)��
struct ReverseIterator
{
	Iterator _it;
	//typename�������ñ�����ȥ��Iterator::Ref����
	ReverseIterator(Iterator it)
		:_it(it)
	{}
	typename Iterator::Ref operator*()
	{
		Iterator it = _it;
		return *(--it);//���õ���(ListIterator)�������������--
	}
	typename Iterator::Pre operator->()
	{
		return &(operator*());
	}

	ReverseIterator operator++()//ǰ��
	{
		--_it;
		return *this;
	}

	ReverseIterator operator++(int)//����
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