#pragma once

#pragma once
#include<iostream>
using namespace std;
enum Color{RED,BLACK};
template<class T,class V>
struct RBTNode
{
	T _key;
	T _value;
	RBTNode<T,V>* _left;
	RBTNode<T,V>* _right;
	RBTNode<T,V>* _parent;
	Color _col;

	RBTNode(const T& data,const V& value)
	:_key(data)
	,_value(value)
	,_left(NULL)
	,_right(NULL)
	,_parent(NULL)
	,_col(RED)
	{}
};

template<class T,class V>
class Tree{
	typedef RBTNode<T,V> Node;
	public:
	Tree()
		:_root(NULL)
	{}

	//采用循环的方式插入节点
	bool Insert(const T& key,const V& value){
		if(_root == NULL){
			_root = new Node(key, value);
			_root->_col = BLACK;
			return true;
		}
		Node* parent = _root;
		Node* cur = _root;
		//寻找插入节点
		while(cur){
			parent = cur;
			if(cur->_key < key)      cur = cur->_right;
			else if(cur->_key > key) cur = cur->_left;
			else return false;//数据相同，已存在，不插入
		}
		//插入节点
		cur = new Node(key,value);
		if(parent->_key > key) parent->_left = cur;
		else  parent->_right = cur;
		cur->_parent = parent;
		//调整
		while(parent && parent->_col == RED){
			Node* grandfather = parent->_parent;
			if(parent == grandfather->_left){//父节点在祖父的左
				Node* uncle = grandfather->_right;
				if(uncle && uncle->_col == RED){//叔叔存在为红色--->调整颜色
					parent->_col = BLACK;
					uncle->_col = BLACK;
					grandfather->_col = RED;
					//向上层处理
					cur = grandfather;
					parent = cur->_parent;
				}
				else{ // 叔叔不存在或为黑色---->调整平衡
					//Node* tmp = parent;
					if (cur == parent->_right) {//cur在父的左，双旋
						RotateL(parent);//先左旋
						parent = parent->_parent;
					}
					RotateR(grandfather);//右旋
					parent->_col = BLACK;
					//tmp->_col = BLACK;//不可直接写parent，由于调整后parent发生改变，调整实际不在是对原parent调整
					grandfather->_col = RED;
					//grandfather->_col = BLACK;
				}
			}
			else{ //父在祖父的右	
				Node* uncle = grandfather->_left;
				if(uncle && uncle->_col == RED){//叔叔存在且为红色
					parent->_col = BLACK;
					uncle->_col = BLACK;
					grandfather->_col = RED;
					//向上层处理
					cur = parent;
					parent = parent->_parent;
				}
				else{ //叔叔不存在或为黑色
					//Node* tmp = parent;//保存原parent的位置，防止调整后parent位置发生变化，调整颜色导致错误
					if (cur == parent->_left) {//折线型，双旋
						RotateR(parent);//右旋 parent;
						parent = parent->_parent;
					}
					RotateL(grandfather);//左旋 parent->_parent;
					parent->_col = BLACK;
					//tmp->_col = BLACK;
					grandfather->_col = RED;
				}
			}
			_root->_col = BLACK;  //将根节点变为黑色
		}  //循环结束
		return true;
	}


	//1、根为黑色，否则返回false
	//递归遍历
	//2、无连续的红色节点否则返回false(j节点为红色，父节点为红色)
	//3、每条路径黑色节点数量相同
	//先计算一条路径(最左侧)黑色节点数量，依次为基准
	//再计算其它路径黑色节点数量，不相同返回false
	bool Banlance(){
		if(_root && _root->_col == RED){
			printf("根为红色!\n");
			return false;
		}
		int num = 0;
		Node* cur = _root;
		while(cur){
			if(cur->_col == BLACK) ++num;
			cur = cur->_left;
		}
		int count = 0;
		return _Balance(_root,num,count);
	}

	bool _Balance(Node* cur,int num,int count){
		if(cur == NULL){
			if(num != count)
				return false;
			return true;
		}
		if(cur->_col == RED && cur->_parent->_col == RED){
			printf("连续的红色节点！\n");
			return false;
		}
		if (cur->_col == BLACK) {
			count++;
		}
		return _Balance(cur->_left,num,count) && _Balance(cur->_right,num,count);
	}
	
