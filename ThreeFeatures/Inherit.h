/*
继承：
1、作用：通过子类(派生类)继承父类(基类)的成员，共享不同的东西，实现各自不同的东西，达到代码复用的作用。
继承是类型之间的建模
子类是父类的的一部分，子类可继承父类中的非static成员。

3、继承方式：

访问修饰符：
public------公有(所有权限)
protected---保护(仅在类中可访问，子类继承父类的public成员后，为protected属性，子类可访问)
private-----私有(仅在类中可访问，类外及子类中不可见(继承但不可访问))

成员属性和继承方式最终取权限小的：
即：
成员属性                继承方式					子类继承后的属性
public          public--protected---private		public--protected---private	
protected		public--protected---private		protected--protected---private
private			public--protected---private	    private---private---private

子类和父类属于不同的作用域，可出现同名的成员，但会构成重定义(隐藏)，隐藏父类的成员，屏蔽对父类该成员的直接访问。若要调用父类的成员，则需加类名指定
注：在实际使用中最好不要定义同名的成员，防止出错。
public继承是一种is--a的关系，即子类是父类的一部分，子类可继承使用父类中所有的public成员。

1、赋值兼容规则：
可直接将子类对象赋给父类，即切片(将父类的部分切分给父类)，此方法不是一种类型转换。可使用引用的方法接收验证
父类对象不可赋给子类，但可通过强转将父类的指针或引用赋给子类，但使用时还是会出现错误

2、构造函数问题：
注：子类由复合构成，初始化子类中父类的数据成员时，必须显示的调用父类的构造函数，
且当父类无缺省的带参构造函数时，必须在子类构造函的初始化列表中调用父类的构造函数，进行初始化父类的成员。
因为：调用子类的构造函数时，会在子类的初始化列表处，调用父类的构造函数，
若此处不显示调用父类的构造函数，则编译器也会寻找父类中无参的构造函数，但父类中已定义带参的构造函数，所以会因找不到匹配的构造函数出错。
缺省的带参函数 = 无参函数+带参函数。

3、拷贝构造问题：
子类初始化父类时，可直接将子类对象传给父类，父类对象会进行切片，将属于父类的部分切分下来进行初始化父类。

4、赋值运算符重载：
注：由于父类的赋值运算符重载函数，与子类的该函数属于同名函数，所以两个函数构成了重定义，子类的该函数隐藏了父类的函数。从而会默认调用子类的赋值函数(就近原则)。
所以在调用父类的赋值函数时，必须加上类域指定调用父类的赋值函数，否则会默认调用子类的赋值函数，从而构成递归。

5、析构函数：
子类和父类的析构函数名虽然表面上看到的相同，但在底层上实际被处理成同名的函数，两者构成了重定义。
所以显示调用父类的析构函数时，必须加上类域指定为父类的，否则会默认的调用子类的析构函数。

调用析构函数时，会先调用子类析构函数，后自动调用父类析构函数。
因为：构造函数时，先调用的是父类构造函数，后构造子类部分，根据栈的先进后出特性，所以不可先析构父类。

protected/private继承是一种has-a关系，类外不可访问，
对于私有继承，子类内不可访问父类成员，
    保护继承，子类内可访问父类非私有成员。

列：
AA a;//父类对象		
BB b; //子类对象
a = b; //子类对象赋给父类
不是类型转化：
b = a; //父类对象赋给子类，错误
AA & aa = b //可引用，说明未发生类型转换

如何定义一个不可继承的类？
解1：将类的构造函数定义成私有的。
原因：1、类的私有成员，外部不可见，子类也不可见。
      2、子类是合成的，调用子类的构造函数时，会先调用父类的构造函数，但父类的构造函数不可见，所以无法实例化处对象。所以该类不可继承。
	注：若类外要实例化出父类对象，则还需在父类中定义一个static接口函数,类外通过类域指定调用。才能实例化出对象。由于static成员是不继承的，所以子类还是无法调用父类的构造。

解2：将类定义成抽象类，抽象类无法实例化出对象。

分类：
1、单继承：子类只有一个直接父类的继承
2、多继承：子类有多个直接父类的继承方式
3、菱形继承：单继承和多继承的复合。

     A
   /   \
  B     C
   \   /
     D
A类中的数据被B，C类继承，B,C再被D继承，从而导致D类中有多个A类中的数据成员，从而导致数据二义性和数据沉于问题。

虚继承：
方法：通过在继承方式修饰符前加virtual 关键字进行修饰，即为虚继承。
1、虚继承是为了解决菱形继承产生的二义性和数据沉于问题。
非虚继承时：同名的成员的数据成员相互独立,数值不同，使用时必须指定是哪个父类，否则会造成二义性问题，运行不通过，使用类与指定后可解决二义性问题，但无法处理数据沉于问题(类中有多个该数据成员)。
虚继承：对同名的数据成员操作，实际是对他们公共父类中的该数据成员操作，两父类的该数据成员值相同。从而可以解决数据二义性问题和数据沉于问题，类中有1个该数据成员

2、虚继承会产生虚基表，用于保存到父类的偏移量(地址)。
调用父类(B/C)中继承的成员时，先通过虚基表中的偏移量找到父类(A)，然后再找到该成员，而不是直接在父类(B/C)中找到该成员(A类成员)。

当继承的父，子类中存在同名的虚函数时，且参数相同，返回类型相同(协变除外)则就构成了多态。
注：子类可不用加virtual关键字，因为子类会继承父类的虚函数特性
    协变---返回类型不相同，但必须是类的指针或引用。


*/

