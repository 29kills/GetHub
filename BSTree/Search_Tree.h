#pragma once
#include<iostream>
#include<assert.h>
using namespace std;

/*
一、插入节点：从头节点向下遍历与节点比较，小的走左侧，大的走右侧，直到为叶子节点，插在不满的节点上(即父节点)(所以需保存父节点)
二、查找：根据大小，遍历查找
三、删除：
1、从根节点进行遍历，找到要删除的节点(根据大小去找)
1、删除节点左为空，让其父节点指向其右子树，右为空，让其父节点指向其左子树
注：若删除的为根节点，则parent = NULL;所以需特殊处理，root->left = NULL直接让root = root->_right;删除root,有为空与之类似
2、左，右节点都不为空----替换法:找其右子树的最左节点，并与之替换(数据)，删除替换的节点

递归解法：
注：由于递归只能返回到上一层，所以递归每层必须有返回值
一、递归插入，注：使用引用传参，为空(左，或右指针)则让其指向新节点，返回true
不为空,cur->key < Key 递归右子树，cur->key > Key 递归左子树，else (相等返回false)
二、递归查找
三、递归删除
1、递归查找删除节点
2、左，或右为空，让删除节点指向其子节点
3、删除左，右孩子都不为空的节点
方法1：使用非递归，改变替代节点的父节点的指向其子节点的方法（与非递归该代码块相同）
方法2：问题转化成删除替代节点的子问题---递归
*/
//试着添加迭代器(中序)---需对数进行修改，每个节点需添加一个指针域，指向父节点，
//注：父节点前添加一个空节点，左，右指针域指向树的最左叶子和最右叶子，根节点是该节点的父亲节点，其它相同，只是无数据
//K为数据类型的模板，V为数据的含义模板
template<class K,class V>
struct SearchTreeNode
{
	K _key;//关键码
	V _value;
	SearchTreeNode<K,V>* _left;
	SearchTreeNode<K,K>* _right;

	SearchTreeNode(const K& key,const V& value)
		:_key(key)
		,_value(value)
		,_left(NULL)
		,_right(NULL)
	{}
};

template<class K,class V>
class SearchTree
{
	typedef SearchTreeNode<K,V> Node;
public:
	SearchTree()
		:_root(NULL)
	{}

	//插入节点：从头节点向下遍历与节点比较，小的走左侧，大的走右侧，直到为叶子节点，插在不满的节点上(即父节点)(所以需保存父节点)
	bool Puch(const K& Key,const V& value)
	{
		if(_root == NULL)
		{
			_root = new Node(Key,value);
			return true;
		}
		else
		{
			Node* cur = _root;
			Node* parent = NULL;//保存当前结点，即下一个节点的父节点
			while(cur)
			{
				if(Key < cur->_key)
				{
					parent = cur;
					cur = cur->_left;
				}
				else if(Key > cur->_key)
				{
					parent = cur;
					cur = cur->_right;
				}
				else
					return false ;//数值相等，错误
			}
			if(parent->_key < Key)
				parent->_right = new Node(Key,value);
			else
				parent->_left = new Node(Key,value);
			return true;
		}
	}

	//递归插入，注：使用引用传参，为空(左，或右指针)则让其指向新节点，返回true
	//不为空,cur->key < Key 递归右子树，cur->key > Key 递归左子树，else (相等返回false)
	//注：由于递归只能返回到上一层，所以递归必须有返回值
	bool Insert(const K& Key)
	{
		return Insert(_root,Key);
	}
	bool Insert(Node*& cur,const K& Key)
	{
		if(cur == NULL)//引用指针域，为空直接让指针域指向新的节点
		{
			cur = new Node(Key);
			return true;
		}

		if(cur->_key < Key)
			return Insert(cur->_right,Key);
		else if(cur->_key > Key)
			return Insert(cur->_left,Key);
		else
			return false;
	}

	//查找
	//const Node* Find(const K& Key)//搜索二叉树不支持修改，修改后就可能不满足其性质
	Node* Find(const K& Key)//value需改
	{
		Node* cur = _root;
		while(cur)
		{
			if(cur->_key == Key)
				return cur;
			else if(cur->_key < Key)
				cur = cur->_right;
			else 
				cur = cur->_left;
		}
		return NULL;
	}

	//递归查找
	Node* Search(const K& Key)
	{
		return Search(_root,Key);
	}
	Node* Search(Node* cur,const K& Key)
	{
		if(cur == NULL)
			return NULL;
		if(cur->_key < Key)
			return Search(cur->_right,Key);
		else if(cur->_key > Key)
			return Search(cur->_left,Key);
		else
			return cur;
	}

	//删除：1、从根节点进行遍历，找到要删除的节点(根据大小去找)
	//      1、删除节点左为空，让其父节点指向其右子树，右为空，让其父节点指向其左子树
	//      注：若删除的为根节点，则parent = NULL;所以需特殊处理，root->left = NULL直接让root = root->_right;删除root,有为空与之类似
	//      2、左，右节点都不为空----替换法:找其右子树的最左节点，并与之替换(数据)，删除替换的节点
	
