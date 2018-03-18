#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>
#include"BitMap.h"

void Init_BitMap(BitMap* mp,size_t size)
{
	assert(mp);
	mp->_capacity = (size>>5)+1;
	mp->_size = 0;
	mp->_data = (typeB*)malloc(sizeof(typeB)*mp->_capacity);
	memset(mp->_data,0,sizeof(typeB)*mp->_capacity);//所有数据置0
	assert(mp->_data);
}

int Insert_BitMap(BitMap* mp,typeB data)
{
	size_t idx = 0;//下标
	assert(mp);
	idx = data >> 5;//数据存放的下标位置(类似与映射)
	//数据已存储
	if(Test(mp,data))
		return 0;
	Set(mp, data); //位置置1
	mp->_size++;
	return 1;
}

//数据对应的bit位置1
void Set(BitMap* mp, size_t data)
{
	size_t idx = data >> 5;
	mp->_data[idx] |= 1 << (data%32);
}

//数据bit位置0
void ReSet(BitMap* mp, size_t data)
{
	size_t idx = data >> 5;
	mp->_data[idx] &= ~(1 << (data%32));
}

//判断位是否为1
int Test(BitMap* mp, size_t data)
{
	size_t count = 0;
	size_t idx = data >> 5;
	if(idx >= mp->_capacity)//越界不存在
		return -1;
	assert(mp);
	return (mp->_data[idx] &(1 << (data%32)));	
}

size_t CountBitMap(BitMap* mp)
{
	size_t i = 0;
	size_t j = 0;
	size_t count =0;
	char* bitCount = "\0\1\1\2\1\2\2\3\1\2\2\3\2\3\3\4";//四个bit位对应1出现的次数的可能
	assert(mp);
	for(; i < mp->_capacity; i++)//检测所有数据
	{
		typeB tmp = mp->_data[i];
	    j = 0;
		while(j < 4)//检测一个数据
		{
			unsigned char ch = tmp;//取1个字节
			count += bitCount[ch&0x0F];//计算0~3bit位中1的个数
			ch =  ch >> 4;
			count += bitCount[ch&0x0F];//计算4~7bit位中1的个数
			tmp = tmp >> 8;//取下一个字节的第0bit位
			j++;//取下一个字节
		}
	}
	return count;
}

size_t SizeBitMap(BitMap* mp)
{
	assert(mp);
	return mp->_size;
}

void DestroyBitMap(BitMap* mp)
{
	assert(mp);
	free(mp->_data);
	mp->_data = NULL;
	mp->_capacity = 0;
	mp->_size = 0;
}

void BitMap_test()
{
	BitMap mp;
	typeB num [] = {0,1,3,6,5,9,8,7,32,26,5,36,63,65,66};
	size_t sz = sizeof(num)/sizeof(num[0]);
	size_t i = 0;

	Init_BitMap(&mp,66);//初始化传入最大数字
	for(i = 0; i < sz; i++)
    Insert_BitMap(&mp,num[i]);

	//检测某个比特位是否为1 
	if(Test(&mp, 100))
		printf("存在\n");
	else
		printf("不存在\n");

	if(Test(&mp, 10))
		printf("存在\n");
	else
		printf("不存在\n");
	printf("%d \n",SizeBitMap(&mp)); 
	// 位图中1的个数 
	printf("%d\n",CountBitMap(&mp)); 
	DestroyBitMap(&mp); 

}