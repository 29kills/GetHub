//�º���------����ɾ����
//�º�����ͨ����Ĵ������Ͳ�����������ʵ�ַº����������������ؿ�ֱ��ʹ�ú��������ã�
#include<iostream>
using namespace std;
template<class T>
struct Less//Less��
{
	bool operator()(const T& num1,const T& num2)//����������()���Ƚϴ�С
	{
		return num1 < num2;
	}
};

void Less_test()
{
	int num1 = 1;
	int num2 = 2;
	Less<int> less;
	cout << (num1 < num2) << endl;//�Ƚϴ�С
	cout << less(num1,num2) << endl;//�º����Ƚϴ�С(<)(�������е����������())
}


/*
template<class T>
void print(const T& t)
{
	cout << t << ' ';
}

template<class T>
class Multiple//�޷���ֵ�ķº���
{
public:
	Multiple(const T& v)//���캯��
		:_value(v)
	{}
	void operator()(T& elem) const//���������أ�ʵ�����ƺ����Ĺ���
	{
		elem *= _value;
	}
private:
	T _value;
};

template<class T>
class Sum
{
public:
	Sum()
		:_data(0)
	{}
	void operator()(T eum)
	{
		_data _= eum;
	}
	operator double()
	{
		return static_cast<double>(_data);
	}
private:
	T _data;
};

void xuh_test()
{
	vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);

	for_each(v.begin(),v.end(),print<int>);
	cout << endl;

	for_each(v.begin(),v.end(),Multiple<int>(9));
	for_each(v.begin(),v.end(),print<int>);
	cout << endl;

	double  num = for_each(v.begin(),v.end(),Sum<int>());
	cout << num << endl;
	cin.get();
}
*/

