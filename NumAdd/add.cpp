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
		sum+=num;//����
		while(cin.peek()==' ')//���Կո����޴�ѭ��������������ǿո�ʱ���س������м���
		{
			cin.get();//��ȡһ���ַ�
		}
		if (cin.peek()=='\n')//��ȡһ���ַ�Ϊ�س�ʱ
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
		while(cin.peek()==' ')//���Կո����޴�ѭ��������������ǿո�ʱ���س������м���
		{
			cin.get();//��ȡһ���ַ�
		}
		if (cin.peek()=='\n')//��ȡһ���ַ�Ϊ�س�ʱ
		{
			break;
		}
		i++;
	}
   return snum[i];//����ÿ������һ����
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
	for(;i>0;i--)//��������
	{
	 a[i]=puts();//����ÿ�����ݵ����һ������֮��
	sum+=a[i];
    }
	return sum;
}