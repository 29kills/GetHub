#pragma once
#include<iostream>
#include<assert.h>
using namespace std;
//线索化可使二叉树不用递归和栈实现遍历
typedef enum{Link,Thread}Pointtag; 

template<class T>
struct BinNode
{
	T _data;
	BinNode<T>* _left;
	BinNode<T>* _right;
	Pointtag _leftpg;
	Pointtag _rightpg;
	BinNode(const T& x)//构造函数
		:_data(x)//初始化列表
		,_left(NULL)
		,_right(NULL)
		,_leftpg(Link)//开始初始化为Link
		,_rightpg(Link)//开始初始化为Link
	{}
};

//实现迭代器---像指针可以++访问
template<class T,class ret,class ptr>
struct _TreeItterator
{
	typedef BinNode<T> DNode;
	typedef _TreeItterator<T,ret,ptr> Self;
	
	DNode* _node;
	_TreeItterator(DNode* node)
		:_node(node)
	{}
	//运算符重载
	ret operator*()//取值
	{
		return _node->_data;
	}
	ret operator->()//取地址
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
//中序迭代器
template<class T,class ret,class ptr>
struct _InOrderTreeItterator : public _TreeItterator<T,ret,ptr>//中序迭代
{
	typedef _InOrderTreeItterator<T,ret,ptr> Self;

	_InOrderTreeItterator(DNode* node)//构造函数
		:_TreeItterator(node)//调用父类的构造
	{}

    Self& operator++()
	{
		if(_node->_rightpg == Thread)
			_node = _node->_right;
		else//Link
		{
			_node = _node->_right;
			while(_node->_leftpg == Link)//走到最左侧
			{
				_node = _node->_left;
			}
		}
		return *this;
	}

	Self& operator--()
	{
		assert(_node->_left);//不为第一个节点(第一个节点的前一个为NULL));
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
struct _PreOrderTreeItterator : public _TreeItterator<T,ret,ptr>//前序迭代
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
		Self tmp(*this);//保存++之前的值
			++*this;//前置++（自动调用++）
		return tmp;
	}
	//前序无法实现--
};


template<class T>
class Tool
{
	typedef BinNode<T> Node;
public :
	typedef _InOrderTreeItterator<T,T&,T*> InIterator;//中序迭代器
	typedef _PreOrderTreeItterator<T,T&,T*> PreIterator;//前序迭代器

	InIterator Inbegin()
	{
		Node* left = _tree;
		while(left && left->_leftpg == Link)//遍历到最左侧节点
		{
			left = left->_left;
		}
		return InIterator(left);//调用构造
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


	//构造二叉树
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
			ncell->_left = GetTree(arr,size,++indiv,indelid);//注：引用应使用前置++，不可写成后置++，否则存在类型转化问题
			ncell->_right = GetTree(arr,size,++indiv,indelid);
		}
        return ncell;
	}
	//先序线索化
	void xsh()//先序线索化
	{
		Node* prev = NULL;
		xsh(_tree,prev);
		if(prev)
		    prev->_rightpg = Thread;//处理最后一个
	}
	void xsh(Node* tree,Node*&  prev)//只处理不满的节点，左侧在当前轮处理，右侧在下一轮处理（需保存上一轮的节点）
	{
		//Node* prev =NULL;//保存上一个节点
		if(!tree)
			return ;
		if(tree->_left == NULL)//当处理当前左
		{
			tree->_leftpg = Thread;
			tree->_left = prev;
		}
		if(prev != NULL && prev->_right == NULL)//处理当前上一节点的右
		{
			prev->_rightpg = Thread;
			prev->_right = tree;
		}
		prev = tree;//保存当前节点
		if(tree->_leftpg == Link)//判断是否访问过
			xsh(tree->_left,prev);
		if(tree->_rightpg == Link)
			xsh(tree->_right,prev);
	}
	//先序线索化遍历
	void xsh_print()//线索化遍历
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
			while(cur->_leftpg == Link)//直接访问
			{
				cout << cur->_data ;
				cur = cur->_left;
			}
			cout << cur->_data ;//访问退出时的节点
			cur = cur->_right;//当作子问题处理
		}
	}
	//中序线索化
	void Inxsh()
	{
		Node* prev = NULL;
		Inxsh(_tree,prev);
		if(prev)
		    prev->_rightpg = Thread;//处理最后一个节点
	}
	void Inxsh(Node* tree,Node*& prev)//prev需使用引用，否则下次进入递归时不能改变prev值
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
	//中序线索化遍历
	void Inxsh_print()
	{
		Inxsh_print(_tree);
		cout << endl;
	}
	void Inxsh_print(Node* tree)//中序线索化遍历
	{
		//1 找到最左节点 2 线索化了直接访问后继节点(右)注意为NULL问题 3 否则当作子问题进行访问
		while(tree)
		{
			while(tree->_leftpg == Link)//找到最左节点
			{
				tree = tree->_left;
			}
			cout << tree->_data ;
			while(tree && tree->_leftpg == Thread)//线索化的节点直接访问后继(循环输出连续后继)
			{
				tree = tree->_right;
				if(!tree)//节点为空，跳出
					break;
				cout << tree->_data;
			}
			if(tree)
				tree = tree->_right;
		}
	}
	//遍历二叉树
	void Tree_print()//前序遍历
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

	Tool<char>::PreIterator it = tree.Prebegin();//前序迭代器
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
	
	cout << "中序：" << endl;
	Tool<char>::InIterator it1 = tree2.Inbegin();//中序迭代器
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