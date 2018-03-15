#pragma once 
#include<iostream>
#include<vector>
#include<assert.h>
using namespace std;
//大堆---所有父节点大于子节点
//小堆---所有父节点小于子节点
//堆应用---优先级队列---PreQueue
//小堆---复用---仿函数(通过类和运算符的重载实现)
template<class T>
struct Less//小堆比较类方法
{
	bool operator()(const T& left,const T& right)const //重载（）
	{
		return left > right;
	}
};
template<class T>
struct Greater//大堆比较类方法
{
	bool operator()(const T& left,const T& right)const //重载（）
	{
		return left < right;
	}
};
//Compare为Less则为小堆,调用小堆类比较方法，为Greater则为大堆，调用大堆类比较方法
template<class T,class Compare = Greater<T>>//后一个参数表明比较方法（缺省参数默认大堆）
class Heap
{
public :
	Heap()//无参构造
	{}
	//数据转化成树
	Heap(T* arr,size_t size)//带参构造
	{
		size_t i = 0;
		_heap.reserve(size);//增容
		for(i = 0;i < size; i++)
		{
			_heap.push_back(arr[i]);
		}
		//建堆
		for(int j = _heap.size()/2;j >= 0 ;j--)//内循环比较当前轮-1次（即靠上的不再比较）
		//AdjustDown(j);//向下调整
		AdjustDown2(j);//向下调整

	}
	//大堆调整
	//1.找到最后一个非叶子节点（即父节点）a，从下向上调整(a--即上一个父亲节点)
	//调堆，假设从K层以下为大堆
	void AdjustDown(size_t K)//向下调整
	{
		size_t parent = K;
		size_t chiled = K*2+1;//左孩子,K*2+2右孩子
		while(chiled < _heap.size())
		{
			Max_change(parent,chiled);//交换处理
			parent++;
			chiled = parent*2+1;
		}
	}
	//插入一个数据（尾插），向上调整，只需调整插入节点的那条路径
	void Puch(T data)
	{
		size_t chiled ;
		size_t parent ;
		_heap.push_back(data);
		//向上调整
		chiled = _heap.size()-1;
		while(chiled)//不为根节点下标（0）
		{
			parent = (chiled-1)/2;
			Max_change(parent,chiled);//交换处理
			chiled = parent;//父亲作为孩子节点
		}
	}
	void AdjustDown2(size_t K)//向下调整
	{
		Compare com;//比较方法对象
		size_t parent = K;
		size_t chiled = K*2+1;//左孩子,K*2+2右孩子
		while(chiled < _heap.size())//不为根节点下标（0）
		{
			if(chiled < _heap.size()-1 && com(_heap[chiled] , _heap[chiled+1]))//com调用对应的比较方法类中的重载函数
			{
				chiled++;//变为右孩子
			}
			//交换数据
			//if(chiled < _heap.size() && _heap[parent] < _heap[chiled])//判断，是否交换
			if(chiled < _heap.size() && com(_heap[parent] , _heap[chiled]))//判断，是否交换
			{
				swap(_heap[parent],_heap[chiled]);//交换
				parent++;
			    chiled = parent*2+1;
			}
			else
				break;
		}
	}
	void Max_change(size_t parent,size_t chiled)//交换处理？
	{
		Compare com;//比较方法对象
		//if(chiled < _heap.size()-1 && _heap[chiled] < _heap[chiled+1])//选出大的孩子,-1是为了防止数组越界
		if(chiled < _heap.size()-1 && com(_heap[chiled] , _heap[chiled+1]))//com调用对应的比较方法类中的重载函数
		{
			chiled++;//变为右孩子
		}
		//交换数据
		//if(chiled < _heap.size() && _heap[parent] < _heap[chiled])//判断，是否交换
		if(chiled < _heap.size() && com(_heap[parent] , _heap[chiled]))//判断，是否交换
		{
			swap(_heap[parent],_heap[chiled]);//交换

		}
	}
	//删除一个最大节点(根节点)
	//先将根节点与最后一个节点交换，删除最后一个节点，在进行向下调整
	void Pop()
	{
		swap(_heap[0],_heap[_heap.size()-1]);//根节点与最后一个节点交换
		_heap.pop_back();//尾删
		AdjustDown(0);//向下调整
	}

	T& Top()
	{
		return _heap.front();
	}
	//判断是否为大堆,从上向下遍历到最后一个节点的父亲节点，进行比较
	bool Isheap()
	{
		Compare com;
		size_t i = 0;
		assert(!_heap.empty());
		for(i = 0;i <= _heap.size()-2/2;i++)
		{
			size_t left = i*2+1;
			size_t right = i*2+2;
			//if((right < _heap.size()&&_heap[i] < _heap[left])||//大堆判断
			   //(right < _heap.size() && _heap[i] < _heap[right]))//不满足
			if((left < _heap.size()-1 && com(_heap[i] , _heap[left])) || //左侧判断
			   (right < _heap.size()-1 && com(_heap[i] , _heap[right])))//右侧判断
				return false;//其中有不满足
			//满足继续遍历
		}//遍历结束，则成立
		return true;
	}
	size_t Size()
	{
		return _heap.size();
	}
	bool Empty()
	{
		return _heap.empty();
	}


