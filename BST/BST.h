#pragma once
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

template<class T,class V>
struct BSTNode{
	T _key;
	V _value;
	size_t _count;  //�ڵ���Ϊ���ڵ��Ӧ�Ľڵ���Ŀ
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
		_root = _copy(_root,bst._root);  //���
	}


	BSTree &operator=(const BSTree &bst) {
		if (this != &bst) {
			BSTree<T,V> tmp(bst);
			swap(this->_root, tmp._root);  //ע���˴���������root�ĵ�ַ
		}
		return *this;
	}

	//�������ɾ��
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

	//������
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
			else {  //�ظ�key���˳�
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
		_InoPrint(_root);  //�������
	}

	void _InoPrint(BSTNode *root) {
		if (root) {
			_InoPrint(root->_left);
			cout << "key:" << root->_key << "  value:" << root->_value << " " << endl;
			_InoPrint(root->_right);
		}
	}

	//����
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

	//��������ȡ������
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
		if (root->_key < key) {  //root->keyС��keyֵ�����key��ֵ����������
			return find_near_up(root->_right, key);
		}  //������δ�ҵ�
		BSTNode *cur = find_near_up(root->_left, key);  //root->key ����key,��������δ�ҵ�����������������ӽ�key��ֵ
		if (cur != NULL) return cur;  //�ҵ���ȵ�ֵ���򷵻ظýڵ�
		else return root;  //δ�ҵ�������ڵ�Ϊ��ӽ�key��ֵ
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
		if (root->_key > key) {  //root->key > key,����ӽ�С��key��ֵ��������
			return find_near_down(root->_left, key);
		}
		BSTNode *cur = find_near_down(root->_right, key);  //root->key < key,��ӽ�key��ֵ��������
		if (cur) return cur;  //�ҵ���ӽ���ֵ
		else return root;  //��Ϊ��ӽ���ֵ
	}

	//���ҵ�k��С��ֵ��
	//����������Ľڵ���� > k,����������
	//������ӵĸ��� < k ������������
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

	//����key������
	int rank(T key) {
		return _rank(_root, key)+1;  //�˴�ͳ�ƴ�0����
	}

	int _rank(BSTNode *root,T key) {
		if (root == NULL) {
			return -1;
		}

		if (root->_key < key) {  //�������ڵ������=�������ڵ����+1�����ڵ㣩+������
			int size_right = _rank(root->_right, key);
			if (size_right < 0) {  //ע��С��0����˵��δ�ҵ������ݣ�ֱ���˳������ټ���֮ǰ�����ֵ��
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

	//�ڵ�ɾ��
	//ɾ����С�ڵ�����⡣
	//�������������Ľڵ㣬������һ���ڵ�ָ��ýڵ㲻Ϊ�յĽڵ��ϡ�ɾ���ýڵ�
	//ע������ԭ���ķ��򱣳�һ��,ͬʱ����sizeֵ
	
	void deleteMin() {
		BSTNode *del = NULL;
		_root = _deleteMin(_root,del);
		delete del;
	}
	//�ݹ����ɾ���ڵ㣬���������Ƴ��ýڵ�
	BSTNode* _deleteMin(BSTNode *root,BSTNode *&del) {
		if (root->_left == NULL) {
			del = root;
			return root->_right;
		}
		root->_left = _deleteMin(root->_left,del);
		root->_count = Size(root->_left) + Size(root->_right) + 1; //���¼���ڵ����
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

	//���ĳ��Χ������min~max
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


	//ɾ������ĳ�ڵ�
	//ɾ���ڵ�ֻ��������/������֮һ��ɾ���ڵ㣬������һ���ڵ�ָ��Ϊ�յ���/������������ͬ��
	//ɾ��������������Ϊ�յĽڵ㣺
	//����1����ɾ���ڵ�����������������ڵ���Ϊ�滻�ڵ㣬��ɾ���ڵ�������ݽ�����ɾ�������ڵ㣬����ͬɾ��һ�������ڵ�
	//����2��ɾ���ڵ����������Сֵ�滻ɾ���ڵ㣬�޸��滻�ڵ������ָ����ɾ���滻�ڵ㡣
	void deleteKey(T key) {
		//_deleteKey(_root, key);
		_deleteKey2(_root, key);
	}

	//����2��
	//Ѱ��ɾ���ڵ�
	BSTNode* _deleteKey2(BSTNode* root, T key) {
		if (root == NULL) {
			return NULL;
		}

		//Ѱ��ɾ���ڵ�
		if (root->_key > key) {
			root->_left = _deleteKey2(root->_left, key);
		}
		else if (root->_key < key) {
			root->_right = _deleteKey2(root->_right, key);
		}
		else {  //�ҵ�ɾ���ڵ�
			if (root->_left == NULL) {
				return root->_right;
			}
			else if (root->_right == NULL) {
				return root->_left;
			}
			else {  //���ҽڵ㶼��Ϊ��
				BSTNode *del = root;
				del->_right = _deleteMin(del->_right,root);  //�ҳ���С�ڵ㣬������ɾ���ڵ���ң���ժ����ע����δ������С�ڵ�,
				root->_right = del->_right; 
				root->_left = del->_left;
				delete del;
			}
		}
		root->_count = Size(root->_left) + Size(root->_right) + 1;  //���½ڵ����
		return root;  //�����滻��Ľڵ�
	}

	bool _deleteKey(BSTNode *&root, T key) {  //ע������ɾ�����ڵ�����⣬�˴�ʹ�ö���ָ�롣
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