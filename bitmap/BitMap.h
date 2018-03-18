
#ifndef __BITMAP_H__

#define __BITMAP_H__

typedef size_t typeB;
typedef struct BitMap
{
	typeB* _data;
	size_t _size;//数据个数
	size_t _capacity;//容量
}BitMap;

void Init_BitMap(BitMap* mp,size_t size);
int Insert_BitMap(BitMap* mp,typeB data);
void Set(BitMap* bmp, size_t which); 
// 置为0 
void ReSet(BitMap* bmp, size_t which); 
// 检测某个比特位是否为1 
int Test(BitMap* bmp, size_t which); 
size_t SizeBitMap(BitMap* bmp); 
// 位图中1的个数 
size_t CountBitMap(BitMap* bmp); 
void DestroyBitMap(BitMap* bmp); 

void BitMap_test();


#endif

//位图：

//将数据的状态使用bit位表示(1表示存在，0表示不存在)
//第一个图数据有32个bit位，可表示0~31的数据状态,一个数据用一个bit位表示，32~63放在第二个数据的比特位中，，，

//列：数据data = {0,1,2,3,5,6,9,8,4,7,22,11} ;最大值为22 则需要22个bit位，(根据最大数据确定bit位数，确定所需数据个数)
//容量：capacity = size>>5+1;  图数据位size_t 类型，
//bit位0~7表示数据0~7之间的状态，，，。空间开32个bit位(图数据位size_t 类型)
//表示方法是通过某种映射方法确定，类似哈希表
//数据所在的图中位置：idx = 数据>>5  (数据%32 获取数据映射的下标)
//数据所在图某位置中所占的bit位置置1：bmp->_data[idx] |= (1 << which%32)
//数据所在图某位置中所占的bit位置置0：bmp->_data[idx] &= ~(1 << which%32)

//位图键值对：数据，容量，数据个数
//初始化，开辟内存空间，大小--->数据元素个数>>5+1（元素个数/32+1，+1是为了处理结果为0的问题）
//初始化位图中的每个数据位为0

//统计有多少个1
//每个数据所对应的为1的bit位的个数(位数据表bitCount)
//位数据表char* bitCount = "\0\1\1\2\1\2\2\3\1\2\2\3\2\3\3\4" (四个bit位数据中出现为1的可能0~16)
//循环 i < capacity
//{
//j = 0;
//size_t value = bmp->_data[i];//取一个size_t 类型的数据
//循环(j < 4)//求一个整型数据所占1的个数
//{
//取一个字节 char ch = value;
//count += bitCount[ch&0x0F];//计算0~3bit位中1的个数
//ch = ch >> 4;
//count += bitCount[ch&0x0F];//计算4~7bit位中1的个数
//value = value >> 8;//取value的下一个字节
//j++;//字节计数+1
//}
//}