#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<stack>
using namespace std;

//插入排序

//typedef int size_t;
//直接插入排序----稳定排序
//时间复杂度：O(N*(N-1)) = O(N^2)
//适用于数据接近有序，和数据较少的排序
void Sort(int* arr,size_t size)
{
	//外循环，从前往后遍历
	//end = i-1;  i表示第i个数据，也表示前i个数据是有序的
	//保存当前数值，用于覆盖后的替换(key = arr[i])
	//内循环(end >=0 &&  key < arr[end]){
	//数值移动， arr[end+1] = arr[end]; end--}
	//还原key值 arr[end+1] = key;

	size_t i = 0;
	size_t prev = 0;
	for(i = 1; i < size; i++)
	{
		prev = i-1;
		int key = arr[i];
		while(prev >= 0 && key > arr[prev])//数据后移，寻找插入的位置
		{
			arr[prev+1] = arr[prev];
			prev--;
		}
		arr[prev+1] = key;//将小的数据(key)放在前边
	}
}

//优化插入排序----采用二分查找的方法查找插入位置
void Sort2(int* arr,size_t size)//优化插入排序
{
	//外循环遍历所有数值，从前往后{
	//使用二分查找，找带插入位置(循环条件 left <= right){}
	//搬移元素(循环条件 left <= end){
	//还原key值，arr[left+1] = key;}}
	int left = 0;
	int right = size-1;
	size_t i = 0;
	for(i = 1; i < size; i++)
	{
		left = 0;
		right = i - 1;
		int key = arr[i];
		int end = i - 1;
		while(left <= right)//查找插入位置
		{
			int mid = left + ((right - left)>>1);
			if(arr[i] < arr[mid])
				right = mid - 1;
			else 
				left = mid + 1;
		}
		while(left <= end)//搬移数据
		{ 
			arr[end+1] = arr[end];
			end--;
		}
		arr[left] = key;//将数据小的放在前边
	}
}

//插入排序的缺点：
//当数据量比较大时，比较的次数增多，搬移的数据量大，效率低
//当数据越无序，效率越低

//希尔排序----对直接插入排序的改进(将数据分组)
//目的：处理数据一次排序太多，和数据不接近有序问题..
//时间复杂度：O(N^1.25)---O(6*N^1.25)
//注：希尔排序为不稳定排序

void Sortx(int* arr,size_t size)
{
	//当gep为素数时最优：gep = size/3+1
	//间距循环大于0 gep > 0 {  ---->-改进gep > 1 { get = gep/3+1;
	//循环遍历当前分组,i = gep；i < size;i++ (+1表示跳跃分组处理，+gep连续分组处理)
	//{end = i-gep;
	//循环移动数据 end >= 0 && key < arr[end]{
	//arr[end+gep] = arr[end];
	//end = end-gep;} 
	//arr[end+gep] = key还原key值}
	//gep--; }

	//int gep = 3;
	int  gep = size-1;
	while(gep > 1)
	{
		gep = gep/3+1;
		size_t i = 0 ;
		for(i = gep; i < size; i++)
		{
			int end = i-gep;//注此处不要使用无符号类型，否则存在越界问题
			int key = arr[i];
			while(end >= 0 && key < arr[end])
			{
				arr[end+gep] = arr[end];
				end = end-gep;
			}
			arr[end+gep] = key;
		}
		gep--;
	} 
}

	template<class T>
void Swap(T* L,T* R)
{
	T tmp = *L;
	*L = *R;
	*R = tmp;
}

//选择排序----不稳定排序
//时间复杂度O(N^2)
//template<class T>
int ChooseSort(int* arr,size_t size)
{
	size_t i,j;
	int max = 0;
	for(i = 0; i < size-1; i++)//循环排序所有数据
	{
		max = 0;//起始假设第一个数据最大
		for(j = 0; j < size-i; j++)//找出但前轮最大的数子的下标
		{
			if(arr[max] < arr[j])
				max = j;
		}

		if(max != size-i-1)//将最大的数据放在但前轮的最后一个位置
		{
			int tmp = arr[max];
			arr[max] = arr[size-i-1];
			arr[size-i-1] = tmp;
		}
	}
}

//选择排序优化
//一轮找出当前轮中最大，最小的两个数，将最大，最小的数放在相应的位置处
	template<class T>
