
#include<iostream>
#include<list>
#include<vector>
#include<algorithm>//�㷨
#include<Windows.h>
using namespace std;
//��������ʹ�÷���
//list<int>::iterator it = L.begin();//��ͨ������---��д
//list<int>::const_iterator ct = L.begin();//const������---��
//vector<int>::reverse_iterator vt = V.rbegin();//���������---��д

//template<class T>
void print_list(const list<int>& d)
{
	list<int>::const_iterator ct = d.begin();
	while(ct != d.end())
	{
		cout << *ct << ' ' ;
		ct++;
	}
}

void List_test()
{
	list<int> L;
	L.push_back(1);//push_back()δ�Ż��������һ�ι���Ϳ�������
	L.push_back(2);//emplace_back��C++11��ģ��������Ż�����ʱֻ����һ�ι��죬����Ч
	L.push_back(3);
	L.push_back(4);
	L.push_back(5);
	L.push_back(6);

	cout << "\n������:" ;
	greater<int> great_num;//����
	L.sort(great_num);
	print_list(L);
	cout << endl;

	cout << "\n������:" ;
	less<int> less_num;//����
	L.sort(less_num);//������(˳�����sort()����)
	print_list(L);

	//ʹ�õ����������ڲ�Ԫ��
	//��ͷ��β��������Ԫ��
	list<int>::iterator it = L.begin();//��ͨ�����������ݿ��޸�
	while(it != L.end())
	{
		if(*it % 2)//�������
		cout << ++*it << endl;
		it++;
	}
	cout << endl;
    list<int>::const_iterator ct = L.begin();//const������,���ݲ����޸�
	while(ct != L.end())
	{
		cout << *ct << endl;
		ct++;
	}
	cout << endl; 
}

void Vector_test()
{
	size_t i = 0;
	vector<int> V;
	V.push_back(1);
	V.push_back(2);
	V.push_back(3);
	V.push_back(4);
	V.push_back(5);
	V.push_back(6);

	//ʹ�õ������������
	//ʹ�õ����������ɶ�������д���޸ģ�
	vector<int>::reverse_iterator vt = V.rbegin();//���������
	while(vt != V.rend())
	{
		if(!(*vt %2))//�������
			cout << *vt << endl;
		vt++;
	}
	//����ʹ��ѭ����ʹ�õ�����
	for(i = 0;i <V.size();i++)//����
	{
		cout << V[i];
	}
	cout << endl;

	{
		size_t N = 1000000;
		size_t start = GetTickCount();//��ȡʱ��
		V.reserve(N);//����������СN(�������ʱ������ݣ�Ч�ʵ�����)��puch_backʹ��
		//V.resize(N);//�ȿ���N���ռ䣬�󿽱���ȥ��Ч�ʵͣ��ʺϺ�[]ʹ��
		for(i = 0; i< N;i++)
		{
			V.push_back(i);
			//V[i] = i;
		}
		size_t end = GetTickCount();//��ȡʱ��
		cout << end - start <<endl;
	}
}

void other_test()
{
	list<int> L1;
	L1.push_back(1);
	L1.push_back(2);
	L1.push_back(3);
	list<int>::iterator pos = find(L1.begin(),L1.end(),3);//��beging--end��3
	if(pos != L1.end())//�ж��Ƿ��ҵ�
	L1.insert(pos,(*pos)*10);//����
	print_list(L1);

	list<int>::iterator p = find(L1.begin(),L1.end(),2);//��beging--end��3
	if(p != L1.end())//�ж��Ƿ��ҵ�
	L1.erase(p);//ɾ��
	print_list(L1);

	cout << endl;
	list<int>::iterator t = L1.begin();
	while(t != L1.end())
	{
		if(*t % 2)//ɾ������
			t = L1.erase(t);//ɾ��,ɾ���󷵻���һ����ַ
		else//δɾ��ָ����һ��,��ֹ������ʧЧ
		t++;//������ʧЧ���ȼ���Ұָ��
	}

	print_list(L1);

}