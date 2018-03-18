/*
熟悉开散列的原理，实现哈希桶 
要求： 
1. 任意类型都可以处理 
2. 扩容降低哈希冲突 

typedef char* K; 
typedef char* V; 

typedef struct Pair 
{ 
	K _key; 
	V _value; 
}Pair; 

typedef struct Node 
{ 
	struct Node* _pNext; 
	Pair _data; 
}Node, *PNode; 


typedef struct HashTable 
{ 
	PNode* _table; 
	unsigned long _capacity; 
	unsigned long _size; 
	PHF _DateToInt; 
}HT; 


////////////////////////////////////////////////////////// 
// .h 
void InitHashBucket(HT* ht, int capacity, PHF dataToInt); 
int InsertHashBucketUnique(HT* ht, K key, V v); 
int DeleteHashBucketUnique(HT* ht, K key); 

void InsertHashBucketEqual(HT* ht, K key, V v); 
int DeleteHashBucketEqual(HT* ht, K key); 
PNode FindHashBucket(HT* ht, K key); 
int CheckCapacity(HT* ht); 
void DestroyHashBucket(HT* ht); 

int HashFunc(HT* ht, K key); 
PNode BuyNode(K key, V value); 
void PrintHashBucket(HT* ht); 

哈希部分的内容，最好写一篇博客 
*/

#ifndef __HASHT_H__

#define __HASHT_H__


typedef char* typeT;
typedef char* typeV;

typedef size_t (*Comp)(const typeT str);

typedef struct Pari//数据单元
{
	typeT _data;
	typeV _value;
}Pair;

typedef struct List//数据链
{
	Pair _cell;
	struct List* Next;
}Node,*pNode;

typedef struct HashTableT//哈希表
{
	pNode* _Data;//哈希数据集，二级指针
	size_t _size;//数据个数
	size_t _capacity;//容量
	Comp _com;//字符串转数值
}HTT;

void InitHashBucket(HTT* ht, int capacity, Comp com); //初始化
int InsertHashBucketUnique(HTT* ht, typeT key, typeV v); //插入
int DeleteHashBucketUnique(HTT* ht, typeT key); //删除
void InsertHashBucketEqual(HTT* ht, typeT key, typeV v); 
int DeleteHashBucketEqual(HTT* ht, typeT key); 
pNode FindHashBucket(HTT* ht, typeT key); 
int CheckCapacity(HTT* ht); //检查容量
void DestroyHashBucket(HTT* ht); //销毁
void CleanHashBucket(HTT* ht); //清空

size_t HashFunc(HTT* ht, typeT key); 
pNode BuyNode(typeT key, typeV value); 
void PrintHashBucket(HTT* ht); 

static size_t BKDRHashT(const char* str);//字符串哈希算法(字符串转数值)
static size_t intBKDRHashT(const typeT data);//字符数字处理

void HashT_test();

#endif

//开散列(开链法)
//哈希桶：哈希表中存放的不在是数据，而是具有相同映射关系的链表的表头
//哈希表中存的是一个结构体指针变量，二级指针，由于哈希表存的是一组数据(一级指针)，每个位置为一个链表(二级指针)
//哈希函数：key = 数据%容量
//注：不插入重复数据,无数据的位置桶为空。
//缺点：当冲突比较大时，查找数据的时间复杂度增大(变成链表查找)	
//解决放法：空间增容---重新计算映射地址，重排布(增容时机：链表长接近桶容量时增容)

//扩容：(size == capacity)
//方法1：与之前相同
//方法2：
//1、获取新空间大小
//创建一个新的哈希表的数据集合(原来的2倍)
//遍历旧哈希表，循环条件，i < capacity;
//当前桶不为空(某一位置)
//{
//将当前桶中的元素放在新的桶中：
//创建一个节点，将旧数据考到节点中
//获取映射地址(%新容量)
//将节点添加到映射地址中
//}
//注：处理单个桶中的链表过长问题：将链表转化成一个红黑树