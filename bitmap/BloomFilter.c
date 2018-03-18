//布隆过滤器
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include"BloomFilter.h"
#include"Compare.h"

//PHF hashFunc[] = {SDBMHash,RSHash,APHash,JSHash,DEKHash};
size_t (*hashF)(const char*) =  {SDBMHash,RSHash,APHash,JSHash,DEKHash};


void InitBloomFilter(BF* bf, PHF hashFunc[FUNCNUM], size_t size)
{
	size_t i = 0;

	Init_BitMap(&bf->_bmp,size);//初始化位图
	bf->_size = 0;
	for(; i < FUNCNUM; i++)
		bf->_HashFunc[i] = hashFunc[i];
}

int InsertBF(BF* bf, DataType key)
{
	size_t i = 0;
	size_t count = 0;
	for(; i < FUNCNUM; i++)//一个字符串占5个bit位表示
	{
		size_t idx = (bf->_HashFunc[i](key))%(bf->_bmp._capacity);//获取数字，并取数字范围在容量内
		if(Test(&bf->_bmp, idx))
			count++;
		if(count == 4)
			return 0;//添加失败
		Set(&bf->_bmp, idx); //数据位置1
	}
	bf->_size++;
	return 1;
}

int IsInBloomFilter(BF* bf, DataType key)
{
	size_t i = 0;
	size_t count= 0;
	size_t j = 0;
	for(; i < bf->_size; i++)
	{
		for(; j < FUNCNUM; j++)//一个字符串占5个bit位表示
		{
			size_t idx = (bf->_HashFunc[j](key))%(bf->_bmp._capacity);//获取数字，并取数字范围在容量内
			if(Test(&bf->_bmp, idx))//相同
			    count++;
		    if(count == 4)
			    return 1;
		}
	}
	return 0;
}

void BF_test()
{
	BF bf;

	InitBloomFilter(&bf,hashF, 10000);//容量越小冲突越高 
    InsertBF(&bf,"123"); 
    InsertBF(&bf,"你好"); 
    InsertBF(&bf,"OK"); 
    InsertBF(&bf,"成功"); 
    printf("%d\n",IsInBloomFilter(&bf, "你好")); 
    printf("%d\n",IsInBloomFilter(&bf, "OK")); 
    printf("%d\n",IsInBloomFilter(&bf, "你1好")); 
    printf("%d\n",IsInBloomFilter(&bf, "001")); 
}
