#include<iostream>
#include<string>
using namespace std;

void Insert(size_t pos,int x)//C中的隐式转化
{
	for(int i=x;i>=pos;i--)//死循环，会隐式将int转化成size_t,所以死循环
	{
		cout << i << endl;
	}
}

void test1()//C++中的静态转换
{
	int i=48;
	//C++中的静态转换，相关类型转换，类似于C中的隐式转换，
	char ch=static_cast<char>(i);//static_char 是一个类 相当于一个关键字
	cout << i  << endl ;
	cout << ch << endl;

	//不相关类型转换，类似C中的强制类型转化,(函数可不写参数，直接使用函数名来使用函数地址，但可能存在跨平台问题)
	int* p=&i;
	int j=reinterpret_cast<int>(p);//int* --->int ;
	cout << p << endl;
	cout << j << endl;

	//const修饰的类型转换（const修饰的变量其实可以改变，但容易出现错误（寄存器值与内存值不相同问题））
	const int a = 2;//const 修饰的变量，编译器会进行优化放在寄存器中，内存中也存放的有，（寄存器地址不可取到）
	//volatile const int a = 2;//const 修饰的变量，volatile 内存可见，直接将a值放在内存中，不放在寄存器中
	int* p2 = const_cast<int*>(&a);
	*p2 = 3; //a的内存中的值被修改，寄存器中的值未修改（容易导致错误）
	cout << a << endl;//a取的是寄存器中值，依然是2
	cout << *p2 << endl; //*p2是内存中的值是3
}

class A
{
public :
	virtual void fun()//类中必须有虚函数（有虚表）
	{}
public :
	int _a;
};

class B : public A
{
public :
	int _b;
};

void dynamic_test(A *pa)
{
    B* pb;
	pb = dynamic_cast<B*>(pa);//安全转换,不可以转换返回0，否则转换
	if(pb)
		cout << "pa指向子类,安全,可转换" << endl;
	else
		cout << "pa指向父类，不安全，不可转换" <<endl; 
}

void AB_test()
{
	A aa;//父类对象
	B bb;//子类对象
	A* pa;//父类指针
	B* pb;//子类指针

	//pb = &aa;//子类指针不可指向父类对象，即不能将父类的对象给子类指针
	pb = &bb;//类的指针只能指向自己的对象，或指向子类的对象，不能指向父类的对象

	pa = &aa; //父类指针指向父类对象
	pb = (B*)pa;//将父类指针pa强转成子类指针（不安全转换）
	//pb->_b=10;//由于，pa指向父类对象(&aa),不包含_b，所以强转后访问_b越界
	dynamic_test(pa);

	pa = &bb;//父类指针指向子类对象
	pb = (B*)pa;//将父类指针pa强转成子类指针 （不安全转换）
	pb->_b = 10;//pa指向子类对象(&bb),包含_b，所以强转后访问_b不会越界
	dynamic_test(pa);
	cout << pb->_b << endl;
}

class C
{
public :
	//explicit C(int x)//单参数构造，加关键字explicit不准许进行隐式类型转换
	C(int x)//单参数构造，会进行隐式类型转换
		:_c(x)//初始化参数列表
	{
		cout << "C(int x)" << endl;
	}
	C(const C& x)//拷贝构造
	{
		cout << "C(const C& x)" << endl;
	}

	C& operator = (const C& c)//赋值重载
	{
		_c=c._c;
		return *this;
	}
public:
	int _c;
};

void string_test()
{
	string s1("1111");//直接构造一个s1对象
	string s2="1111";//隐式类型转换 + (构造 + 拷贝构造 + 优化)==构造

	char* ch1="1111";//内容保存在文字常量区，栈中保存所指向的常量区地址（ch1）
	char ch2[]="1111";//在栈中开辟一块内存空间，存放内容

	cout << sizeof(s1) <<endl ;//一个string类型为28/32个字节
	cout << sizeof(s2) << endl ;
	
	cout << sizeof(ch1) << endl;//地址占4个字节
	cout << sizeof(ch2) << endl;//数组大小，即字符串的长度（有隐含的'\0'5）

	//单参数构造函数的优化
	C c1(4);//构造对象，直接调用构造函数
	C c2=5;//创建对象，进行优化后调用构造函数（隐式类型转换）
	cout << c1._c << endl;
	cout << c2._c << endl;

	c2=c1;//赋值运算
	cout << c2._c << endl;
}