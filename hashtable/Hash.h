#ifndef __HASH_H__

#define __HASH_H__

#define _pMax 18

typedef char* type;
//typedef int type;


enum stateD{EmptyD,ExistD,DExistD};

typedef size_t (*Compare)(const type str);

typedef struct EndmD//位置
{
	type _data;//数据值
	enum stateD _state;//位置状态
}EndmD;

typedef struct HashTableD//哈希表
{
	EndmD* _Data;//结构体指针类型，动态顺序表存储
	size_t _size;//数据个数
	size_t _capacity;//容量
	Compare _com;//字符串转数值
}HTD;

void InitHashTableD(HTD* ht,size_t sz,Compare com);//初始化
//void InitHashTableD(HTD* ht,size_t sz);//初始化

size_t achievePrm(size_t sz);//获取素数
void AddSeraveD(HTD* ht,size_t key);//扩容,key用于指定空间大小
void Swap(HTD*ht,HTD* tmph);//交换
void InsertHashTableD(HTD* ht,type data);//插入
size_t HashFunkD(HTD* ht,type data);//哈希函数(获取映射地址)
int FindHashTableD(HTD* ht,type data);//查找
void DeleteHashTableD(HTD* ht,type data);//删除
void PrintHashTableD(HTD* ht);

size_t DetectiveLineD(HTD* ht,size_t key);//线性探测
size_t DeletectiveTwoD(HTD* ht,size_t key1);//二次探测

static size_t BKDRHash(const char* str);//字符串哈希算法(字符串转数值)
static size_t intBKDRHash(const type data);//字符数字处理

//素数表函数

void Hash_testD();//测试

void Application_testD();

#endif