
//红黑树实现方法1
#include<iostream>
using namespace std;

enum RB {RED,BLACK};
template<class T,class V>
struct RBTNode {
	T _key;
	V _value;
	enum RB _color;
	int _count;
	RBTNode<T, V> *_left;
	RBTNode<T,V> *_right;

	RBTNode(T key = (T), V value = (V)) 
		:_key(key)
		,_value(value)
		,_color(RED)
		,_count(1)
		,_left(NULL)
		,_right(NULL)
	{}
};

template<class T, class V>
class RBTree {
public:
	typedef RBTNode<T, V> RBTNode;
	//构造，拷贝构造，赋值运算符重载
	RBTree()
		:_root(NULL)
	{}

	int size() {
		size(_root);
	}

	int size(RBTNode* node) {
		if (node)  return node->_count;
		else return 0;
	}

	void put(T key, V value) {
		_root = _put(_root, key, value);  //递归添加
		_root->_color = BLACK; //将根变为黑色
	}
	RBTNode* _put(RBTNode* root, T key, V value) {
		//创建新节点
		if (root == NULL) {
			return new RBTNode(key, value);
		}

		//递归查找插入位置
		if (root->_key < key) {
			root->_right = _put(root->_right, key, value);
		}
		else if (root->_key > key) {
			root->_left = _put(root->_left, key, value);
		}
		else {
			root->_value = value;
		}

		//找到了插入节点位置root,并且已将新节点插入
		//递归进行红黑调整(插入节点都为红色)，从下向上调整树的颜色，直到根节结束
		//1、插入位置节点为红色，新节点插入在右侧，进行一次左旋转
		//2、插入位置节点为红色，新节点插入在左侧，进行一次右旋转，
		//3、出现左右子节点都为红色节点，将左右子节点变为黑色，根点变为红色
		if (isRED(root->_right) && !isRED(root->_left))       root = rotateLeft(root);  //右旋节点为插入位置的节点
		if (isRED(root->_left) && isRED(root->_left->_left))  root = rotateRight(root);  //注：左旋的节点为插入位置节点的上一个节点
		if (isRED(root->_left) && isRED(root->_right)) root = flipColor(root);  //出现左右子节点都为红色，则进行颜色变换

		//节点数目统计
		root->_count = size(root->_left) + size(root->_right) + 1;
	
		return root;
	}

	bool isRED(RBTNode* node) {
		if (node == NULL) return false;
		if (node->_color == RED) return true;
		else return false;
	}
	RBTNode* rotateLeft(RBTNode *root) {
		//节点位置交换
		RBTNode* root_right = root->_right;
		root->_right = root_right->_left;
		root_right->_left = root;

		//节点的颜色与原来该位置节点颜色保持一致
		root_right->_color = root->_color; 
		root->_color = RED;

		//节点计数器也同样与原来抱持一致
		root_right->_count = root->_count;

		//添加节点位置节点重新计算
		root->_count = size(root->_left) + size(root->_right) + 1;

		return root_right;  //返回新的root
	}

	RBTNode* rotateRight(RBTNode* root) {
		//节点位置交换
		RBTNode* root_left = root->_left;
		root->_left = root_left->_right;
		root_left->_right = root;

		//保持原位置节点的颜色
		root->_color = RED;
		root_left->_color = root->_color;
		//保持原来位置的计数器值
		root_left->_count = root->_count;
		//插入节点位置的节点重新计算
		root->_count = size(root->_left) + size(root->_right) + 1;

		return root_left;
	}

	RBTNode* flipColor(RBTNode* root) {
		root->_color = RED;
		root->_left->_color = BLACK;
		root->_right->_color = BLACK;
		return root;
	}

	//删除节点
	//根据2-3树的特点，删除节点只可删除一个3-节点，即红色节点，否则导致树的不平衡
	//删除2-节点时，即黑色节点时，需先对树进行调整，调整出一个红色节点，然后在删除

	void Delete(T key) {
		if (!isRED(_root->_left) && !isRED(_root->_right)) {
			_root->_color = RED;
		}
		_root = _delete(_root, key);
		if (_root) {
			_root->_color = BLACK;
		}
	}