	bool Delete(const K& Key)
	{
		Node* cur = _root;
		Node* parent = NULL;
		Node* del = NULL;
		//查找要删除的节点
		while(cur)
		{
			if(Key > cur->_key)
			{
				parent = cur;//保存当前结点（下个节点的父亲节点）
				cur = cur->_right;//指向右子树
			}
			else if(Key < cur->_key)
			{
				parent = cur;
				cur = cur->_left;//指向左子树
			}
			//注意：若要删除的节点(cur)为根节点或不存在,则parent = NULL,删除时需对此情况特殊处理
			else//找到
			{
				del = cur;//cur为将要删除的节点
				//cur左或右为空---父节点链接其子节点
				if(cur->_left == NULL)//左为空
				{
					if(parent == NULL)//删除根节点
						_root = _root->_right;
					else
					{
						if(parent->_left == cur)//cur链接在父节点的左
						    parent->_left = cur->_right;//父节点的左链接右子树
					    else//cur链接在父节点的右
						    parent->_right = cur->_right;//父节点的右链接右子树
					}
				}
				else if(cur->_right == NULL)
				{
					if(parent == NULL)
						_root = _root->_left;
					else
					{
						if(parent->_left == cur)//cur链接在父节点的左
						    parent->_left = cur->_left;//父节点的左链接右子树
					    else//cur链接在父节点的右
						    parent->_right = cur->_left;//父节点的右链接右子树
					}
				}
				//左，右都不为空，找其右子树的最左节点，并与之替换，删除替换的节点
				//注：若删除节点的右子树，无左节点则该右节点(右树根)当作左节点，而不是NULL
				else//左，右都不为空
				{
					Node* parent = cur;//存替代节点的父节点
					Node* sub = cur->_right;//找替代节点,在其右子树找最左节点
					while(sub->_left)//找最左节点
					{
						sub = sub->_left;
					}
					cur->_key = sub->_key;
					//删除替代节点
					//由于sub为最左节点，所以父节点指向sub的右节点
					if(parent->_left == sub)//父的左链接sub的右
					{
						parent->_left = sub->_right;
					}
					else//父的右链接sub的右
						parent->_right = sub->_right;
				 del = sub;
				}
			 delete del;
			 return true;
			}
		}
		//未找到
		return false;
	}

	void print()
	{
		print(_root);
	}
	void print(Node* cur)
	{
		if(cur == NULL)
			return ;
		print(cur->_left);
		cout << cur->_key << ' ';
		print(cur->_right);
	}

	//递归删除
	bool Remove(const K& Key)
	{
		return Remove(_root,Key);
	}
	bool Remove(Node*& cur,const K& Key)
	{
		//递归查找删除节点
		if(cur == NULL)//未找到
			return false;
		if(cur->_key < Key)//左查找
			Remove(cur->_right,Key);
		else if(cur->_key > Key)//右查找
			Remove(cur->_left,Key);
		//更改新指向，删除原指向
		else //找到删除节点
		{
			Node* del = cur;
			if(cur->_left == NULL)//删除节点的左孩子为空
			{
				cur = cur->_right;//删除节点指向其右孩子
				delete del;//转化成子问题，需放在此处删除
			}
			else if(cur->_right == NULL)//删除节点的右孩子为空
			{
				cur = cur->_left;//删除节点指向其左孩子
				delete del;//转化成子问题，需放在此处删除
			}
			//删除节点，左，右孩子都不为空
			//方法1：使用非递归，改变替代节点的父节点的指向其子节点的方法（与非递归该代码块相同）
			//方法2：问题转化成删除替代节点的子问题---递归
			else
			{
				Node* sub = cur->_right;//替代节点为该节点的右子树上的最左节点(若无左节点则该右节点当作左节点，而不是NULL)
				while(sub->_left)
				{
					sub = sub->_left;
				}
				cur->_key = sub->_key;
				Remove(_root,sub->_key);//问题转化成删除替代节点的子问题
			}
			//delete del;//递归删除左，右不为空节点时，不可放在此处删除，因为转化成子问题后，此处会发生多次删除问题
			return true;
		}
	}
private:
	Node* _root;
};

/*
void SearchTree_test()
{
	SearchTree<int> st;
	st.Puch(1);
	st.Puch(2);
	st.Puch(4);
	st.Puch(3);
	st.Puch(5);
	st.print();
	cout << endl;
	cout << st.Find(3)->_key << endl;
	st.Delete(1);
	cout << st.Delete(4) << endl;
	cout << st.Delete(4) << endl;
	cout << st.Delete(8) << endl;
	cout << st.Delete(5) << endl;
	cout << st.Delete(2) << endl;
	st.Puch(5);
	st.Puch(0);
	st.Insert(6);
	cout << st.Delete(3) << endl;
	cout << st.Delete(2) << endl;
	cout << st.Find(8) << endl;
	cout << st.Find(6) << endl;
	cout << st.Search(8) << endl;
	cout << st.Search(6) << endl;

	cout << st.Remove(6) << endl;
	cout << st.Remove(6) << endl;
	cout << st.Remove(0) << endl;
	cout << endl;
	st.print();
}

//添加V表示数据的含义，如个数，意思等
*/
//防词典功能
#include<string>
void BST_test()
{
	SearchTree<string,string> st;
	st.Puch("tree","树");
	st.Puch("hello","你好");
	st.Puch("men","男");
	st.Puch("baby","baby");
	st.Puch("ok","好");

	string word;
	while(1)
	{
		cout  << "输入word:" ;
		cin >> word ;
	    SearchTreeNode<string,string>* ret = st.Find(word);
		if(ret)
	    cout << ret->_value << endl;
		else
		cout << "No Word" << endl;
	}
}