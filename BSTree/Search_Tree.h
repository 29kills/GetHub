#pragma once
#include<iostream>
#include<assert.h>
using namespace std;

/*
һ������ڵ㣺��ͷ�ڵ����±�����ڵ�Ƚϣ�С������࣬������Ҳֱ࣬��ΪҶ�ӽڵ㣬���ڲ����Ľڵ���(�����ڵ�)(�����豣�游�ڵ�)
�������ң����ݴ�С����������
����ɾ����
1���Ӹ��ڵ���б������ҵ�Ҫɾ���Ľڵ�(���ݴ�Сȥ��)
1��ɾ���ڵ���Ϊ�գ����丸�ڵ�ָ��������������Ϊ�գ����丸�ڵ�ָ����������
ע����ɾ����Ϊ���ڵ㣬��parent = NULL;���������⴦��root->left = NULLֱ����root = root->_right;ɾ��root,��Ϊ����֮����
2�����ҽڵ㶼��Ϊ��----�滻��:����������������ڵ㣬����֮�滻(����)��ɾ���滻�Ľڵ�

�ݹ�ⷨ��
ע�����ڵݹ�ֻ�ܷ��ص���һ�㣬���Եݹ�ÿ������з���ֵ
һ���ݹ���룬ע��ʹ�����ô��Σ�Ϊ��(�󣬻���ָ��)������ָ���½ڵ㣬����true
��Ϊ��,cur->key < Key �ݹ���������cur->key > Key �ݹ���������else (��ȷ���false)
�����ݹ����
�����ݹ�ɾ��
1���ݹ����ɾ���ڵ�
2���󣬻���Ϊ�գ���ɾ���ڵ�ָ�����ӽڵ�
3��ɾ�����Һ��Ӷ���Ϊ�յĽڵ�
����1��ʹ�÷ǵݹ飬�ı�����ڵ�ĸ��ڵ��ָ�����ӽڵ�ķ�������ǵݹ�ô������ͬ��
����2������ת����ɾ������ڵ��������---�ݹ�
*/
//������ӵ�����(����)---����������޸ģ�ÿ���ڵ������һ��ָ����ָ�򸸽ڵ㣬
//ע�����ڵ�ǰ���һ���սڵ㣬����ָ����ָ����������Ҷ�Ӻ�����Ҷ�ӣ����ڵ��Ǹýڵ�ĸ��׽ڵ㣬������ͬ��ֻ��������
//KΪ�������͵�ģ�壬VΪ���ݵĺ���ģ��
template<class K,class V>
struct SearchTreeNode
{
	K _key;//�ؼ���
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