/*
//无法继承的类
#include<iostream>
using namespace std;

class A
{
private: //将A的构造函数定义成私有的，使类不可被继承
	A()
	{
		cout << "构造A" << endl;
	}

public:
	static A* Get()
	{
		A();
	}

protected:
	int _a;
};

class B : public A
{
public:
	B() //不可调用A的构造函数，无法实例化出对象
	{
		cout << "构造B" << endl;
	}

	int add()
	{
		_a = 10;
		_b = 20;
		return _a+_b;
	}

protected:
	int _b;
};


void test4()
{

	B bb;
	A* a = A::Get(); //通过接口实例化对象
}
*/


/*

//继承
#include<iostream>
using namespace std;

class A
{
public:


	//A(const int& a)
	//	:_a(new int(a))
	//{}

	//缺省构造函数 = 无参构造+有参构造
	A(const int& a = 0)
	:_a(new int(a))
	{
		cout << "构造A" << endl;
	}

	~A()
	{
		cout <<"A"<< endl;
		delete _a;
	}

protected:
	int* _a;
};

class B : public A
{
public:
	
	//B(const int& a,const int& b)
	//	:A(a) //正确
	//	,_b(new int(b))
	//{}

	//B(const int& a,const int& b)
	//{
	//	A(a);//错误，在初始化列表时，会调用A类中的无参构造函数，但A类中无无参的构造函数，所以会报无默认的构造函数出错
	//	_b = new int(b);
	//}



	//A类有带缺省的构造函数时

	//B(const int& a,const int& b)
	//{
	//	A(a);//错误，在初始化列表时，会调用A类中的参构造函数，无参调用，实例化出a,此处再在调用父类构造，带参调用，又实例化出一个a，导致重定义问题
	//	_b = new int(b);
	//}
	
	//B(const int& a,const int& b)
	//{
	//	_a = new int(a); //错误，在初始化列表时，会调用A类中的参构造函数，无参调用，实例化处_a后，已对_a开辟空间，此处不可再开辟空间
	//	_b = new int(b);
	//	cout << "构造B" << endl;
	//}

	//B(const int& a,const int& b)//正确
	//{
	//	*_a = 1; //正确，在初始化列表时，会调用A类中的参构造函数，无参调用，实例化处_a后,此处进行初始化
	//	_b = new int(b);
	//	cout << "构造B" << endl;
	//}

	B(const int& a,const int& b)//正确
		:A(a)
		,_b(new int(b))
	{
		cout << "构造B" << endl;
	}

	//~B()//自动先析构子类，后析构父类
	//{
	//	~A();//错误，子类和父类析构函数，在底层上是同名的函数，即构成了重定义，子类隐藏了父类，导致递归出错。
	//	cout <<"B"<< endl;
	//	delete _b;
	//}

	//~B()//自动先析构子类，后析构父类
	//{
	//	A::~A();//错误，显示析构父类后，再析构子类，子类析构后会自动再析构父类，导致出错
	//	cout <<"B"<< endl;
	//	delete _b;
	//}

	~B()//自动先析构子类，后析构父类---正确
	{
		cout <<"B"<< endl;
		delete _b;
	}

protected:
	int* _b;
};

void test3()
{
	B bb(0,0);
}

*/

/*

#include<iostream>
using namespace std;

class A
{
public:
	A()
	{}

protected:
	void print()
	{
		cout << "输出" <<endl;
	}

private:
	int _a;
};

class B : public A
{
public:
	B()
	{}

	void change()
	{
		//this->_a  = 1;//错误父类私用成员，子类内不可见(不可访问)
		print();//代码段不属于某一个类，不使用this指针调用，父类的保护成员，子类内部可访问
	}

private:
	int _b;
};

void test()
{
	A a;
	B b;
	
	//b._a = 1;错误父类私用成员不可见(不可访问)
	//b.print();//错误保护成员外部不可见(不可访问)

	a = b;
	A & aa = b;//支持，说明未发生隐式类型转换
	int i = 0;
	size_t d = 0;
	//int & t = d;//引用不支持，发生隐式类型转换
	//b = a;//父类对象不可赋给子类
}

*/

