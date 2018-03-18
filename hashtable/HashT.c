#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>
#include"HashT.h"

void InitHashBucket(HTT* ht, int capacity, Comp com) //初始化
{
	size_t i = 0;
	assert(ht);
	ht->_com = com;
	ht->_size = 0;
	ht->_capacity = capacity;
	ht->_Data = (pNode*)malloc(sizeof(Node*)*ht->_capacity);//哈希表的长度大小
	for(; i < ht->_capacity; i++)//初始化每个桶为NULL
		ht->_Data[i] = NULL;
}

int InsertHashBucketUnique(HTT* ht, typeT key, typeV v) //插入
{
	size_t idx = 0;
	pNode prev = NULL;
	pNode cur = NULL;
	assert(ht);
	idx = HashFunc(ht, key);
	cur = ht->_Data[idx];
	//该位置无数据---链接新数据
	if(cur == NULL)
	{
		ht->_Data[idx] = BuyNode(key, v);//链接新节点
		ht->_size++;
		return 1;
	}
	//该位置有数据---链接新数据
	while(cur)//插入到为空的位置
	{
		if(cur->_cell._data == key)//数据已存在
			return 0;//不插入重复数据
		prev = cur;
		cur = cur->Next;
	}
	cur = BuyNode(key, v);//链接新节点
	prev->Next = cur;
	ht->_size++;
	return 1;
}

int DeleteHashBucketUnique(HTT* ht, typeT key)//删除
{
	size_t idx = 0;
	pNode cur = NULL;
	pNode del = NULL;
	assert(ht);
	idx = HashFunc(ht, key);
	cur = ht->_Data[idx];
	//该位置有数据---对比是否删除
	while(cur)//位置有数据
	{
		//数据是否相同---相同删除
		del = cur;
		cur = cur->Next;
		if(strcmp(del->_cell._data , key) == 0)
		{
			ht->_Data[idx] = cur;
			free(del);
			del = NULL;
			ht->_size--;
			return 1;//不插入重复数据
		}
	}
	return 0;
}

size_t HashFunc(HTT* ht, typeT key)
{
	return ht->_com(key)%ht->_capacity;
}
//创建一个节点
pNode BuyNode(typeT key, typeV value)
{
	pNode newNode = (pNode)malloc(sizeof(Node));
	newNode->_cell._data = key;
	newNode->_cell._value = value;
	newNode->Next = NULL;
	return newNode;
}
void PrintHashBucket(HTT* ht)
{
	size_t i = 0;
	size_t j = 0;
	assert(ht);

	for(; i < ht->_capacity; i++)
	{
		pNode cur = ht->_Data[i];
		while(cur)
		{
			printf("%s %s\n",cur->_cell._data,cur->_cell._value);
			cur = cur->Next;
		}
	}
}

void InsertHashBucketEqual(HTT* ht, typeT key, typeV v)
{
	size_t idx = 0;
	pNode prev = NULL;
	pNode cur = NULL;
	assert(ht);
	idx = HashFunc(ht, key);
	cur = ht->_Data[idx];
	//该位置无数据---链接新数据
	if(cur == NULL)
	{
		ht->_Data[idx] = BuyNode(key, v);//链接新节点
		return ;
	}
	//该位置有数据---链接新数据
	while(cur)//插入到为空的位置
	{
		prev = cur;
		cur = cur->Next;
	}
	cur = BuyNode(key, v);//链接新节点
	prev->Next = cur;
	ht->_size++;
}

int DeleteHashBucketEqual(HTT* ht, typeT key)
{
	size_t sz = ht->_size;
	size_t idx = 0;
	pNode del = NULL;
	pNode cur = NULL;
	assert(ht);
	idx = HashFunc(ht, key);
	cur = ht->_Data[idx];
	//该位置有数据---对比是否删除
	while(cur)//位置有数据
	{
		//数据是否相同---相同删除
		del = cur;//头删
		cur = cur->Next;
		if(strcmp(del->_cell._data , key) == 0)
		{
			if(del == ht->_Data[idx])//处理删头问题
			    ht->_Data[idx] = cur;//更新头节点
			free(del);
			del = NULL;
			ht->_size--;
		}
	}

	if(sz < ht->_size)//判断是否删除过数据
		return 1;
	return 0;
}
pNode FindHashBucket(HTT* ht, typeT key)
{
	size_t idx = 0;
	pNode cur = NULL;
	assert(ht);
	idx = HashFunc(ht, key);
	cur = ht->_Data[idx];
	//该位置有数据---对比是否相同
	while(cur)//位置有数据
	{
		//数据是否相同---相同地址
		if(strcmp(cur->_cell._data , key) == 0)
		{
			return cur;
		}
		cur = cur->Next;
	}
	return NULL;
}

int CheckCapacity(HTT* ht)
{
	return ht->_capacity;
}
void DestroyHashBucket(HTT* ht)//销毁
{
	CleanHashBucket(ht); //清空
	free(ht->_Data);
	ht->_Data = NULL;
}

void CleanHashBucket(HTT* ht) //清空
{
	pNode cur = NULL;
	size_t i = 0;
	pNode del =NULL;
	assert(ht);
	for(; i < ht->_capacity ;i++)//清空哈希表(清空每个桶)
	{
		del = ht->_Data[i];
		while(cur)//清空每个桶中的链表
		{
			/*
			del = cur->Next;
			cur = del->Next;
			free(del);
			del = NULL;
			*/
			del = cur;
			cur = del->Next;
			free(del);
			del = NULL;
		}
	}
}

static size_t BKDRHashT(const char* str)//字符串哈希算法(字符串转数值)
{
	unsigned int seed = 131;
	unsigned int hash = 0;
	while(*str)
	{
		hash = hash * seed + (*str++);
	}
	return (hash & 0x7FFFFFFF);
}

static size_t intBKDRHashT(const typeT data)//字符数字处理
{
	return (unsigned int)data;
}

void HashT_test()
{
	HTT ht;
	InitHashBucket(&ht, 100, BKDRHashT); //初始化
    InsertHashBucketUnique(&ht, "123", "数字"); //插入
    InsertHashBucketEqual(&ht, "25", "数字"); 
    InsertHashBucketUnique(&ht, "123", "数字"); //插入
    DeleteHashBucketUnique(&ht, "25"); //删除

    InsertHashBucketEqual(&ht, "256", "数字"); 
    InsertHashBucketEqual(&ht, "26", "数字"); 
    InsertHashBucketEqual(&ht, "26", "数字"); 
    InsertHashBucketEqual(&ht, "256", "数字"); 
    DeleteHashBucketEqual(&ht, "26"); 
    printf("%p\n",FindHashBucket(&ht, "256")); 
    printf("%d\n",CheckCapacity(&ht)); //检查容量
    PrintHashBucket(&ht); 

    CleanHashBucket(&ht); //清空
	DestroyHashBucket(&ht); //销毁


}