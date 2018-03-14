#pragma once
#include<iostream>
#include"Aptr.h"
#include"Scoped_Ptr.h "
#include"Shared_Ptr.h"
#include"Weak_Ptr.h"
#include"Smart.h"
#include"Anti_Fun.h"

int main()
{
	//Smart_test();//简单的智能指针
    //Aptr_test();//权限转移
	//Scptr_test();//防拷贝
	//Shptr_test();//计数
	//Less_test();//仿函数

	Shptr_list_test();//双向链表测试--循环引用问题
	Weak_Ptr_test();//循环引用问题---弱指针
	//xuh_test();
	system("pause");
	return 0;
}