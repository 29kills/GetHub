#pragma once
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

template<class T,class V>
struct BSTNode{
	T _key;
	V _value;
	size_t _count;  //节点作为根节点对应的节点数目
	BSTNode<T,V> *_left;
	BSTNode<T,V> *_right;
	
	BSTNode(T key,V value)
		:_key(key)
		,_value(value)
		,_count(1)
		,_left(NULL)
		,_right(NULL)
	{}
};

template<class T,class V>
class BSTree {
public:
	typedef struct BSTNode<T,V> BSTNode;
	BSTree()
		:_root(NULL)
	{}

	BSTree(const BSTree &bst) 
		:_root(NULL)
	{
		_root = _copy(_root,bst._root);  //深拷贝
	}


	BSTree &operator=(const BSTree &bst) {
		if (this != &bst) {
			BSTree<T,V> tmp(bst);
			swap(this->_root, tmp._root);  //注：此处交换的是root的地址
		}
		return *this;
	}

	//后序遍历删除
	~BSTree() {
		Delete(_root);
		_root = NULL;
	}

	int Size() {
		if (_root) {
			return _root->_count;
		}
	}

	int Size(BSTNode *node) {
		if (node) {
			return node->_count;
		}
		return 0;
	}

	void Delete(BSTNode* root) {
		if (root) {
			Delete(root->_left);
			Delete(root->_right);
			delete root;
			root = NULL;
		}
	}

	//树拷贝
	BSTNode* _copy(BSTNode *root, const BSTNode *bst) {
		if (bst == NULL) return NULL;

		root = new BSTNode(bst->_key,bst->_value);
		root->_count = bst->_count;
		if (bst->_left != NULL) {
			(root)->_left = _copy(root, bst->_left);
		}
		if (bst->_right) {
			(root)->_right = _copy(root, bst->_right);
		}
		return root;
	}
	/*
	void insert(T key,V value) {
		BSTNode *newNode = new BSTNode(key,value);
		if (_root == NULL) {
			_root = newNode;
		}
		
		BSTNode *InNode = _root;
		BSTNode *cur = _root;

		while (cur) {
			InNode = cur;
			if (cur->_key > key) {
				cur->_count++;
				cur = cur->_left;
			}
			else if (cur->_key < key) {
				cur->_count++;
				cur = cur->_right;
			}
			else {  //重复key，退出
				cur->_value = value;
				return;
			}
		}

		if (InNode->_key > key) {
			InNode->_left = newNode;
		}
		else {
			InNode->_right = newNode;
		}

	//	_root->_count = Size(_root)+1;
	}

	*/

	void insert(T key, V value) {
		_root = _insert(_root, key, value);
	}

	BSTNode* _insert(BSTNode* root,T key, V value) {
		if (root == NULL) {
			return new BSTNode(key, value);
		}
		if (root->_key > key) {
			root->_left = _insert(root->_left, key, value);
		}
		else if (root->_key < key) {
			root->_right = _insert(root->_right, key, value);
		}
		else {
			root->_value = value;
		}
		root->_count = Size(root->_left) + Size(root->_right) + 1;
		return root;
	}

	void InoPrint() {
		_InoPrint(_root);  //中序遍历
	}

	void _InoPrint(BSTNode *root) {
		if (root) {
			_InoPrint(root->_left);
			cout << "key:" << root->_key << "  value:" << root->_value << " " << endl;
			_InoPrint(root->_right);
		}
	}

	//查找
	V Find(T key) {
		BSTNode *cur = _root;
		while (cur) {
			if (cur->_key == key) {
				return cur->_value;
			}else if (cur->_key > key) {
				cur = cur->_left;
			} else {
				cur = cur->_right;
			}
		}
		return 0;
	}

	//查找向上取整的数
	V findNearUp(T key) {
		BSTNode *tmp = find_near_up(_root, key);
		if (tmp) {
			return tmp->_key;
		}
		else {
			return -1;
		}
	}