	void RotateR(Node* parent){
		Node* pparent = NULL;
		Node* SubL = parent->_left;
		Node* SubLR = SubL->_right;

		parent->_left = SubLR;
		if (SubLR) {
			SubLR->_parent = parent;
		}
		//问题
		SubL->_right = parent;
		pparent = parent->_parent;
		parent->_parent = SubL;
		//处理新的父亲的父亲节点
		SubL->_parent = pparent;
		if(pparent == NULL){
		_root = SubL;
		}
		else{
			if(parent == pparent->_left) pparent->_left = SubL;
			else pparent->_right = SubL;
		SubL->_parent = pparent;
		}
		_root->_parent = NULL;
	}
	

	//左旋
	void RotateL(Node* parent){
		Node* SubR = parent->_right;
		Node* SubRL = SubR->_left;

		parent->_right = SubRL;
		if (SubRL) {//更新SubRL的父亲
			SubRL->_parent = parent;
		}
		SubR->_left = parent;
		Node* pparent = parent->_parent;
		parent->_parent = SubR;
		//处理新的父亲的父亲节点
		SubR->_parent = pparent;
		if (pparent == NULL) {
			_root = SubR;
		}
		else{
			if(parent == pparent->_left) pparent->_left = SubR;
			else pparent->_right = SubR;
			SubR->_parent = pparent;
		}
		_root->_parent = NULL;
	}

	void InOrder(){
		_InOrder(_root);
	}

	void _InOrder(Node* root){
		if(root){
			_InOrder(root->_left);
			cout << root->_key << ' ' <<endl;
			_InOrder(root->_right);
		}
	}

	private:
	Node* _root;
};


void RBSTree_test(){
	int a[] = { 16,3,7,11,9,26,18,14,15,1,2};
	//int a[] = {3,1,2,4,5,6,7,8};
	//int a[] = {1,2,3};
	//int a[] = { 16,3,7};

	int i = 0;
	Tree<int,int> t;
	for(; i < sizeof(a)/sizeof(a[0]); ++i){
		t.Insert(a[i],i);
	}
	t.InOrder();
	if (t.Banlance()) {
		printf("是红黑树！\n");
	}
}








/*
//红黑树-----是一棵近似平衡的二叉搜索树
//为什么是一个近似平衡的搜索树？
通过对任何一条从根节点到叶子节点的颜色约束，保证最长路径不超过最短路径的二倍
二倍：是为了减少调整树的开销
时间复杂度：O(lgN)  空间复杂度：O(N)
性质：
1、每个节点不是红色就是黑色的，根节点的颜色是黑色的
2、红色节点的两个子节点是黑色的，即无连续的红色节点
3、根节点到叶子节点的黑色节点数量相同，即每条路径上的黑色节点数量相同
4、叶子节点是黑色的（叶子---空节点）

为什么满足以上性质红黑树就能近似平衡？
因为，无连续的红色节点，且每条路径上的黑色节点个数相同，所以最短路径与最长路径差小于2，否则不能满足每条路径黑色节点数相同。
如：最短路径只有一个黑色节点，最长路径有右红色也有黑色节点。

每次插入红色节点：
若插入黑色节点，则会改变路径上黑色节点个数，插入红色节点，再看其它条件是否满足，不满足进行调整

颜色调整：
1、插入的节点(cur)的父节点(p)为黑色，则直接插入

2、插入的节点(cur)的父节点(p)为红色，则看叔叔节点
2.1、叔叔节点存在且为红色---->将父节点和叔叔节点变为黑色，祖父节点变为红色，
之后若祖父节点为根节点，则再变为黑色
否则，cur,p,g向上移动，即cur = p,再判断cur的父节点，和叔叔节点（循环2步的以上步骤，直到p为黑色节点为止）。

2.2、叔叔节点不存在或为黑色节点，直线形式---->单旋转
p为g的左孩子，cur为p的左孩子---->右单旋
p为g的右孩子，cur为p的右孩子---->左单旋
再将p变为黑，g变为红。

2.3、叔叔节点为黑色或不存在，折现形式-------->双旋
p为g的左孩子，cur为p的右孩子---->则对p左单旋--->右单旋
p为g的右孩子，cur为p的左孩子---->则对p右单旋--->左单旋
再将p变为黑，g变为红。

注：由于调整后，parent的位置发生变化，在对原来位置的节点颜色调整会导致错误，所以调整之前保存parent的位置，在对保存的节点的颜色进行调整

节点删除：
节点的删除与AVL树的删除类似，分为5中情况
增删查改的时间复杂度为0(lgN)

*/