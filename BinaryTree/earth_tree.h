#include<iostream>
#include<stack>
#include<queue>

using namespace std;

template<class T>
struct TreeNode
{
	T _value;
	TreeNode* _left;
	TreeNode* _right;

	TreeNode(const T& x)//构造函数
		:_value(x)
		,_left(NULL)
		,_right(NULL)
	{}
};

template <class T>
class Tool//构造函数
{
	typedef TreeNode<T> TNode;//自定义类型
public :
	Tool(T* arr,size_t size,const T invalid)//invalid非法值
	{
		size_t index = 0;
		//while(size--)//不可加循环
		_tree = CreateBinaryTree(arr,size,index,invalid);//构造树
	}

	TNode* CreateBinaryTree(T* arr,const size_t size,size_t& index,T invalid)//构造树（前序）
	{
	    TNode* _tree = NULL;
		if(index < size && arr[index] != invalid)//注意越界
		{
			_tree = new TNode(arr[index]);//创建根节点（自动调用构造函数）
			_tree->_left = CreateBinaryTree(arr,size,++index,invalid);//构造左子树

			_tree->_right = CreateBinaryTree(arr,size,++index,invalid);//构造右子树
		}
		return _tree;
	}

	size_t Size()//使用递归的方法计算，需要传参，采用重载的方法
	{
		size_t size = 0;
		Size(_tree,size);
		return size;
	}
	size_t Size(TNode* _tree,size_t& size)//节点数
	{
		if(_tree == NULL) 
			return 0;
		size++;
	    Size(_tree->_left,size);
		Size(_tree->_right,size);
		return size;
	}

	size_t Size_leave()//叶子数
	{
		size_t count = 0;
		return Size_leave(_tree,count);
	}

	size_t Size_leave(TNode* _tree,size_t& count)
	{
		
		if(NULL == _tree)
			return count;//退出递归条件
		if(_tree->_left == NULL && _tree->_right == NULL)
			 count++;
		Size_leave(_tree->_left,count);
		Size_leave(_tree->_right,count);
		return count;//每层递归返回值
	}

	size_t Heigh()//求树的深度，三目运算符 分别求左，右字数，大的+1
	{
		size_t count = 0;
		return Heigh(_tree);
	}
	size_t Heigh(TNode* _tree)
	{
		static size_t n1 = 1;//根节点为第一层
		static size_t n2 = 1;
	
		if(NULL == _tree)//空节点返回0
			return 0;
		Heigh(_tree->_left);
		Heigh(_tree->_right);//回退时计数
		if(_tree->_left || _tree->_right)//在有左或右子树的节点才进行比较
		return (n1 > n2 ? n1 : n2)++;
		return 1;//只有根节点
	}

	size_t GetKleve(size_t K)
	{
		return GetKleve(_tree,K);
	}
	size_t GetKleve(TNode* tree,size_t K)//求第K层的节点数  递归求子数K-1层
	{
		if(tree == NULL || K == 0)
			return 0;
		if(K == 1)
			return 1;
		return GetKleve(tree->_left,K-1)+GetKleve(tree->_right,K-1);
	}

	void Mirror()//镜像---前序遍历递归，将左，右子数进行交换
	{
		Mirror(_tree);
	}
	void Mirror(TNode* _tree)
	{
		TNode* ptemp = NULL;//交换中间变量
		if(NULL == _tree)
			return ;
	
		ptemp = _tree->_left;
		_tree->_left = _tree->_right;
		_tree->_right = ptemp;

		Mirror(_tree->_left);
		Mirror(_tree->_right);
	}
	//广度优先级 使用队列实现
	//1.头节点入队列
	//2、队列不为空-->循环条件
	//3、遍历队头
	//4、左或右子数不为空--入队列
	//5、队头出队列
	void Leve_Order()//广度优先级 使用队列实现
	{
		Leve_Order(_tree);
	}
	void Leve_Order(TNode* tree)
	{
		queue<TNode*> q;
		TNode* cur = tree;
		TNode* Top = NULL;
		if(cur == NULL )
			return ;
		q.push(tree);
		while(!q.empty())
		{
			Top = q.front();
			cout << Top->_value << ' ' ;
			q.pop();
			if(Top->_left != NULL)
			{
				q.push(Top->_left);
			}
			if(Top->_right != NULL)
				q.push(Top->_right);
		}
	}

