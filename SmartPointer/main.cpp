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
	//Smart_test();//�򵥵�����ָ��
    //Aptr_test();//Ȩ��ת��
	//Scptr_test();//������
	//Shptr_test();//����
	//Less_test();//�º���

	Shptr_list_test();//˫���������--ѭ����������
	Weak_Ptr_test();//ѭ����������---��ָ��
	//xuh_test();
	system("pause");
	return 0;
}