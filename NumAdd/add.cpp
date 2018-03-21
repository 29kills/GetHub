/*
#include<iostream>
#include<stdlib.h>
using namespace std;
int puts();
void outs(int add);
void main()
{
	int add=0;
	add=puts();
	outs(add);
	system("pause");
}
int puts()
{
	int num=0;
	int sum=0;
	while(cin>>num)
	{
		sum+=num;//计算
		while(cin.peek()==' ')//忽略空格，若无次循环，则最后输入是空格时按回车不进行计算
		{
			cin.get();//提取一个字符
		}
		if (cin.peek()=='\n')//获取一个字符为回车时
		{
			break;
		}
	}
	return sum;
}
void outs(int add)
{
	cout<<"add="<<add<<endl;
}
*/




#include<iostream>
#include<stdlib.h>
#define N 20
using namespace std;
int  puts();
void outs(int add);
int adds();
void main()
{
	int add=0;
	add=adds();
	outs(add);
	system("pause");
}
int puts()
{
	int i=0;
	int snum[N];
	while(cin>>snum[i])
	{
		while(cin.peek()==' ')//忽略空格，若无次循环，则最后输入是空格时按回车不进行计算
		{
			cin.get();//提取一个字符
		}
		if (cin.peek()=='\n')//获取一个字符为回车时
		{
			break;
		}
		i++;
	}
   return snum[i];//传递每组的最后一个数
}
void outs(int add)
{
	cout<<"add="<<add<<endl;
}
int adds()
{
	int i=5;
	int a[20];
	int sum=0;
	for(;i>0;i--)//五组数据
	{
	 a[i]=puts();//计算每组数据的最后一个数据之和
	sum+=a[i];
    }
	return sum;
}