	BSTNode* find_near_up(BSTNode* root, T key) {
		if (root == NULL) {
			return NULL;
		}
		if (root->_key == key) {  
			return root;
		}
		if (root->_key < key) {  //root->key小于key值，则比key大值在右子树。
			return find_near_up(root->_right, key);
		}  //右子树未找到
		BSTNode *cur = find_near_up(root->_left, key);  //root->key 大与key,或右子树未找到，则在左子树找最接近key的值
		if (cur != NULL) return cur;  //找到相等的值，则返回该节点
		else return root;  //未找到，则根节点为最接近key的值
	}

	V findNearDown(T key) {
		BSTNode* tmp = find_near_down(_root, key);
		if (tmp) {
			return tmp->_key;
		}
		return -1;
	}

	BSTNode* find_near_down(BSTNode *root, T key) {
		if (root == NULL) return NULL;
		if (root->_key == key) {
			return root;
		}
		if (root->_key > key) {  //root->key > key,则最接近小于key的值在左子树
			return find_near_down(root->_left, key);
		}
		BSTNode *cur = find_near_down(root->_right, key);  //root->key < key,最接近key的值在右子树
		if (cur) return cur;  //找到最接近的值
		else return root;  //根为最接近的值
	}

	//查找第k大小的值。
	//如果左子数的节点个数 > k,则在左子树
	//如果左子的个数 < k 则在右子树。
	V find_sizeth(int k){
		return _find_sizeth(_root, k - 1);
	}

	V _find_sizeth(BSTNode* root, int k) {
		if (root == NULL) {
			return 0;
		}
		int size_left = Size(root->_left);
		if (size_left == k) return root->_value;
		if (size_left > k) {
			return _find_sizeth(root->_left, k);
		}
		if (size_left < k) {
			return _find_sizeth(root->_right, k - size_left - 1);
		}
	}

	//查找key的排名
	int rank(T key) {
		return _rank(_root, key)+1;  //此处统计从0算起
	}

	int _rank(BSTNode *root,T key) {
		if (root == NULL) {
			return -1;
		}

		if (root->_key < key) {  //右子树节点的排名=左子树节点个数+1（根节点）+右子树
			int size_right = _rank(root->_right, key);
			if (size_right < 0) {  //注：小于0，则说明未找到该数据，直接退出，不再加上之前计算的值。
				return size_right;
			}
			else {
				return Size(root->_left) + 1 + size_right;
			}
		}
		else if(root->_key > key){
			return _rank(root->_left, key);
		}
		else {
			return Size(root->_left);
		}
	}

	//节点删除
	//删除最小节点的问题。
	//向左遍历到最左的节点，将其上一个节点指向该节点不为空的节点上。删除该节点
	//注方向与原来的方向保持一致,同时更新size值
	
	void deleteMin() {
		BSTNode *del = NULL;
		_root = _deleteMin(_root,del);
		delete del;
	}
	//递归查找删除节点，并从树中移除该节点
	BSTNode* _deleteMin(BSTNode *root,BSTNode *&del) {
		if (root->_left == NULL) {
			del = root;
			return root->_right;
		}
		root->_left = _deleteMin(root->_left,del);
		root->_count = Size(root->_left) + Size(root->_right) + 1; //重新计算节点个数
		return root;
	}

	V keyMin() {
		BSTNode* tmp = _keyMin(_root);
		if (tmp) {
			return tmp->_key;
		}
		else {
			return -1;
		}
	}

	BSTNode* _keyMin(BSTNode *root) {
		if (root == NULL) {
			return NULL;
		}
		if (root->_left == NULL) {
			return root;
		}
		else {
			return _keyMin(root->_left);
		}
	}

	//输出某范围的数据min~max
	void minToMax(T min, T max) {
		_minToMax(_root, min, max);
	}

	void _minToMax(BSTNode *root, T min, T max) {
		if (root == NULL) {
			return;
		}
		if (root->_key > min) {
			_minToMax(root->_left, min, max);
		}
		if (min <= root->_key && max > root->_key) {
			cout << root->_key << endl;
		}
		if (root->_key < max) {
			_minToMax(root->_right, min, max);
		}
	}


	//删除任意某节点
	//删除节点只有左子树/右子树之一，删除节点，并让上一个节点指向不为空的左/右子树，方法同上
	//删除左右子树都不为空的节点：
	//方法1：在删除节点的左子树中找最最大节点作为替换节点，与删除节点进行数据交换，删除交换节点，方法同删除一个子树节点
	//方法2：删除节点的右子树最小值替换删除节点，修改替换节点的左右指针域。删除替换节点。
	void deleteKey(T key) {
		//_deleteKey(_root, key);
		_deleteKey2(_root, key);
	}

