/*
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>
#include"HashTable.h"

void InitHashTable(HT* ht)//初始化
{
	size_t i = 0;
	assert(ht);
	ht->_capacity = 3;//开三个空间
	ht->_size = 0;
	ht->_Data = (Endm*)malloc(sizeof(Endm)*ht->_capacity);
	assert(ht->_Data);
	for(; i < ht->_capacity; i++)
		ht->_Data[i]._state = Empty;//状态置空
}

size_t DetectiveLine(HT* ht,size_t key)//线性探测
{
	key++;
	if(key >= ht->_capacity)
		key = 0;
	return key;
}

void AddSerave(HT* ht,size_t key)//扩容
{
	if(ht->_size == ht->_capacity || key >= ht->_capacity)
	{
		size_t i = 0;
		Endm* newData = NULL;

		ht->_capacity = key;//扩大到key
		while(ht->_capacity < key || ht->_size >= ht->_capacity)
			ht->_capacity *= 2;//容量扩大2倍

		newData = (Endm*)malloc(sizeof(Endm)*ht->_capacity);
		assert(newData);
		memcpy(newData,ht->_Data,sizeof(Endm)*ht->_size);
		free(ht->_Data);
		ht->_Data = newData;
		//初始化新增位置状态
		for(i = ht->_size; i < ht->_capacity; i++)
			ht->_Data[i]._state = Empty;
	}
}

size_t HashFunk(HT* ht,type data)//哈希函数(获取映射地址)
{
	return data % (ht->_capacity);//此处应模取最接近(<=容量)容量的素数
}

void InsertHashTable(HT* ht,type data)//插入
{
	size_t key = 0;
	key = HashFunk(ht,data);//哈希函数(获取映射地址)
	AddSerave(ht,key);//扩容处理
	//寻找可插入位置（空，或删除非空）
	while(ht->_Data[key]._state == Exist)
	{
		//线性探测
		key = DetectiveLine(ht,key);
	}
	//ht->_Data[key]._data = 1;
	ht->_Data[key]._data = data;
	ht->_Data[key]._state = Exist;
	ht->_size++;
}

int FindHashTable(HT* ht,type data)//查找
{
	size_t key = HashFunk(ht,data);//哈希函数(获取映射地址)
	size_t tmp = key;//标记起始查找地址
	assert(ht);
	if(ht->_size == 0)
		return -1;

	while(ht->_Data[key]._state != Empty)
	{
		//if(key == data)//字符应用处理添加
		//return key;

		if(ht->_Data[key]._data == data)
			return key;
		//线性探测
		key = DetectiveLine(ht,key);

		if(key == tmp)//再次到达key--->未找到
			break;
	}
	return -1;
}

void DeleteHashTable(HT* ht,type data)//删除
{
	size_t key = 0;
	assert(ht);
	key = FindHashTable(ht,data);//查找
	if(key < 0)//未找到
		return ;
	ht->_Data[key]._state = DExist;
	ht->_size--;
}

void PrintHashTable(HT* ht)
{
	size_t i = 0;
	while(i < ht->_capacity)
	{
		if(ht->_Data[i]._state == Exist)
		printf("%d ",ht->_Data[i]);
		i++;
	}
	printf("\n");
}

void Hash_test()//测试
{
	HT ht;
    InitHashTable(&ht);//初始化
	AddSerave(&ht,10);//扩容
    InsertHashTable(&ht,1);//插入
    InsertHashTable(&ht,3);//插入
    DeleteHashTable(&ht,1);//删除
    InsertHashTable(&ht,11);//插入

    InsertHashTable(&ht,1);//插入
    InsertHashTable(&ht,9);//插入
    InsertHashTable(&ht,2);//插入
    InsertHashTable(&ht,8);//插入
	InsertHashTable(&ht,9);//插入
    InsertHashTable(&ht,2);//插入
    InsertHashTable(&ht,8);//插入
    InsertHashTable(&ht,0);//插入

    printf("%d\n",FindHashTable(&ht,2));//查找
    DeleteHashTable(&ht,1);//删除
    InsertHashTable(&ht,1);//插入
    InsertHashTable(&ht,4);//插入

    PrintHashTable(&ht);
}

/*
//字符应用处理
void Application_test()
{
	char ch[] = {"ahabccdssdfzkycbabcsd"};
	int i = 0;
	size_t sz = sizeof(ch)/sizeof(ch[0]);
	HT hc;
	InitHashTable(&hc);//初始化
	AddSerave(&hc,255);//扩容
	//根据字符对应的数值，放在对应的哈希表地址中,表中存储的是个数
	for(; i < sz; i++)
	{
		//int c = FindHashTable(&hc,2);//返回下标---下标即为字符的ASCLL
		if(FindHashTable(&hc,ch[i]) == ch[i])
			hc._Data[ch[i]]._data++;
		else
			 InsertHashTable(&hc,ch[i]);//插入
	}
	//遍历字符串，找出出现次数为1的字符
	for(i = 0; i < sz; i++)
	{
		int key = FindHashTable(&hc,ch[i]);
		if(hc._Data[key]._data == 1)
		{
			printf("%c ",ch[i]);
			//break;
		}
	}
}

//哈希表
//将数据存储在顺序表中，存储时按某种映射关系(哈希函数)存储在对应的下标处。
//哈希函数：hf(Key) = A*Key+1;
//哈希函数：
//1、直接定制法：
//直接根据数据与下标的关系，确定映射

//应用：求一个字符串中第一次只出现一次的字符
//解：建一个大小为256(最多有256种字符)的哈希表
//根据字符的数值，作为对应的下标，数组中放出现的次数（循环遍历一次所有数据）
//遍历字符串中的字符，确定那个字符第一次出现，返回字符即可

//除留余数法：
//地址(下标) = 数据 % p；(p是最接近哈希大小的素数（p <= max_size）)

//哈希冲突：
//原因：哈希函数的不合理
//哈希冲突是无法避免的，
//解决：闭散列
//冲突检测：使用位置状态标记的方法：三种状态：空，非空，删除非空
//方法：冲突后，将数据放在冲突位置的后面的空位处(每个位置有三种状态：空，不空，删除不空)
//线性探测：查找时从映射的地址处开始向后找，直到找到(数据相同)或遇到空位退出
//注：若到达最后一个元素还未找打，则返回到表的起始位置，继续向后找
//插入：映射的地址状态为空--->直接插入，不为空--->查找从该地址后查找插入位置
//插入位置查找与查找类似，插入在空(或删除非空)位置处，插入前线检侧是否表满，表满扩容
//查找：计算映射地址，从映射地址处开始查找，直到找到数据或遇到空位置退出(注意：回到起始查找位置也应退出)
//删除仅将删除为位置状态更改为 删除不空 （注：退出条件防止出现死循环，回到起始位置也应退出）

//线性探测缺陷：数据堆积(一但发生冲突，就会容易连续发生冲突)
//数据越多也容易发生冲突，
//解决方法：1、使用负载因子控制扩容，2、采用二次探测不使用顺序探测
//负载因子：size/capacity <= 0.7~0.8 效率较高
//          size*10/capacity <= 7~8（*10是处理整型除法问题）
//二次探测：
//H(i+1) = Hi + (2*i+1);(i = 0, 1,2,3...)
//缺陷：当容量快满时，会一直查找空位，导致效率低
//解决方法：使用控制负载因子增容--->以空间换时间


//综上待处理问题
//1、动态增容----如何使用负载因子增容
//如何将数据放回到新空间，不可直接内存复制？，使用诼个插入的方法(只插入有效元素)，交换哈希表的内容，释放旧空间
//2、哈希函数中，%素数，素数如何查找
//
//3、存储字符串，时如何求映射地址？
//除留余数法：如何处理 字符串取模问题？
//解决方法：字符串转化成整型
//1、将每个字符对应的ASCLL数值相加
//2、字符哈希算法，将字符串转化成数字
//3、使用函数指针，将所有字符串数据类型转换成整型
//注：哈希表结构体中，添加一个函数指针类型变量，用于转化数据类型

*/