void ChooseSort2(T* arr,size_t size)
{	
	size_t begin = 0;
	size_t end = size-1;
	size_t i = 0;
	while(begin < end)//循环处理所用数据
	{
		i = begin;
		T min = begin;
		T max = begin; 
		//找出当前轮最小的数据下标
		for(; i <=  end; i++)//注此处必须取=
			if(arr[min] > arr[i])
				min = i;
		//找出当前轮最大的数据下标
		for(i = begin; i <= end; i++)//取=
			if(arr[max] < arr[i])
				max = i;
		//将最小的数据放在当前轮的最前面
		if(min != begin)
			Swap(&arr[min],&arr[begin]);
		//处理最大数据在最前面的位置处时，导致最大的数据被移动到min位置问题
		if(max == begin)
			max = min;
		//将最大的数据放在当前轮的最后
		if(max != end)
			Swap(&arr[max],&arr[end]);
		//当前轮最大，最小数据位置处理完毕，进行下一轮处理
		begin++;end--;
	}
}

//冒泡排序----稳定排序
	template<class T>
void BubbleSort(T* arr,size_t size)
{
	size_t i = 0;
	size_t j = 0;
	T tmp = 0;//标记判断是否有序
	for(; i < size-1; i++)//循环排序所有数据
	{
		tmp  = 0;
		for(j = 0; j < size-i-1; j++)//每两个数据依次进行比较，将大的朝后移动，直至放在当前轮的最后
		{
			if(arr[j] < arr[j+1])
				Swap(&arr[j],&arr[j+1]);
			tmp = 1;
		}
		if(tmp == 0)
			return ;
	}
}


//快速排序---递归处理方法1，2
//时间复杂度O(lgN)
	template<class T>
void FastSort(T* arr,size_t left,size_t right)
{

	if(arr && left < right)//递归出口
	{
		//size_t dev = _FastSort(arr,left,right);
		size_t dev = 0; 
		//dev = _FastSort2(arr,left,right);//单轮处理
		dev = _FastSort3(arr,left,right);//单轮处理
		FastSort(arr,left,dev);//处理前面部分
		FastSort(arr,dev+1,right);//处理后面部分
	}

}
//快速排序方法1
	template<class T>
size_t _FastSort(T* arr,size_t left,size_t right)
{
	if(!arr || left >= right)
		return 0;
	size_t begin = left;//左标记
	size_t end = right-1;//右标记
	while(begin < end)//循环出口
	{
		T key = arr[end];//标记最后一个数据作为参考值
		while(begin < end && arr[begin] <= key )//左值<参考值，左标记向后移动
			begin++;
		while(begin < end && arr[end] >= key)//右值>参考值，右标记向前移
			end--;
		if(begin < end)//左值与右值不在同一位置
			Swap(&arr[begin],&arr[end]);//交换左右数值
	}
	if((int)begin < (int)right-1)//左值位置不在最后位置
		Swap(&arr[begin],&arr[right-1]);//交换左值与最后的数据
	return begin;//返回左值位置，作为数据前后的分隔位置
}
//快速排序方法2
	template<class T>
size_t _FastSort2(T* arr,size_t left,size_t right)
{
	int begin = left;
	int end = right-1;
	if(!arr && left >= right)
		return 0;
	T key = arr[end];
	while(begin < end)
	{
		while(begin < end && arr[begin] <= key)
			begin++;
		if(begin < end)
			arr[end--] = arr[begin];
		while(begin < end && arr[end] >= key)
			end--;
		if(begin < end)
			arr[begin++] = arr[end];
	}
	arr[begin] = key;//注在循环外
	return begin;
}
//快速排序方法3
	template<class T>
void FSort(T* arr,int right)
{
	int left = 0;
	int end = right-1;
	if(!arr || left >= end)
		return ;
	T key = arr[0];

	while(left < end)//循环处理至左与右相遇，才一轮处理完毕
	{
		//处理右侧大于key的值
		while(left < end && arr[end] >= key)
			end--;
		if(left < end)
			arr[left++] = arr[end];
		//处理左侧小于key的值
		while(left < end && arr[left] <= key)
			left++;
		if(left < end)
			arr[end--] = arr[left];//key处的值被覆盖

		arr[left] = key;
	}
	//arr[left] = key;//还原key值
	FSort(arr,left);
	FSort(arr+left+1,right-left-1);
}

	template<class T>
int _FastSort3(T*arr,int left,int right)
{
	int cur = left;
	int prev = left-1;
	T key = arr[right-1];

	while(cur < right)
	{
		if(arr[cur] < key && ++prev != cur)
			Swap(&arr[cur],&arr[prev]);
		cur++;
	}

	if(++prev != right)
		Swap(&arr[prev],&arr[right-1]);
	return prev;
}