	//����ڵ㣺��ͷ�ڵ����±�����ڵ�Ƚϣ�С������࣬������Ҳֱ࣬��ΪҶ�ӽڵ㣬���ڲ����Ľڵ���(�����ڵ�)(�����豣�游�ڵ�)
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
			Node* parent = NULL;//���浱ǰ��㣬����һ���ڵ�ĸ��ڵ�
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
					return false ;//��ֵ��ȣ�����
			}
			if(parent->_key < Key)
				parent->_right = new Node(Key,value);
			else
				parent->_left = new Node(Key,value);
			return true;
		}
	}

	//�ݹ���룬ע��ʹ�����ô��Σ�Ϊ��(�󣬻���ָ��)������ָ���½ڵ㣬����true
	//��Ϊ��,cur->key < Key �ݹ���������cur->key > Key �ݹ���������else (��ȷ���false)
	//ע�����ڵݹ�ֻ�ܷ��ص���һ�㣬���Եݹ�����з���ֵ
	bool Insert(const K& Key)
	{
		return Insert(_root,Key);
	}
	bool Insert(Node*& cur,const K& Key)
	{
		if(cur == NULL)//����ָ����Ϊ��ֱ����ָ����ָ���µĽڵ�
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

	//����
	//const Node* Find(const K& Key)//������������֧���޸ģ��޸ĺ�Ϳ��ܲ�����������
	Node* Find(const K& Key)//value���
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

	//�ݹ����
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

	//ɾ����1���Ӹ��ڵ���б������ҵ�Ҫɾ���Ľڵ�(���ݴ�Сȥ��)
	//      1��ɾ���ڵ���Ϊ�գ����丸�ڵ�ָ��������������Ϊ�գ����丸�ڵ�ָ����������
	//      ע����ɾ����Ϊ���ڵ㣬��parent = NULL;���������⴦��root->left = NULLֱ����root = root->_right;ɾ��root,��Ϊ����֮����
	//      2�����ҽڵ㶼��Ϊ��----�滻��:����������������ڵ㣬����֮�滻(����)��ɾ���滻�Ľڵ�
	
	bool Delete(const K& Key)
	{
		Node* cur = _root;
		Node* parent = NULL;
		Node* del = NULL;
		//����Ҫɾ���Ľڵ�
		while(cur)
		{
			if(Key > cur->_key)
			{
				parent = cur;//���浱ǰ��㣨�¸��ڵ�ĸ��׽ڵ㣩
				cur = cur->_right;//ָ��������
			}
			else if(Key < cur->_key)
			{
				parent = cur;
				cur = cur->_left;//ָ��������
			}
			//ע�⣺��Ҫɾ���Ľڵ�(cur)Ϊ���ڵ�򲻴���,��parent = NULL,ɾ��ʱ��Դ�������⴦��
			else//�ҵ�
			{
				del = cur;//curΪ��Ҫɾ���Ľڵ�
				//cur�����Ϊ��---���ڵ��������ӽڵ�
				if(cur->_left == NULL)//��Ϊ��
				{
					if(parent == NULL)//ɾ�����ڵ�
						_root = _root->_right;
					else
					{
						if(parent->_left == cur)//cur�����ڸ��ڵ����
						    parent->_left = cur->_right;//���ڵ��������������
					    else//cur�����ڸ��ڵ����
						    parent->_right = cur->_right;//���ڵ��������������
					}
				}
				else if(cur->_right == NULL)
				{
					if(parent == NULL)
						_root = _root->_left;
					else
					{
						if(parent->_left == cur)//cur�����ڸ��ڵ����
						    parent->_left = cur->_left;//���ڵ��������������
					    else//cur�����ڸ��ڵ����
						    parent->_right = cur->_left;//���ڵ��������������
					}
				}
				//���Ҷ���Ϊ�գ�����������������ڵ㣬����֮�滻��ɾ���滻�Ľڵ�
				//ע����ɾ���ڵ��������������ڵ�����ҽڵ�(������)������ڵ㣬������NULL
				else//���Ҷ���Ϊ��
				{
					Node* parent = cur;//������ڵ�ĸ��ڵ�
					Node* sub = cur->_right;//������ڵ�,����������������ڵ�
					while(sub->_left)//������ڵ�
					{
						sub = sub->_left;
					}
					cur->_key = sub->_key;
					//ɾ������ڵ�
					//����subΪ����ڵ㣬���Ը��ڵ�ָ��sub���ҽڵ�
					if(parent->_left == sub)//����������sub����
					{
						parent->_left = sub->_right;
					}
					else//����������sub����
						parent->_right = sub->_right;
				 del = sub;
				}
			 delete del;
			 return true;
			}
		}
		//δ�ҵ�
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

	//�ݹ�ɾ��
	bool Remove(const K& Key)
	{
		return Remove(_root,Key);
	}
	bool Remove(Node*& cur,const K& Key)
	{
		//�ݹ����ɾ���ڵ�
		if(cur == NULL)//δ�ҵ�
			return false;
		if(cur->_key < Key)//�����
			Remove(cur->_right,Key);
		else if(cur->_key > Key)//�Ҳ���
			Remove(cur->_left,Key);
		//������ָ��ɾ��ԭָ��
		else //�ҵ�ɾ���ڵ�
		{
			Node* del = cur;
			if(cur->_left == NULL)//ɾ���ڵ������Ϊ��
			{
				cur = cur->_right;//ɾ���ڵ�ָ�����Һ���
				delete del;//ת���������⣬����ڴ˴�ɾ��
			}
			else if(cur->_right == NULL)//ɾ���ڵ���Һ���Ϊ��
			{
				cur = cur->_left;//ɾ���ڵ�ָ��������
				delete del;//ת���������⣬����ڴ˴�ɾ��
			}
			//ɾ���ڵ㣬���Һ��Ӷ���Ϊ��
			//����1��ʹ�÷ǵݹ飬�ı�����ڵ�ĸ��ڵ��ָ�����ӽڵ�ķ�������ǵݹ�ô������ͬ��
			//����2������ת����ɾ������ڵ��������---�ݹ�
			else
			{
				Node* sub = cur->_right;//����ڵ�Ϊ�ýڵ���������ϵ�����ڵ�(������ڵ�����ҽڵ㵱����ڵ㣬������NULL)
				while(sub->_left)
				{
					sub = sub->_left;
				}
				cur->_key = sub->_key;
				Remove(_root,sub->_key);//����ת����ɾ������ڵ��������
			}
			//delete del;//�ݹ�ɾ�����Ҳ�Ϊ�սڵ�ʱ�����ɷ��ڴ˴�ɾ������Ϊת����������󣬴˴��ᷢ�����ɾ������
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

//���V��ʾ���ݵĺ��壬���������˼��
*/
//���ʵ书��
#include<string>
void BST_test()
{
	SearchTree<string,string> st;
	st.Puch("tree","��");
	st.Puch("hello","���");
	st.Puch("men","��");
	st.Puch("baby","baby");
	st.Puch("ok","��");

	string word;
	while(1)
	{
		cout  << "����word:" ;
		cin >> word ;
	    SearchTreeNode<string,string>* ret = st.Find(word);
		if(ret)
	    cout << ret->_value << endl;
		else
		cout << "No Word" << endl;
	}
}