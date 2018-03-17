#include<iostream>
#include<assert.h>
#include<math.h>

using namespace std;

template<class T,class V>
struct AvlNode
{
	T _key;//数值
	V _value;//含义
	int _bf;//平衡因子
	AvlNode<T,V>* _left;
	AvlNode<T,V>* _right;
	AvlNode<T,V>* _parent;
	AvlNode(const T& key,const V& value)
		:_key(key)
		,_value(value)
		,_bf(0)
		,_left(NULL)
		,_right(NULL)
		,_parent(NULL)
	{}
};
template<class T,class V>
class AVL
{
	typedef AvlNode<T,V> Node;
public:
	AVL()
		:_root(NULL)
	{}

	bool Push_Back(const T& Key,const V& value)
	{
		if(_root == NULL)
		{
			_root = new Node(Key,value);//根节点
			return true;
		}
		Node* cur = _root;
		Node* parent = NULL;

		//遍历查找到可插入位置
		while(cur)
		{
			if(cur->_key < Key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if(cur->_key > Key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else//数值相同错误
				return false;
		}

		//链接新节点
		cur = new Node(Key,value);
		if(parent->_key < Key)//插入在右侧
		{
			parent->_right = cur;
		}
		else//插入在左侧
		{
			parent->_left = cur;
		}
		cur->_parent = parent;//初始新节点的父亲

		//处理平衡因子
		while(parent)
		{
			//平衡因子计算(处理双亲(父)节点的因子)
			if(parent->_left == cur)//插入在双亲的左
				parent->_bf--;      //平衡因子减-1
			else                    //插入在双亲的右
				parent->_bf++;      //平衡因子+1

			//根据平衡因子的数值判断是否调整树
			if(parent->_bf == 0)//平衡不用调整树，退出
				break;
			else if(parent->_bf == 1 || parent->_bf == -1)//不平衡，因子为1--向上回退
			{
				cur = parent;
				parent = cur->_parent;
			}
			//需平衡调整树
			else//不平衡，因子为2，平衡处理
			{
				if(parent->_bf == 2)//树的右侧长
				{
					if(cur->_bf == -1)//插入在右子树节点左侧
						Lotatel(parent);//左单旋
					else             //插入在右子树节点右侧
						Rotaterl(parent);//右左旋
				}
				else//树的左侧长
				{
					if(cur->_bf == -1)  //插入在右子树节点左侧
						Rotatel(parent);//右旋
					else                //插入在右子树节点左侧
						Rotatelr(parent);//左右旋
				}
				break;
			}
			//平衡处理：
			//1、添加在较高右子树的右节点上(右节点的右或左)，右比左长---左旋
			//2、添加在较高左子树的左节点上(左节点的左或右)，左比右长---右旋
			//3、添加在较高右子树的左节点上(左节点的左或右)--右比左长---右，左双旋，先右旋成1种，在进行左旋
			//4、添加在较高左子树的右节点上(右节点的左或右)--左比右长---左，右双旋，先左旋成2种，在进行右旋
		}
		return true;
	}

	void Rotatelr(Node* parent)//左，右双旋
	{
		Node* subl = parent->_left;
		Node* sublr = subl->_right;
		int bf = sublr->_bf;//记录旋转之前的因子值

		Lotatel(parent->_left);//左旋
		Rotatel(parent);//右旋
		//更新因子值
		if(bf == -1)
			subl->_bf = 1;
		else if(bf == 1)
			parent->_bf = -1;
	}

	void Rotaterl(Node* parent)//右，左双旋
	{
		Node* subr = parent->_right;
		Node* subrl = subr->_left;
		int bf = subrl->_bf;//记录旋转之前的

		Rotatel(parent->_right);//右旋
		Lotatel(parent);//左旋

		if(bf == 1)
			parent->_bf = -1;
		else if(bf == -1)
			subr->_bf = 1;
	}

	void Lotatel(Node* parent)//左旋---父节点的右长
	{
		//parent是因子值为2的节点
		Node* subr = parent->_right;//获取父节点的右子树
		Node* subl = subr->_left;   //获取右子树的左孩子

		//改变指针域，实现树的调整
		parent->_right = subl;     //父节点的右指向subr的左孩子
		if(subl)//右子树存在左孩子
			subl->_parent = parent;//更改subr左孩子的父节点
		subr->_left = parent;    //更改subr的左指域指向父节点
		Node* pparent = parent->_parent;//获取原父节点的父亲
		subr->_parent = pparent;//更新subr父亲节点的父亲
		parent->_parent = subr;//subr当作新的父亲节点

		if(parent == _root)//父节点为根节点
			_root = subr;//更改根节点
		else
		{
			if(pparent->_left == parent)//原父亲节点在左侧
				pparent->_left = subr;//新父亲节点连接在左侧（原父亲节点的父亲节点左侧）
			else
				pparent->_right = subr;////新父亲节点连接在右侧
		}
		//更新节点因子值
		parent->_bf = subr->_bf = 0;
	}

	void Rotatel(Node* parent)//右旋
	{
		Node* subl = parent->_left;
		Node* sublr = subl->_right;

		parent->_left = sublr;
		if(sublr)//存在父节点的右子树存在左节点
			sublr->_parent = parent;//更改其父节点
		subl->_right = parent;
		Node* pparent = parent->_parent;//原父节点的父亲
		subl->_parent = pparent;
		parent->_parent = subl;

		if(parent == _root)//父节点为根节点
			_root = subl;//更改根节点
		else
		{
			if(pparent->_left == parent)
				pparent->_left = subl;
			else
				pparent->_right = subl;
		}
		//更新节点因子
		parent->_bf = subl->_bf = 0;
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

	bool IsBalance()
	{
		return IsBalance(_root);
	}
	bool IsBalance(Node* root)
	{
		if(root == NULL)
			return true;
		int leftH = Height(root->_left);
		int rightH = Height(root->_right);
		if(abs(leftH-rightH) >= 2)//差值大于2，不为平衡树
			return false;
		return IsBalance(root->_left) && IsBalance(root->_right);//递归左右子树
	}
	size_t Height(Node* cur)
	{
		if(cur == NULL)
			return 0;

		static size_t n1 = 1;//根节点为第一层
		static size_t n2 = 1;

		n1 = Height(cur->_left);
		n2 = Height(cur->_right);
		if(cur->_left || cur->_right)//在有左或右子树的节点才进行比较
		return (n1 > n2 ? n1 : n2)++;
		return 1;//只有根节点
	}

	//删除为处理完
	void Ereas(Node* parent)//删除后调整
	{
		while(parent)
		{
			//因子处理
			if(parent->_right)
				parent->_bf--;
			else
				parent->_bf++;
			//树调整
			Node* cur = NULL;
			if(parent->_bf == 1 || parent->_bf == -1)
				break;//高度未变，退出
			else if(parent->_bf == 0)
			{
				cur = parent;
				parent = cur->_parent;
			}
			else
			{
				if(parent->_bf == 2)//树的右侧长
				{
					if(cur->_bf == -1)
						Lotatel(parent);//左旋
					else
						Rotaterl(parent);//右左旋
				}
				else//树的左侧长
				{
					if(cur->_bf == -1)
						Rotatel(parent);//右旋
					else
						Rotatelr(parent);//左右旋
				}
				//break;
			}
		}
	}

private:
    Node* _root;
};

void AVL_test()
{
	int arr[] = {16,3,7,11,9,26,18,14,15};
	AVL<int,int> a;
	int i = 0;
	for(i = 0; i < sizeof(arr)/sizeof(arr[0]); i++)
		a.Push_Back(arr[i],i);
	a.print();
	cout << endl;
	cout << a.IsBalance() << endl;
}