//快排
//时间复杂度：数据刚好可分成两部分时最优O(NlgN) 最差O(N^2)
//缺陷：当数据为倒序时，排序的效率低，O(N^2)
//解决：每次使用中间值(数值大小)作为比较值

//快排使用递归，当数据量比较大时，效率低
//当数据个数大于16时，使用插入排序

//使用栈，实现非递归的快排
void FSortStack(int* arr,size_t size)
{
	if(!arr || size < 1)
		return ;
	stack<int> s;
	int left = 0;
	int right = size-1;
	//左右入栈
	s.push(right);
	s.push(left);
	//循环排序
	while(!s.empty())
	{
		//获取当前左右的范围
		left = s.top();s.pop();
		right  = s.top();s.pop();
		//进行单轮排序
		int begin = left;
		int end = right;
		int key = arr[end];//比较值
		while(begin < end)
		{
			if(begin < end && arr[begin] < key)
				begin++;
			arr[end] = arr[begin];
			if(begin < end && arr[end] > key)
				end--;
			arr[begin] = arr[end];
		}
		arr[begin] = key;//还原比较值
		//进行排序左侧部分
		if(left < begin-1)
		{
			s.push(begin-1);
			s.push(left);
		}
		//排序右侧部分
		if(right > begin+1)
		{
			s.push(right);
			s.push(begin+1);
		}
	}
}

//快排缺陷，当数据倒序时进行顺序排序效率低为O(N^2)
//由于每次划分不均匀，不是按倍均匀划分，所以每个数据的排列都得遍历一次所有的数据，时间复杂度为O(N^2)
//解决方法：选取合适的参考值，使数据按均匀化份分
//快排优化---三数取中法

int num(int* arr,int left,int right)//将数据排序，将中间值放在最左侧，并返回作为参考值
{
	int mid = left+((right-left)>>1);
	if(arr[right] < arr[mid])
		Swap(&arr[mid],&arr[right]);
	if(arr[left] > arr[right])
		Swap(&arr[left],&arr[right]);
	if(arr[left] < arr[mid])
		Swap(&arr[left],&arr[mid]);
	return arr[left];//返回最左值作为参考值
}

void FSortQ(int* arr,int size)
{
	stack<int> s;
	int left = 0;
	int right = size-1;
	//	int key = num(arr,begin,end);
	//先将左右入栈
	s.push(left);
	s.push(right);
	//栈不为空，循环排序
	while(!s.empty())
	{
		//获取当前轮排序范围
		right = s.top(); s.pop();
		left = s.top(); s.pop();
		//进行当前轮排序
		int begin = left;
		int end = right;
		int key = num(arr,begin,end);		
		while(begin < end)
		{

			while(begin < end && arr[end] >= key)
				end--;
			arr[begin] = arr[end];

			while(begin < end && arr[begin] <= key)
				begin++;
			arr[end] = arr[begin];
		}
		arr[begin] = key;

		//获取范围
		if(left < begin-1)//获取左侧部分
		{
			s.push(left);
			s.push(begin-1);
		}

		if(right > begin+1)//获取右侧部分
		{
			s.push(begin+1);
			s.push(right);
		}
	}	
}


//归并处理--选取小的数据放在新空间中，依次存放两部分的数据，即完成两部分的有序合并
void MergeData(int* arr,int left,int mid, int right,int* temp)
{
	int begin1 = left;
	int end1 = mid;
	int begin2 = mid;
	int end2 = right;
	int index = 0;    //注拷贝时temp未加left,此处不可赋值为left
	//	int index = left;    //注拷贝时temp未加left,此处不可赋值为left
	while(begin1 < end1 && begin2 < end2)//循环选取小的数据放在新的空间中
	{
		if(arr[begin1] <= arr[begin2])//前部分数据小
		{
			temp[index++] = arr[begin1++];//该数据放在新的空间中，前部分标记后移
		}
		else
		{
			temp[index++] = arr[begin2++];
		}
	}
	while(begin1 < end1)//前部分数据未放完
	{
		temp[index++] = arr[begin1++];
	}

	while(begin2 < end2)//后部分数据未放完
	{
		temp[index++] = arr[begin2++];
	}
}
//归并排序---递归函数
void MergeSort(int* arr,int left,int right,int* temp)
{
	if(right - left > 1)//划分只有1个元素时退出，不在划分，进行归并处理
	{
		int mid = left+((right-left)>>1);//每次划分成两部分
		MergeSort(arr,left,mid,temp);//处理前部分
		MergeSort(arr,mid,right,temp);//处理后部分
		//		MergeData(arr,left,mid,right,temp);//合并处理(将两部分进行有序合并)
		memcpy(arr+left,temp,sizeof(arr[0])*(right-left));//将新空间当前的新数据，存放在上次存放的后面
		memcpy(arr+left,temp+left,sizeof(arr[0])*(right-left));//将新空间当前的新数据，存放在上次存放的后面
	}
}
//递归归并排序
void MS(int* arr,int size)
{
	int* temp = (int*)malloc(sizeof(int)*size);
	if(temp == NULL)
		return ;
	MergeSort(arr,0,size,temp);
	free(temp);
}

