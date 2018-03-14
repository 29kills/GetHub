
#include<iostream>
#include<list>
#include<vector>
#include<algorithm>//算法
#include<Windows.h>
using namespace std;
//迭代器的使用方法
//list<int>::iterator it = L.begin();//普通迭代器---读写
//list<int>::const_iterator ct = L.begin();//const迭代器---读
//vector<int>::reverse_iterator vt = V.rbegin();//反向迭代器---读写

//template<class T>
void print_list(const list<int>& d)
{
	list<int>::const_iterator ct = d.begin();
	while(ct != d.end())
	{
		cout << *ct << ' ' ;
		ct++;
	}
}

void List_test()
{
	list<int> L;
	L.push_back(1);//push_back()未优化，需调用一次构造和拷贝构造
	L.push_back(2);//emplace_back是C++11里的，进行了优化，有时只调用一次构造，更高效
	L.push_back(3);
	L.push_back(4);
	L.push_back(5);
	L.push_back(6);

	cout << "\n升序处理:" ;
	greater<int> great_num;//升序
	L.sort(great_num);
	print_list(L);
	cout << endl;

	cout << "\n降序处理:" ;
	less<int> less_num;//降序
	L.sort(less_num);//降序处理(顺序表无sort()函数)
	print_list(L);

	//使用迭代器访问内部元素
	//从头到尾遍历所有元素
	list<int>::iterator it = L.begin();//普通迭代器，内容可修改
	while(it != L.end())
	{
		if(*it % 2)//输出奇数
		cout << ++*it << endl;
		it++;
	}
	cout << endl;
    list<int>::const_iterator ct = L.begin();//const迭代器,内容不可修改
	while(ct != L.end())
	{
		cout << *ct << endl;
		ct++;
	}
	cout << endl; 
}

void Vector_test()
{
	size_t i = 0;
	vector<int> V;
	V.push_back(1);
	V.push_back(2);
	V.push_back(3);
	V.push_back(4);
	V.push_back(5);
	V.push_back(6);

	//使用迭代器逆序遍历
	//使用迭代器不仅可读，还可写（修改）
	vector<int>::reverse_iterator vt = V.rbegin();//反向迭代器
	while(vt != V.rend())
	{
		if(!(*vt %2))//需加括号
			cout << *vt << endl;
		vt++;
	}
	//遍历使用循环或使用迭代器
	for(i = 0;i <V.size();i++)//遍历
	{
		cout << V[i];
	}
	cout << endl;

	{
		size_t N = 1000000;
		size_t start = GetTickCount();//获取时间
		V.reserve(N);//开辟容量大小N(避免插入时多次增容，效率低问题)和puch_back使用
		//V.resize(N);//先开辟N个空间，后拷贝过去，效率低，适合和[]使用
		for(i = 0; i< N;i++)
		{
			V.push_back(i);
			//V[i] = i;
		}
		size_t end = GetTickCount();//获取时间
		cout << end - start <<endl;
	}
}

void other_test()
{
	list<int> L1;
	L1.push_back(1);
	L1.push_back(2);
	L1.push_back(3);
	list<int>::iterator pos = find(L1.begin(),L1.end(),3);//从beging--end找3
	if(pos != L1.end())//判断是否找到
	L1.insert(pos,(*pos)*10);//插入
	print_list(L1);

	list<int>::iterator p = find(L1.begin(),L1.end(),2);//从beging--end找3
	if(p != L1.end())//判断是否找到
	L1.erase(p);//删除
	print_list(L1);

	cout << endl;
	list<int>::iterator t = L1.begin();
	while(t != L1.end())
	{
		if(*t % 2)//删除奇数
			t = L1.erase(t);//删除,删除后返回下一个地址
		else//未删除指向下一个,防止迭代器失效
		t++;//迭代器失效，等价于野指针
	}

	print_list(L1);

}