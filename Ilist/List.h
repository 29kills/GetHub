#pragma once

typedef int DataType;

struct ListNode
{
	ListNode* _next;
	ListNode* _prev;

	DataType _data;

	ListNode(DataType x)
		:_data(x)
		,_next(NULL)
		,_prev(NULL)
	{}
};

class List
{
	typedef ListNode Node;
public:
	List()
		:_head(new Node(DataType()))
	{
		_head->_next = _head;
		_head->_prev = _head;
	}

	// l2(l1)
	List(const List& l)
		:_head(new Node(DataType()))
	{
		_head->_next = _head;
		_head->_prev = _head;

		Node* cur = l._head->_next;
		while (cur != l._head)
		{
			PushBack(cur->_data);
			cur = cur->_next;
		}
	}

	// l1 = l2
	List& operator=(List l)
	{
		swap(_head, l._head);

		return *this;
	}

	~List()
	{
		Node* cur = _head->_next;
		while (cur != _head)
		{
			Node* next = cur->_next;
			delete cur;
			cur = next;
		}

		delete _head;
		_head = NULL;
	}

	void PushBack(DataType x)
	{
		//Node* tail = _head->_prev;
		//Node* newnode = new Node(x);
		//// tail newnode _head

		//tail->_next = newnode;
		//newnode->_prev = tail;

		//newnode->_next = _head;
		//_head->_prev = newnode;

		Insert(_head, x);
	}

	void PushFront(DataType x)
	{
		Insert(_head->_next, x);
	}

	void PopBack()
	{
		Erase(_head->_prev);
	}

	void PopFront()
	{
		Erase(_head->_next);
	}

	void Insert(Node* pos, DataType x)
	{
		assert(pos);
		Node* newnode = new Node(x);
		Node* prev = pos->_prev;
		// prev newnode pos
		prev->_next = newnode;
		newnode->_prev = prev;
		newnode->_next = pos;
		pos->_prev = newnode;
	}

	void Erase(Node* pos)
	{
		assert(pos != _head);

		Node* prev = pos->_prev;
		Node* next = pos->_next;

		delete pos;
		prev->_next = next;
		next->_prev = prev;
	}

	void Print()
	{
		Node* cur = _head->_next;
		while (cur != _head)
		{
			cout<<cur->_data<<" ";
			cur = cur->_next;
		}
		cout<<endl;
	}

private:
	Node* _head;
};

void TestList()
{
	List l1;
	l1.PushBack(1);
	l1.PushBack(2);
	l1.PushBack(3);
	l1.PushBack(4);
	l1.Print();

	List l2 = l1;
	l2.Print();

	l2.PopBack();
	l2.PopBack();
	l2.PopBack();
	l2.PopBack();
	l2.Print();
}