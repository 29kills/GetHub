//深浅拷贝----类型萃取实现（通过不同的类(指定)选择（模板确定），选择不同的拷贝方法）
#pragma once
#include<iostream>
#include<string>
using namespace std;

struct __FalseType{};//类
struct __TrueType{};

template<class T>
struct __TypeTraits //拷贝string
{
	//POD：平凡类型---基本类型
	//在C++中与C兼容的类型，可按照C的处理方式
	typedef __FalseType IsPODType;//内嵌重定义
	//typedef __TrueType IsPODType;
};

template<>//特化
struct __TypeTraits<string>//拷贝int ,char ..
{
	typedef __TrueType IsPODType;
	//typedef __FalseType IsPODType;//内嵌重定义
};

//特化自定义Data类
/*
class Date;//前置声明
template<>
struct __TypeTraits<Data> //拷贝int ,char ...
{
	typedef __TrueType IsPODType;

};
*/

template<class T>
T*__TypeCopy(T* dst,const T* src,const size_t count)//确定调用那个复制
{
	return __TypeCopy(dst,src,count,__TypeTraits<T>::IsPODType());//重载
}

template<class T>
T* __TypeCopy(T* dst,const T* src,const size_t count,__TrueType)//拷贝int或char...
{
	return (T*)memcpy(dst,src,count*sizeof(T));//效率高(浅拷贝)
}

template<class T>
T* __TypeCopy(T* dst,const T* src,const size_t count,__FalseType)//拷贝string
{
	for(size_t i=0;i<count;++i)//深拷贝
	{
		dst[i]=src[i];
	}
	return dst;
}

void test_copy(void)
{
	int a1[]={1,2,3};
	int a2[]={4,5,6};
    __TypeCopy(a1,a2,3);
	cout << a1 <<endl;

	string s1[]={"123"};
	string s2[]={"456"};
	__TypeCopy(s1,s2,1);//个数1
	cout << s1 << endl;
}