//非递归归并排序
void MSNor(int* arr,int size)
{
	int* temp = (int*)malloc(sizeof(int)*size);//保存合并后的结果
	if(temp == NULL)
		return ;
	int gap = 1;//先从一个数据开始合并
	int left = 0,right,mid;
	while(gap < size)
	{
		for(int i = 0; i < size; i += 2*gap)
		{
			left = i;
			mid = left+gap;//中间位置
			if(mid > size)
				mid = size;//mid越界，调整mid到最后
			right = mid+gap;
			if(right > size)
				right = size;//right越界，调整到最后
			MergeData(arr,left,mid,right,temp);
			memcpy(arr+left,temp,sizeof(arr[0])*(right-left));
		}
		gap *= 2;//每次合并后，下次合并的数据个数扩大2倍
	}
	//	memcpy(arr,temp,sizeof(arr[0])*size);
	free(temp);
}

//归并排序：稳定
//归并排序时间复杂度：O(N*lgN)
//递归空间复杂度：
//非递归空间复杂度：O(1)


//计数排序---不稳定排序
//时间复杂度：O(N), 空间复杂度：O(M) M数据范围
//统计元素个数(空间大小= max-min,先确定数据大小范围(max，min))
//将数据的的次数放在数据所映射的下标中
//按下标映射的数值和次数的顺序输出数据，即为有序的数据
//释放空间，退出

typedef struct Num
{
	int Max;
	int Min;
}Num;

void Fun(int* arr,int size,Num* mm)
{
	mm->Max = arr[0];
	mm->Min = arr[0];
	int i = 1;
	for(;i < size; i++)
	{
		if(arr[i] < mm->Min)
			mm->Min = arr[i];
		else if(arr[i] > mm->Max)
			mm->Max = arr[i];
	}

}
#include<string.h>
void NSort(int* arr,int size)
{
	Num mm;
	mm.Max = 9;
	mm.Min = 0;
	//	Fun(arr,size,&mm);//计算数据范围
	int sz = mm.Max - mm.Min+1;
	int* num = (int*)malloc(sizeof(int)*sz);
	memset(num,0,sizeof(arr[0])*sz);//初始化新开辟的空间
	int i = 0;
	for(; i < size; i++)//统计个数
	{
		num[arr[i]-mm.Min] += 1;
	}
	//按顺序写回原数组中
	int j = 0;
	i = 0;
	while(j <= sz)
	{
		while(num[j]--)
		{
			arr[i++] = j+mm.Min;
		}
		j++;
	}
	free(num);
}

//堆向下调整
void AdjustDown(int* arr,int size,int parent)
{
	int child = parent*2+1;
	while(child < size)
	{
		if(child+1 < size && arr[child] < arr[child+1])
			child++;
		if(arr[parent] < arr[child])
		{
			Swap(&arr[parent],&arr[child]);
			parent = child;
			child = parent*2+1;
		}
		else
			return ;
	}
}

//堆排序
void HeapSort(int* arr,int size)
{
	if(!arr || size < 1)
		return ;
	int parent = (size-2) >> 1;
	int i = 0;
	//堆调整
	for(i = parent; i >= 0;i--)
		AdjustDown(arr,size,i);
	//堆排序	
	for(i = size-1; i > 0;)
	{
		Swap(&arr[0],&arr[i]);//将堆顶与当前最后一个元素交换
		AdjustDown(arr,i,0);//从堆顶向下调整(调整i个元素)
		i--;//注：调整是一个开区间，即i是不进行调整的，所以调整之后在--
	}
}