	//自己实现的代码
	void Init_heap(T* arr,const size_t size)
	{
		size_t i = 0;
		for(i = 0; i < size; i++)
		{
			_heap.push_back(arr[i]);
		}
	}
	void Max_heap()
	{
		size_t i = 0;
		size_t j = 0;
		while(j++ < _heap.size())
		{
			i = 0;
			while(i < _heap.size())
			{
				if(i*2+1 < _heap.size() && _heap[i] < _heap[i*2+1])
				{
					T tmp = _heap[i];
					_heap[i] = _heap[i*2+1];
					_heap[i*2+1] = tmp;
				}
				if(i*2+2 < _heap.size() && _heap[i] < _heap[i*2+2])
				{
					T tmp = _heap[i];
					_heap[i] = _heap[i*2+2];
					_heap[i*2+2] = tmp;
				}
				i++;
			}
		}
	}

	void Min_heap()
	{
		size_t i = 0;
		size_t j = 0;
		while(j++ < _heap.size())
		{
			i = 0;
			while(i < _heap.size())
			{
				if(i*2+1 < _heap.size() && _heap[i] > _heap[i*2+1])
				{
					T tmp = _heap[i];
					_heap[i] = _heap[i*2+1];
					_heap[i*2+1] = tmp;
				}
				if(i*2+2 < _heap.size() && _heap[i] > _heap[i*2+2])
				{
					T tmp = _heap[i];
					_heap[i] = _heap[i*2+2];
					_heap[i*2+2] = tmp;
				}
				i++;
			}
		}
	}
	void heap_print()
	{
		size_t i = 0;
		while(i < _heap.size())
		{
			cout << _heap[i++] << ' ';
		}
		cout << endl;
	}
private :
	vector<T> _heap;
};

void Heap_test()
{
	int arr[] = {1,2,3,4,5,9,8,6,7};
	size_t sz = sizeof(arr)/sizeof(arr[0]);

	Heap<int> h1(arr,sz);//大堆
	cout << h1.Isheap() << endl;
	h1.heap_print();
	
	h1.Puch(10);
	h1.heap_print();

	h1.Pop();
	h1.heap_print();

	cout << endl;
	Heap<int,Less<int>> h2(arr,sz);//小堆
	h2.heap_print();
	
	h2.Puch(10);
	h2.heap_print();

	h2.Pop();
	h2.heap_print();
	cout << h1.Isheap() << endl;

	/*
	Heap<int> h1;
	h1.Init_heap(arr,sz);
	h1.heap_print();

	h1.Max_heap();
	h1.heap_print();

	h1.Min_heap();
	h1.heap_print();
	*/
}


//具有很多的数据，求最大的前K个数---建堆求解（建K个数据的堆）
//排序解法:时间复杂度最小O(N*lgN)，并且空间可能无法满足
//堆解：建一个具有K个节点的 小堆，将堆头节点Pop掉(进行调整)，再取下一个数据与堆头进行比较，大于堆头将数据入堆(进行调整)，
//依次循环，让所有数据入一次堆，最终堆即为最大的前K个数据，时间复杂度：O(N*lgK)
//实际写法不用实现堆，只实现建堆，和向下调整，不用写Pop,满足条件只需使用交换函数swap交换堆顶(arr2[0])即可
void Big_test()
{
	const size_t N = 10000;
	const size_t K = 10;
	int arr[N];//原数据
	int arr2[K];//将要放入堆中的数据
	int i = 0;
	for(i= 0;i < N;i++)//生成数据
	{
		arr[i] = rand()%N;
	}
	//设置10个最大数 > 10000,若结果 > 10000则正确
	arr[10] = N+100;
	arr[100] = N+200;
	arr[101] = N+150;
	arr[150] = N+160;
	arr[16] = N+170;
	arr[50] = N+160;
	arr[90] = N+600;
	arr[900] = N+650;
	arr[1000] = N+100;
	arr[500] = N+690;

	for(i = 0;i < K; i++)//取前K个数据
	{
		arr2[i] = arr[i];
	}
	Heap<int,Less<int>> h1(arr2,K);//建小堆(会进行调整)

	for(i = K - 1; i < N ;i++)//循环入堆比较
	{
		if(h1.Top() < arr[i])
		{
			h1.Pop();//删除堆头
			h1.Puch(arr[i]);//比当前堆头大，入堆(入堆后会进行调整)
		}
	}
	h1.heap_print();//打印最终堆中的元素
}

//堆排序---选择排序
//1、升序---建小堆 
//2、循环将最小的数据放在最前：每次将根节点与当前最后一个节点交换，后进行调整，每轮后不在考虑最后一个节点
//3、时间复杂度---O(N*lgN)