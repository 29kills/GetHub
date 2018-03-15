#pragma once
#include<iostream>
#include<assert.h>
using namespace std;
//��������ʹ���������õݹ��ջʵ�ֱ���
typedef enum{Link,Thread}Pointtag; 

template<class T>
struct BinNode
{
	T _data;
	BinNode<T>* _left;
	BinNode<T>* _right;
	Pointtag _leftpg;
	Pointtag _rightpg;
	BinNode(const T& x)//���캯��
		:_data(x)//��ʼ���б�
		,_left(NULL)
		,_right(NULL)
		,_leftpg(Link)//��ʼ��ʼ��ΪLink
		,_rightpg(Link)//��ʼ��ʼ��ΪLink
	{}
};

//ʵ�ֵ�����---��ָ�����++����
template<class T,class ret,class ptr>
struct _TreeItterator
{
	typedef BinNode<T> DNode;
	typedef _TreeItterator<T,ret,ptr> Self;
	
	DNode* _node;
	_TreeItterator(DNode* node)
		:_node(node)
	{}
	//���������
	ret operator*()//ȡֵ
	{
		return _node->_data;
	}
	ret operator->()//ȡ��ַ
	{
		return &(operator*())
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
//���������
template<class T,class ret,class ptr>
struct _InOrderTreeItterator : public _TreeItterator<T,ret,ptr>//�������
{
	typedef _InOrderTreeItterator<T,ret,ptr> Self;

	_InOrderTreeItterator(DNode* node)//���캯��
		:_TreeItterator(node)//���ø���Ĺ���
	{}

    Self& operator++()
	{
		if(_node->_rightpg == Thread)
			_node = _node->_right;
		else//Link
		{
			_node = _node->_right;
			while(_node->_leftpg == Link)//�ߵ������
			{
				_node = _node->_left;
			}
		}
		return *this;
	}

	Self& operator--()
	{
		assert(_node->_left);//��Ϊ��һ���ڵ�(��һ���ڵ��ǰһ��ΪNULL));
		if(_node->_leftpg == Link)
		{
			_node = _node->_left;
		}
		else 
		{
			DNode* right = _node->_left;
			while(right && right->_rightpg == Thread)
			{
				right = right->_left;
			}
			_node = right;
		}
		return *this;
	}

	Self& operator--(int)
	{
		Self tmp(*this);
		--*this;
		return tmp;
	}
};

template<class T,class ret,class ptr>
struct _PreOrderTreeItterator : public _TreeItterator<T,ret,ptr>//ǰ�����
{
	typedef _PreOrderTreeItterator<T,ret,ptr> Self;
	_PreOrderTreeItterator(DNode* node)
		:_TreeItterator(node)
	{}

	Self& operator++()
	{
		if(_node->_leftpg == Link)
			_node = _node->_left;
		else
		{
			_node = _node->_right;
		}
		return *this;
	}

	Self& operator++(int)
	{
		Self tmp(*this);//����++֮ǰ��ֵ
			++*this;//ǰ��++���Զ�����++��
		return tmp;
	}
	//ǰ���޷�ʵ��--
};


template<class T>
class Tool
{
	typedef BinNode<T> Node;
public :
	typedef _InOrderTreeItterator<T,T&,T*> InIterator;//���������
	typedef _PreOrderTreeItterator<T,T&,T*> PreIterator;//ǰ�������

	InIterator Inbegin()
	{
		Node* left = _tree;
		while(left && left->_leftpg == Link)//�����������ڵ�
		{
			left = left->_left;
		}
		return InIterator(left);//���ù���
	}

	InIterator InEnd()
	{
		return InIterator(NULL);
	}

	PreIterator Prebegin()
	{
		return PreIterator(_tree);
	}

	PreIterator PreEnd()
	{
		return PreIterator(NULL);
	}


	//���������
	Tool(T* arr,const size_t size,T indelid)
	{
		assert(arr);
		size_t indiv = 0 ;
		_tree = GetTree(arr,size,indiv,indelid);
	}
	Node* GetTree(T* arr,const size_t size,size_t& indiv,T indelid)
	{
		Node* ncell = NULL;
		if(arr[indiv] != indelid && indiv < size)
		{
		    ncell = new Node(arr[indiv]);
			ncell->_left = GetTree(arr,size,++indiv,indelid);//ע������Ӧʹ��ǰ��++������д�ɺ���++�������������ת������
			ncell->_right = GetTree(arr,size,++indiv,indelid);
		}
        return ncell;
	}
	//����������
	void xsh()//����������
	{
		Node* prev = NULL;
		xsh(_tree,prev);
		if(prev)
		    prev->_rightpg = Thread;//�������һ��
	}
	void xsh(Node* tree,Node*&  prev)//ֻ�������Ľڵ㣬����ڵ�ǰ�ִ����Ҳ�����һ�ִ����豣����һ�ֵĽڵ㣩
	{
		//Node* prev =NULL;//������һ���ڵ�
		if(!tree)
			return ;
		if(tree->_left == NULL)//������ǰ��
		{
			tree->_leftpg = Thread;
			tree->_left = prev;
		}
		if(prev != NULL && prev->_right == NULL)//����ǰ��һ�ڵ����
		{
			prev->_rightpg = Thread;
			prev->_right = tree;
		}
		prev = tree;//���浱ǰ�ڵ�
		if(tree->_leftpg == Link)//�ж��Ƿ���ʹ�
			xsh(tree->_left,prev);
		if(tree->_rightpg == Link)
			xsh(tree->_right,prev);
	}
	//��������������
	void xsh_print()//����������
	{
		xsh_print(_tree);
		cout << endl;
	}
	void xsh_print(Node* tree)
	{
		if(tree == NULL)
			return ;
		Node* cur = tree;
		while(cur)
		{
			while(cur->_leftpg == Link)//ֱ�ӷ���
			{
				cout << cur->_data ;
				cur = cur->_left;
			}
			cout << cur->_data ;//�����˳�ʱ�Ľڵ�
			cur = cur->_right;//���������⴦��
		}
	}
	//����������
	void Inxsh()
	{
		Node* prev = NULL;
		Inxsh(_tree,prev);
		if(prev)
		    prev->_rightpg = Thread;//�������һ���ڵ�
	}
	void Inxsh(Node* tree,Node*& prev)//prev��ʹ�����ã������´ν���ݹ�ʱ���ܸı�prevֵ
	{
		
		if(tree == NULL)
			return ;
		Inxsh(tree->_left,prev);
		if(tree->_left == NULL)
		{
			tree->_leftpg = Thread;
			tree->_left = prev;
		}
		
		if(prev && prev->_right == NULL)
		{
			prev->_right = tree;
			prev->_rightpg = Thread;
			
		}
		prev = tree;
		Inxsh(tree->_right,prev);
	}
	//��������������
	void Inxsh_print()
	{
		Inxsh_print(_tree);
		cout << endl;
	}
	void Inxsh_print(Node* tree)//��������������
	{
		//1 �ҵ�����ڵ� 2 ��������ֱ�ӷ��ʺ�̽ڵ�(��)ע��ΪNULL���� 3 ��������������з���
		while(tree)
		{
			while(tree->_leftpg == Link)//�ҵ�����ڵ�
			{
				tree = tree->_left;
			}
			cout << tree->_data ;
			while(tree && tree->_leftpg == Thread)//�������Ľڵ�ֱ�ӷ��ʺ��(ѭ������������)
			{
				tree = tree->_right;
				if(!tree)//�ڵ�Ϊ�գ�����
					break;
				cout << tree->_data;
			}
			if(tree)
				tree = tree->_right;
		}
	}
	//����������
	void Tree_print()//ǰ�����
	{
		first_print(_tree);
		cout << endl;
	}
	void first_print(Node* tree)
	{
		if(tree == NULL)
		{
			return ;
		}
		cout << tree->_data ;
		if(tree->_left)
			first_print(tree->_left);
		if(tree->_right)
			first_print(tree->_right);
	}
private :
	Node* _tree;
};

void Tree_test()
{
	char ch[] = {'a','b','d','#','#','g','#','#','c','e','#','#'};
	char arr[] = {'a','b','d','f','#','#','m','#','#','g','#','#','c','e','#','#','#','#'};
	size_t size = sizeof(ch)/sizeof(ch[0]);
	Tool<char> tree(ch,size,'#');
	tree.Tree_print();
	cout << endl;

	tree.xsh();
	tree.xsh_print();

	Tool<char>::PreIterator it = tree.Prebegin();//ǰ�������
	while(it != tree.PreEnd())
	{
		cout << *it ;
		++it;
	}
	cout << endl;

	size_t sz = sizeof(arr)/sizeof(arr[0]);
	Tool<char> tree2(arr,sz,'#');
	tree2.Tree_print();
	cout << endl;

	tree2.Inxsh();
	tree2.Inxsh_print();
	cout << endl;
	
	cout << "����" << endl;
	Tool<char>::InIterator it1 = tree2.Inbegin();//���������
	cout << "*it1:"<< *it1 << endl;

	it1++;
	cout << "*it1++:"<< *it1 << endl;
	it1++;
	cout << "*it1++:"<< *it1 << endl;	

	it1--;
	cout <<"*it1--:"<< *it1 << endl;

	while(it1 != tree2.InEnd())
	{
		cout << *it1 ;
		++it1;
	}
	cout << endl;
}