#pragma once 
#include<assert.h>
#include"Iterator.h"
template <class T>
struct _ListNode//˫������
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

//������---��һ�������Ľӿڣ����ڷ��������е�Ԫ�أ��ṩ�Զ���ļ�ӷ���
template<class T,class ref,class pre>
struct ListIterator
{
	typedef _ListNode<T> Node;
	typedef ListIterator<T,ref,pre> Self;
	typedef ref Ref;
	typedef pre Pre;
	Node* _node;
	ListIterator(Node* node)//����
		:_node(node)
	{}
	//���������
	ref operator*()//��������
	{
		return _node->_data;
	}
	pre operator->()//���ص�ַ
	{
		return &(_node->_data);
	}
	Self& operator++()//ǰ��++(������)
	{
		_node = _node->_next;
		return *this;//������
	}
	Self& operator++(int)//����++(������)
	{
		Self tmp(*this);//���浱ǰλ��
		_node = _node->_next;//����
		return tmp;
	}
	Self& operator--()//ǰ��--(������)
	{
		_node = _node->_prev;
		return *this;//������
	}
	Self& operator--(int)//����--(������)
	{
		Self tmp(*this)
		_node = _node->_prev;
		return tmp;//������
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
class mylist//����
{
	typedef _ListNode<T> Node;//Node��ԭʼ���ͣ��������������
public :
	typedef ListIterator<T,T&,T*> Iterator;//Iterator���Զ������ͣ������������
	typedef ListIterator<T,const T&,const T*> const_Iterator;//�����������
	typedef ReverseIterator<Iterator> RIterator;//���������
	typedef ReverseIterator<const_Iterator> const_RIterator;//����

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
		return Begin();//����const���ε�Begin
	}

	const_Iterator Begin()const//�����޸�
	{
		return const_Iterator(_head->_next);
	}

	const_Iterator End()const 
	{
		return const_Iterator(_head);
	}

	Iterator Begin() 
	{
		return Iterator(_head->_next);//����ͷ�ڵ����һ��
	}

	Iterator End()
	{
		return Iterator(_head);//���һ��Ԫ��ҲӦ���룬������_head
	}

	mylist()//����
		:_head(new Node(T()))//����һ��ͷ�ڵ�(��һ��ȱʡ����)
	{
		_head->_prev = _head;//ָ���Լ�
		_head->_next = _head;
	}

	void Insert(Iterator pos,const T& x)//posλ�ò���
	{
		//ע��pos����
		Node* cur = pos._node;
		Node* prev = cur->_prev;
		Node* newNode = new Node(x);

		newNode->_next = cur;
		cur->_prev = newNode;

		newNode->_prev = prev;
		prev->_next = newNode;
		
	}
	Iterator Erase(Iterator& pos)//ɾ��(ʹ�����ô��������ʧЧ)
	{
		assert(pos != End());//ͷ����ɾ���޽ڵ㣩
		Node* next = (pos._node)->_next;
		Node* prev = pos._node->_prev;

		prev->_next = next;
		next->_prev = prev;

		delete pos._node;
		pos = prev;//ָ��ǰλ�ã�ɾ����λ�ã�
		return Iterator(next);//���ص�ǰ�ڵ㣬���������ʧЧ����
		//ע�ⷵ������
	}
	void PopBack()//βɾ
	{
		Erase(Iterator(End()._node->_prev));//End()��ȡ��һ��
	}

	void PushFront(const T& data)//ͷ��
	{
		Insert(Begin(),data);
	}

	void PushBack(const T& data)//β��
	{
		Insert(End(),data);//posλ�ò���
	}

protected :
	Node* _head;
};

void print_mylist(const mylist<int>& L2)
{
	mylist<int>::const_Iterator it = L2.Begin();//const ������
	while(it != L2.End())
	{
		cout << *it << ' ';
		++it;
	}
	cout << endl;
}

void print_erase(mylist<int>& L1)
{
	mylist<int>::Iterator it = L1.Begin();//��ͨ������
	while(it != L1.End())
	{
		if(*it%2==0)
	       L1.Erase(it);//���ص�ǰλ�ÿɲ��ý��գ�����������ʧЧ
		++it;
	}
	cout << endl;
}
template<class T>
void print_RIterator(const mylist<T>& L1)
{
	mylist<int>::const_RIterator Re = L1.RBegin();//���������
	//mylist<int>::RIterator Re = L1.RBegin();//���������
	while(Re != L1.REnd())
	{
		//*Re = 5;//const���β����޸�
		cout << *Re << ' ';
		Re++;//���ú���++�������������
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