/*

//菱形继承
#include<iostream>
using namespace std;

class A
{
public:
	A()
	{}

	void Funa()
	{
		cout << "Funa()" << endl;
	}

public:
	int _a;
};

class B : public A //公有继承A
{
public:
	B()
	{}

	void Funb()
	{
		cout << "Funb()" << endl;
	}

public:
	int _b;
};


class C : public A //单继承
{
public:
	C()
	{}

	void Func()
	{
		cout << "Func()" << endl;
	}

public:
	int _c;
};

class D : public B,public C //多继承
{
public:
	D()
	{}

	void Fund()
	{
		cout << "Fund()" << endl;
	}

public:
	int _d;
};

void test2()
{
	A aa;
	B bb;
	C cc;
	D dd;

	cout << "类的大小" << endl; //函数(代码段)和静态成员(静态区)不属于某一个对象，是所有对象共有的，所以不算做对象的大小。
	cout << "aa = " << sizeof(aa) << endl; //4
	cout << "bb = " << sizeof(bb) << endl; //4+4
	cout << "cc = " << sizeof(cc) << endl; //4+4
	cout << "dd = " << sizeof(dd) << endl; //8+8+4

	aa._a = 0;
	//dd._a = 10;//错误，D类继承有多个数据_a,存在二义性问题
	//dd.A::_a  = 1; //错误，A不是D的直接父类，所以A不算是D的父类，不可直接访问A类成员
	dd.B::_a = 1; //通过类域，指定访问B类中的_a成员，可解决二义性问题，但D类中有多个_a成员，存在数据冗余问题。
	dd.C::_a = 2; //D类中的两个_a成员数据不同
	dd._b = 3;
	dd._c = 4;
	dd._d = 5;
	cout << dd.B::_a << endl;
	cout << dd.C::_a << endl;
	cout << aa._a << endl;
}

*/


/*
//菱形虚继承

#include<iostream>
using namespace std;

class A
{
public:
	A()
	{}

	void Funa()
	{
		cout << "Funa()" << endl;
	}

public:
	int _a;
};

class B : virtual public A //公有继承A
{
public:
	B()
	{}

	void Funb()
	{
		cout << "Funb()" << endl;
	}

public:
	int _b;
};

//注意virtual关键字添加的位置，添加在继承公共父类处
class C : virtual public A //单继承
{
public:
	C()
	{}

	void Func()
	{
		cout << "Func()" << endl;
	}

public:
	int _c;
};

class D : public B,public C //多继承
{
public:
	D()
	{}

	void Fund()
	{
		cout << "Fund()" << endl;
	}

public:
	int _d;
};

void test2()
{
	A aa;
	B bb;
	C cc;
	D dd;
	//函数(代码段)和静态成员(静态区)不属于某一个对象，是所有对象共有的，所以不算做对象的大小。
	cout << "类的大小" << endl; 
	cout << "aa = " << sizeof(aa) << endl; //4
	cout << "bb = " << sizeof(bb) << endl; //4+4+4(虚基表)
	cout << "cc = " << sizeof(cc) << endl; //4+4+4(虚基表)
	cout << "dd = " << sizeof(dd) << endl; //12+12+4-4(A类大小)，
	
	dd.B::_a = 0; //通过类域，指定访问B类中的_a成员，
	dd.C::_a = 1; //通过类域，指定访问C类中的_a成员，
	dd._a = 2;   //但实际都是直接对同一个父类A操作，结果值相同
	dd._b = 3;
	dd._c = 4;
	dd._d = 5;

	//注：B，C不直接继承A类，而是通过虚基表表找到A类，所以B,C共用的是一个A类(原A类)，而不是各种独有。所以减去多统计的A类大小
	dd._a = 10;//正确，D类继承父类B，C,两个父类根据虚基表找到他们的公共父类A,他们都是直接对同一个父类A操作。所以D类实际只有在一个_a成员，从而解决二义性和数据冗余问题
	//dd.A::_a  = 1; //错误，A不是D的直接父类，所以A不算是D的父类，不可直接访问A类成员
	dd.B::_a = 1; //通过类域，指定访问B类中的_a成员，
	dd.C::_a = 2; //通过类域，指定访问C类中的_a成员，但实际都是直接对同一个父类A操作，结果值相同
	dd._b = 3;
	dd._c = 4;
	dd._d = 5;
	//对公共继承的父类数据操作，即直接对原父类中的数据操作，数据相同
	cout << dd.B::_a << endl;
	cout << dd.C::_a << endl;
	cout << aa._a << endl;//对aa对象操作，属于不同对象，所以数值不同
}

*/