	void Mirror2()//非递归---使用队列存放左，右子数（类似广度优先级遍历（遍历改交换）），(先)交换左右子数
	{
		Mirror2(_tree);
	}
	void Mirror2(TNode* tree)
	{
		queue<TNode*> q;
		TNode* temp = NULL;
		TNode* Top = tree;
		if(tree == NULL)
			return ;

		q.push(tree);
		while(!q.empty())
		{
			Top = q.front();
			//交换位置
			temp = Top->_left;
			Top->_left = Top->_right;
			Top->_right = temp;

			q.pop();
			if(Top->_left != NULL)
			{
				q.push(Top->_left);
			}
			if(Top->_right != NULL)
				q.push(Top->_right);
		}
	}
	//判断是否为完全二叉树
	//不是完全二叉树：1、同一节点有右子树无左子树 2、小于N-1层不满（即从无右孩子节点开始，之后节点无孩子节点）
	int IsCompleteBinTree()//判断是否为完全二叉树---层次遍历，使用队列
	{
		return IsCompleteBinTree(_tree);
	}
	int IsCompleteBinTree(TNode* tree)
	{
		queue<TNode*> q;
		TNode* Top = tree;
		TNode* cur = NULL;//标记不满的父亲节点
		if(tree == NULL)
			return 0;

		q.push(tree);
		while(!q.empty())
		{
			Top = q.front();
		
			if(Top->_left == NULL && Top->_right != NULL ||//有右子树，无左子树
				Top->_left != NULL && cur != NULL)//小于N-1层不满cur为不满层
				return 0;
			if(Top->_right == NULL)
				cur = Top;//标记不满位置
			q.pop();

			if(Top->_left)
				q.push(Top->_left);
			if(Top->_right)
				q.push(Top->_right);
		}
		return 1;
	}

	void Tree_print()//_tree外部不可访问
	{
		Tree_print(_tree);//重载
	}
    void Tree_print(TNode* ptool)//前序遍历
	{
		if(ptool)
		{
			printf("%c ",ptool->_value);
			Tree_print(ptool->_left);//左
			Tree_print(ptool->_right);//右
		}
	}

	TNode* Find(const T& data)//查找
	{
		return Find(_tree,data);//递归
		//return find(_tree,data);//非递归
	}
	TNode* Find(TNode* tree,const T& data)//递归实现
	{
		TNode* tmp = NULL;
		if(NULL == tree)
			return NULL;
		if(tree->_value == data)
			return tree;

		tmp = Find(tree->_left,data);
		if(tmp)//用于检测左子树是否找到（若不判断，则一直还要在右子树查找，导致错误）
		{
            return tmp;//找到返回退出
		}
		return Find(tree->_right,data);//左子树未找到，在有子树查找
	}
	TNode* find(TNode* tree,const T& data)//非递归查找---栈实现
	{
		stack<TNode*> s;
		TNode* cur = tree;
		if(NULL == tree)
			return NULL;
		s.push(tree);
		while(!s.empty())
		{
			TNode* Top = s.top();
			if(Top->_value == data)
				return Top;
			s.pop();
			if(Top->_left)
				s.push(Top->_left);
			if(Top->_right)
				s.push(Top->_right);
		}
		return NULL;
	}
	//非递归---使用栈
	//前序遍历,中序遍历，后序遍历
	void PreOrderNor()//前序遍历
	{
		PreOrderNor(_tree);
	}
	void PreOrderNor(TNode* _tree)
	{
		stack<TNode*> entry;
		TNode* cur = _tree;
		if(_tree == NULL)
			return ;
		entry.push(_tree);//根节点入栈

		while(cur && !entry.empty())
		{
			cur = entry.top();
			cout << cur->_value << ' ' ;
			entry.pop();

			if(cur->_right)//栈是先进后出，所以右子树先入栈
			{
				entry.push(cur->_right);//右子树入栈
			}

			if(cur->_left)
			{
				entry.push(cur->_left);//左子树入栈
				cur = cur->_left;
			}
		}
	}
	//中序递归遍历
	void InOrder()
	{
		InOrder(_tree);
	}
	void InOrder(TNode* pRoot)
	{
		if(pRoot != NULL)
		{
			InOrder(pRoot->_left);
			printf("%c ",pRoot->_value);
			InOrder(pRoot->_right);
		}
	}