	RBTNode* _delete(RBTNode* root, T key) {
		if (root->_key > key) {
			if (!isRED(root->_left) && !isRED(root->_left->_left)) {
				root = moveRedLeft(root);
			}
			root->_left = _delete(root->_left, key);
		}
		else {
			if (isRED(root->_left)) root = rotateRight(root);
			if (root->_key == key && root->_right == NULL) return NULL;
			if (!isRED(root->_right) && !isRED(root->_right->_left)) root = moveRedRight(root);
			if (root->_key == key) {
				T min_key = min(root->_right);
				root->_value = get(root->_right, min_key);
				root->_key = min_key;
				root->_right = _deleteMin(root->_right);
			}
			else {
				root->_right = _delete(root->_right, key);
			}
		}
		return balance(root);
	}

	RBTNode* moveRedLeft(RBTNode* root) {
		noFlipColor(root);
		if (isRED(root->_right->_left)) {
			root->_right = rotateRight(root->_right);
			root = rotateLeft(root);
		}
		return root;
	}

	RBTNode* moveRedRight(RBTNode* root) {
		noFlipColor(root);
		if (!isRED(root->_left->_left)) {
			root = rotateRight(root);
		}
		return root;
	}

	RBTNode* _deleteMin(RBTNode* root,RBTNode* &del) {
		if (root->_left == NULL) {  //找到最小节点
			del = root;  //保存最小节点
			return NULL;  //返回NULL用于接收,即删除了最小节点
		}
		if (!isRED(root->_left) && isRED(root->_left->_left)) {
			root = moveRedLeft(root);
		}
		root->_left = _deleteMin(root->_left,del);  //接收删除后的节点，即让其置为NULL
		return balance(root);
	}

	RBTNode* _deleteMin(RBTNode* root) {
		RBTNode* del = NULL;
		root = _deleteMin(_root, del);
		if (del) {
			delete del;
			del = NULL;
		}
		return root;
	}

	RBTNode* _deleteMax(RBTNode* root,RBTNode* &del) {
		if (isRED(root->_left)) root = rotateRight(root);
		if (root->_right == NULL) {
			del = root;
			return NULL;
		}
		if (!isRED(root->_right) && isRED(root->_right->_left)) {
			root = moveRedRight(root);
		}
		root->_right = _deleteMax(root->_right,del);
		return balance(root);
	}

	RBTNode* _deleteMax(RBTNode* root) {
		RBTNode* del = NULL;
		root = _deleteMax(_root, del);
		if (del) {
			delete del;
			del = NULL;
		}
		return root;
	}

	RBTNode* balance(RBTNode* root) {
		if (isRED(root->_right)) root = rotateLeft(root);
		if (isRED(root->_right) && !isRED(root->_left))       root = rotateLeft(root);  //右旋节点为插入位置的节点
		if (isRED(root->_left) && isRED(root->_left->_left))  root = rotateRight(root);  //注：左旋的节点为插入位置节点的上一个节点
		if (isRED(root->_left) && isRED(root->_right)) root = flipColor(root);  //出现左右子节点都为红色，则进行颜色变换																			//节点数目统计
		root->_count = size(root->_left) + size(root->_right) + 1;

		return root;
	}

	void noFlipColor(RBTNode* root) {
		if (root) {
			root->_color = BLACK;
			root->_left->_color = RED;
			root->_right->_color = RED;
		}
	}

	V get(RBTNode* root, T key) {
		if (root == NULL) return -1;
		if (root->_key == key) return root->_value;
		else if (root->_key < key)  return get(root->_right, key);
		else  return get(root->_left, key);
	}

	T min(RBTNode* root) {
		if (root == NULL) return -1;
		if (root->_left == NULL) return root->_key;
		return min(root->_left);
	}

	T get() {
		return get(_root, min(_root));
	}

	void deleteMin() {
		_deleteMin(_root);
	}

	void deleteMax() {
		_deleteMax(_root);
	}

	void Print() {
		_Print(_root);
	}

	void _Print(RBTNode* root) {
		if (root == NULL) return;
		_Print(root->_left);
		cout << root->_key << " ";
		_Print(root->_right);
	}

private:
	RBTNode *_root;
 };

void test_RBTree() {
	RBTree<int, int> rb;
	rb.put(1, 1);
	rb.put(2, 2);
	rb.put(3, 3);
	rb.put(4, 4);


	cout << rb.get() << endl;

	rb.Print();
	cout << endl;
	rb.deleteMin();
	rb.Delete(3);
	rb.deleteMax();
	rb.Print();
	cout << endl;

}