int maxnum(int* arr,size_t size)
{
	size_t i = 0;
	int tmp = arr[0];
	for(i = 1; i < size ; i++)
	{
		if(tmp < arr[i])
			tmp = arr[i];
	}
	return tmp;
}

//基数排序(桶排序)----稳定排序，时间复杂度：O(N),空间复杂度：O(N)
//低位关键码优先---先排低位   高位关键码优先----先排高位(与低位有区别，每位排好后，数据所在的桶不可变，只能桶内调整，即需采用递归)
//根据数据位数(按个位，十位...)排序，(先求最大数据的位数)
//利用哈希函数(取模映射)，有10中情况(0-9),数组大小为10
//开辟一个空间(大小10)的桶(队列)，每个桶可存多个数据，根据取模的方法获取位数值，再根据值将数据放在对应的桶中
//某个桶的地址 = 桶的起始地址+偏移量(之间 数据元素个数)

void RadixSortMsd(int* arr,size_t size)
{
	//1、开辟10个大小的数组(桶个数10)
	//桶：桶可以为队列(开销大)，
	//不使用队列：使用用一个数组，桶连续放在一个内存中，下一个桶位置 = 上一个桶地址+上一个桶元素个数
	//1.1 开辟一个数组，大小为10，表示10个桶---count[10]，存储桶中的元素
	//循环10次，遍历数据集，统计每个桶中的数据个数(数据%10作为下标)，桶中存数据个数
	//1.2，定义一个数组大小为10(桶个数)，存储每个桶的起始位置，---startadds[10]  桶的起始地址
	//循环9次,统计桶的起始地址，桶起始位置 = 上一个桶的地址+上一个桶的元素个数
	//1.3、定义一个桶，桶的大小为size（动态开辟）----bucket[size]

	//2、入桶：将数据进行通过哈希函数(数据取模运算)放在对应的桶中，
	//2.1、循环size次，取数据的低位(%10)，获取桶的下标(桶地址)，将数据存在对应的桶中，同时++，(++表示存储位置后移，该位置已存储数据)
	//for(i < size;i+)
	//{
	//int buno = arr[i]%10; //计算桶编号
	//bucket[startadds[buno]++] = arr[i];//根据桶编号，将数据放在对应的桶中，同时++，表示该位置已存储数据，下次往后存储
	//}
	//3、回收数据：按从小到大的桶号顺序回收(放到原数组中)		  
	//循环处理其它位(循环次数为最大数据的位数)
	//处理高位：类似2-3步驻，处理完所有数据的位(个位——>高位)，即得到有序数据	  

	int max = maxnum(arr,size);//获取最大数据
	int bitnum = 1;//位标记
	while(bitnum < max*10)//循环处理各个位
	{
		int count[10]={0};//需初始化 --- 注：每个位的排列都是无关的，所以必须放在循环内部
		int startadds[10] = {0};//需初始化起始地址(桶所在的下标)
		size_t i = 0;
		//统计每个桶中数据个数
		for(i = 0;i < size; i++)
		{
			count[arr[i]/bitnum%10]++;
		}
		//计算桶的起始位置(各个桶所在的下标)
		for(i = 1; i < 10; i++)
			startadds[i] = startadds[i-1]+count[i-1];
		int* bluck = (int*)malloc(sizeof(int)*size);
		//将数据放在对应的桶中
		for(i = 0; i < size; i++)
		{
			int number = arr[i]/bitnum%10;
			bluck[startadds[number]++] = arr[i];
		}
		//将桶中的数据回收(放回数组)
		memmove(arr,bluck,sizeof(int)*size);
		bitnum *= 10;//处理下个位(高位)
	}
}

void print(int* arr,size_t size)
{  
	size_t i = 0;
	for(; i < size; i++)
	{
		cout << arr[i] << " " ;
	}
	cout << endl;
}
int main()
{
	int arr[] = {1,9,8,9,4,6,9,8,2,0};
	size_t sz = sizeof(arr)/sizeof(arr[0]);
	print(arr,sz);
	// Sortx(arr,sz);
	// ChooseSort2(arr,sz);
	// BubbleSort(arr,sz);
	//FastSort(arr,0,sz);
	// FSort(arr,sz);
	//FSortStack(arr,sz);
	//MS(arr,sz);
	//	MSNor(arr,sz);
	//	NSort(arr,sz);
	//	HeapSort(arr,sz);
//	FSortQ(arr,sz);
	RadixSortMsd(arr,sz);
	print(arr,sz);
	return 0;
} 
