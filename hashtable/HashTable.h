/*
#ifndef __HASHTABLD_H__

#define __HASHTABLD_H__

typedef int type;

enum state{Empty,Exist,DExist};

typedef struct Endm//位置
{
	type _data;//数据值
	enum state _state;//位置状态
}Endm;

typedef struct HashTable//哈希表
{
	Endm* _Data;//结构体指针类型，动态顺序表存储
	size_t _size;//数据个数
	size_t _capacity;//容量
}HT;

void InitHashTable(HT* ht);//初始化
void AddSerave(HT* ht,size_t key);//扩容,key用于指定空间大小
void InsertHashTable(HT* ht,type data);//插入
size_t HashFunk(HT* ht,type data);//哈希函数(获取映射地址)
int FindHashTable(HT* ht,type data);//查找
void DeleteHashTable(HT* ht,type data);//删除
void PrintHashTable(HT* ht);
size_t DetectiveLine(HT* ht,size_t key);//线性探测

//素数表函数

void Hash_test();//测试

void Application_test();

#endif

*/