	void InOrderNor()//中序遍历、
	{
		InOrderNor(_tree);
	}
	void InOrderNor(TNode* _tree)
	{
		stack<TNode*> entry;
		TNode* cur = _tree;
		TNode* Top = NULL;
		if(NULL == _tree)
			return ;
		while(cur || !entry.empty())
		{
			while(cur)//走到最左边
			{
				entry.push(cur);
				cur = cur->_left;
				
			}

			Top = entry.top();//取栈顶
			cout << Top->_value <<' ' ;//输出栈顶

			if(Top->_right)//有右子树入栈
				cur = Top->_right;
			entry.pop();
		}
	}

	void PostOderNor()//后序遍历
	{
		PostOderNor(_tree);
	}
	void PostOderNor(TNode* _tree)
	{
		stack<TNode*> entry;
		TNode* cur = _tree;
		TNode* Top = NULL;
		TNode* prev = NULL;
		if(NULL == _tree)
			return ;
		while(cur || !entry.empty())
		{
			while(cur)//走到当前树的最左侧
			{
				entry.push(cur);
				cur = cur->_left;
			}
			Top = entry.top();

			if(Top->_right == NULL || prev == Top->_right)//右为空或右已被访问，则访问当前根节点
			{
				cout << Top->_value << ' ' ;
				prev = entry.top();//标记已访问过的右节点
				entry.pop();//访问过的节点出栈
			}
			else//以右节点作为一个新的树
			cur = Top->_right;
		}
	}

	~Tool()//析构---后序销毁
	{
		Delete(_tree);
		_tree = NULL;
	}
	void Delete(TNode* tree)
	{
		if(!tree)
			return ;
		Delete(tree->_left);
		Delete(tree->_right);
		delete tree;
	}
	
private :
	TNode* _tree;
};

//时间复杂度：O(n+1)==O(n)
//空间复杂度：O(n)
//前序
//中序
//后序
//层序（广度优先遍历）--->使用队列实现
//template <class T>
void tree_test()
{
	char arr[] = {'a','b','d','#','#','g','#','#','c','e','#','#'};
	//char arr[] = {'a','b','d','#','#','g','#','#','c','#','e','#','#'};
	//char arr[] = {'a','b','d','f','#','#','m','#','#','g','#','#','c','e','#','#','#','#'};

	//char arr[] = {'a','#','#','#','#'};

	int sz = sizeof(arr)/sizeof(arr[0]);
	Tool<char> tree(arr,sz,'#');
	
	tree.Tree_print();
	cout << endl;
	cout << "总结点数：" << tree.Size() << endl;
	cout << "叶子节点数：" << tree.Size_leave() << endl;
	cout << "树的深度：" << tree.Heigh() << endl;
	cout << "第K层节点数：" << tree.GetKleve(2) << endl;

	cout << "第一次镜像：" ;
	tree.Mirror();
	tree.Tree_print();
	cout << endl;
	cout << "第二次镜像：" ;
	tree.Mirror();
	tree.Tree_print();

	cout <<"\n先序遍历：";
	tree.PreOrderNor();

	cout <<"\n中序遍历：";
	tree.InOrderNor();
	cout <<"\n中序递归遍历：";
	tree.InOrder();

	cout <<"\n后序遍历：";
	tree.PostOderNor();
	cout <<"\n层次遍历：" ;
	tree.Leve_Order();

	cout << "\n第一次镜像：";
	tree.Mirror2();
	tree.Tree_print();
	cout << "\n第二次镜像：";
	tree.Mirror2();
	tree.Tree_print();

	cout << "\n是否为完全二叉树：" ;
	cout << tree.IsCompleteBinTree() << endl;

	cout << tree.Find('b')->_value << endl;
	
}