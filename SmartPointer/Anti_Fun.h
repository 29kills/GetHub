//仿函数------定制删除器
//仿函数是通过类的创建，和操作符的重载实现仿函数（操作符的重载可直接使用函数名调用）
#include<iostream>
using namespace std;
template<class T>
struct Less//Less类
{
	bool operator()(const T& num1,const T& num2)//操作符重载()，比较大小
	{
		return num1 < num2;
	}
};

void Less_test()
{
	int num1 = 1;
	int num2 = 2;
	Less<int> less;
	cout << (num1 < num2) << endl;//比较大小
	cout << less(num1,num2) << endl;//仿函数比较大小(<)(调用类中的重载运算符())
}


/*
template<class T>
void print(const T& t)
{
	cout << t << ' ';
}

template<class T>
class Multiple//无返回值的仿函数
{
public:
	Multiple(const T& v)//构造函数
		:_value(v)
	{}
	void operator()(T& elem) const//操作符重载，实现类似函数的功能
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