	//方法2：
	//寻找删除节点
	BSTNode* _deleteKey2(BSTNode* root, T key) {
		if (root == NULL) {
			return NULL;
		}

		//寻找删除节点
		if (root->_key > key) {
			root->_left = _deleteKey2(root->_left, key);
		}
		else if (root->_key < key) {
			root->_right = _deleteKey2(root->_right, key);
		}
		else {  //找到删除节点
			if (root->_left == NULL) {
				return root->_right;
			}
			else if (root->_right == NULL) {
				return root->_left;
			}
			else {  //左右节点都不为空
				BSTNode *del = root;
				del->_right = _deleteMin(del->_right,root);  //找出最小节点，并更新删除节点的右，并摘除，注：并未析构最小节点,
				root->_right = del->_right; 
				root->_left = del->_left;
				delete del;
			}
		}
		root->_count = Size(root->_left) + Size(root->_right) + 1;  //更新节点个数
		return root;  //返回替换后的节点
	}

	bool _deleteKey(BSTNode *&root, T key) {  //注：存在删除根节点的问题，此处使用二级指针。
		if (root == NULL) {
			return false;
		}

		if (root->_key > key) {
			_deleteKey(root->_left, key);
		}
		else if (root->_key < key) {
			_deleteKey(root->_right, key);
		}
		else {
			BSTNode *tmp = root;
			if (root->_left == NULL) {
				root = root->_right;
				delete tmp;
				tmp = NULL;
			}
			else if(root->_right == NULL){
				root = root->_left;
				delete tmp;
				tmp = NULL;
			}
			else {
				BSTNode* right_min = _keyMin(root->_right);
				_swap(root, right_min);
				_deleteKey(root->_right, right_min->_key);
			}
			if (root) {
				root->_count = Size(root->_left) + Size(root->_right) + 1;
			}
			return true;
		}
		if (root) {
			root->_count = Size(root->_left) + Size(root->_right) + 1;
		}
	}

	void _swap(BSTNode* left, BSTNode* right) {
		swap(left->_key, right->_key);
		swap(left->_value, right->_value);
	}

private:
	BSTNode *_root;
};

void test_BSTree() {

	BSTree<float,float> bst;
	bst.insert(1,1);
	cout << bst.Size() << endl;
	bst.insert(2, 2);
	cout << bst.Size() << endl;
	bst.InoPrint();
	

	BSTree<float,float> bst2(bst);
	cout << bst2.Size() << endl;
	bst2.insert(3, 2.1);
	bst2.InoPrint();
	bst.InoPrint();
	cout << bst2.Size() << endl;

	
	BSTree<float,float> bst3;
	//bst3 = bst;
	cout << "bst3" << endl;
	bst3.insert(3, 4.2);
	bst3.insert(2, 10);
	bst3.insert(1.9, 1.8);
	bst3.insert(4.1, 2.2);
	bst3.insert(3.2, 3.4);
	bst3.insert(5, 5);

	bst3.InoPrint();
	cout << "bst" << endl;
	bst.InoPrint();

	cout << bst.Size() << endl;
	cout << bst3.Size() << endl;

	cout << "find_near_up" << endl;
	cout << bst3.findNearUp(3.5) << endl;

	cout << "find_near_dowan" << endl;
	cout << bst3.findNearDown(3.8) << endl;

	cout << "rank" << endl;
	cout << bst3.rank(3.2) << endl;
	cout << bst3.rank(2.5) << endl;

	cout << "find_sizeth" << endl;
	cout << bst3.find_sizeth(6) << endl; 

	bst3.deleteMin();
	bst3.InoPrint();

	cout << "keyMin" << endl;
	cout << bst3.keyMin() << endl;

	bst3.InoPrint();
	cout << "deleteKye" << endl;
	bst3.deleteKey(4.1);
	bst3.InoPrint();
	

	cout << "minToMax" << endl;
	bst3.minToMax(3, 4);
	return;
}