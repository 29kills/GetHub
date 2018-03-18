//布隆过滤器
/*
2. 熟悉布隆过滤器的原理，实现以下接口 
typedef char* DataType; 
typedef size_t (*PHF)(DataType); 
#define FUNCNUM 5 

typedef struct BloomFilter 
{ 
	BitMap _bmp; 
	PHF _HashFunc[FUNCNUM]; 
	size_t _size; 
}BF; 

//////////////////////////////////////////////////////////////////// 
// BloomFilter.h 
void InitBloomFilter(BF* bf, PHF hashFunc[FUNCNUM], size_t size); 
int InsertBF(BF* bf, DataType key); 
int IsInBloomFilter(BF* bf, DataType key); 
void DestroyBloomFilter(BF* bf); 
*/

#ifndef __BLOOMFILTER_H__

#define __BLOOMFILTER_H__

#include"BitMap.h"
#define FUNCNUM 5 //哈希函数个数

typedef char* DataType; 
typedef size_t (*PHF)(DataType); 
 


typedef struct BloomFilter 
{ 
	BitMap _bmp; //位图
	PHF _HashFunc[FUNCNUM]; //哈希函数（地址映射）
	size_t _size; //个数
}BF; 

void InitBloomFilter(BF* bf, PHF hashFunc[FUNCNUM], size_t size); 
int InsertBF(BF* bf, DataType key); 
int IsInBloomFilter(BF* bf, DataType key);//判断是否存在 
void DestroyBloomFilter(BF* bf); 

void BF_test();

#endif