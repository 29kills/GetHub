#pragma once
#include<iostream>
#include<assert.h>
using namespace std;
//拷贝
//1、浅拷贝----共享一块空间
//注：浅拷贝需引用计数器，避免一块空间的多次析构问题
//2、写时拷贝--对空间写操作时，进行创建新空间考入原数据，进行新空间的数据写操作
class String
{
public:
	String(char* str = " ")//缺省值为空('\0')，是为了便于处理,不可为NULL
		//注：初始化列表是按声明的顺序初始话的，而不是此处的顺序
	{
		_capacity = strlen(str)+1;
		_size = _capacity;//字符个数统计'\0'
		_str = new char[_capacity];//+1是为了拷贝'\0'
		strcpy(_str,str);
	}
	/*
	//以前写法---自己开辟新空间后放入数据
	//s1(s)
	String(const String& s)//自定义拷贝构造，定义深拷贝---避免指向同一地址空间
	{
		this->_str = new char[strlen(s._str)+1];//深拷贝
		strcpy(_str,s._str);
	}

	//s1=s;
	String& operator=(const String& s)//赋值运算
	{
		if(this == &s)//不可s1 = s1
			return *this;

		delete []_str;//释放原有空间
		this->_str = new char[strlen(s._str)+1];//this隐含的，函数中可显示写，也可不写(注：形参不可显示写)
		strcpy(_str,s._str);
		return *this;
	}
	*/

	//现代写法---定义一个新的对象，交换对象中的内容
	//s1(s);
	String(const String& s)
		:_str(NULL)//初始_str为空---防止对野指针进行析构导致出错
	{
		String tmp(s._str);//创建一个临时对象，用于交换内容
		this->Swap(tmp);//交互内容(指向的地址)
		//此函数退出时会析构tmp，此时tmp已指向原来的_str空间，即对_str析构
	}
	//s1 = s;
	String& operator=(String s)
	{
		this->Swap(s);//巧用形参产生的临时拷贝（对象），交换临时变量的内容
		return *this;
	}

	void Swap(String& s)//用于交换对象的内容
	{
		swap(s._str,_str);
		swap(s._capacity,_capacity);
		swap(s._size,_size);
	}
	char*& operator+=(char* ch)//字符串链接
	{
		return this->operator+(ch);
	}
	char*& operator+(char* ch)
	{
		_capacity += strlen(ch);
		char* newstr = new char[_capacity];//开辟新空间
		strcpy(newstr,_str);//将原字符串放入到新空间
		strcat(newstr,ch);//字符串拼接
		delete []_str;//释放原有空间
		_str = newstr;//指向新空间
		return _str;
	}

	char& operator[](const size_t pos)//,返回引用则可读，可写
	{
		assert(pos < _size);//位置合法
		return _str[pos];
	}

	bool operator<(String& s)const //修饰this
	{
		size_t i = 0;
		for(i = 0;i < _size && i < s._size;i++)
		{
			if(_str[i] < s._str[i])
				return true;
			else if(_str[i] > s._str[i])
				return false;
		}
		if(_size < s._size)
			return true;
		else
			return false;
	}
	bool operator>(String s)const
	{
		return !(*this < s) ;
	}
	bool operator==(String s)const
	{
		size_t i = 0;
	    if(_size != s._size)
		    return false;
		for(i = 0;i < _size && i < s._size;i++)
		{
			if(_str[i] != s._str[i])
				return false;
		}
		return true;
	}
	void Reverse(const size_t newcapacity)//增容
	{
		//_str = (char*)realloc(_str,newcapacity);
		char* tmp = new char[newcapacity];
		memmove(tmp,_str,sizeof(char)*_size);
		delete []_str;
		_str = tmp;
		assert(_str);
	}
	//插入字符串
	void Push_Back(const char* str)
	{
		size_t sz = strlen(str);
		if(_size+sz > _capacity)
		{
			_capacity += sz;
		    Reverse(_capacity);
		}
		strcpy(_str+_size-1,str);//从_size-1拷贝位置(-1是由于下标从0开始)
		_size += sz;	
	}
	//插入字符---尾插
	void Push_Back(const char ch)
	{
		if(_size == _capacity)
		{
			_capacity = (_capacity > 0)? _capacity*2 : 2;
			Reverse(_capacity);
		}
		_str[_size-1] = ch;
		_str[_size] = '\0';
		_size++;
	}
	//删除
	void Pop_Back()
	{
	}
	//任意位置插入
	void Insert(const size_t pos,const char* str)
	{
		assert(pos < _size);
        size_t sz = strlen(str);
		if(_size+sz > _capacity)
		{
			_capacity += sz;
		    Reverse(_capacity);
		}
		int cur = _size-1;//使用int 类型，否则pos为0时会发生死循环
		while(cur >= (int)pos)//进行强制类型转换，否则不同类型比较会进行隐式类型转换，向范围大的转，即转成size_t类型，造成死循环
		{
			_str[cur+sz] = _str[cur];
			cur--;
		}	
		//_str[pos] += *str;
		memmove(_str+pos,str,sizeof(char)*sz);
		_size += sz;
	}
	void Insert(const size_t pos,const char ch)
	{
		assert(pos < _size);
		if(_size == _capacity)
		{
			_capacity = (_capacity > 0)? _capacity*2 : 2;
			Reverse(_capacity);
		}
		int cur = _size-1;//使用int 类型，否则pos为0时会发生死循环
		while(cur >= (int)pos)//需将pos转化成int类型比较，否则死循环
		{
			_str[cur+1] = _str[cur];
			cur--;
		}
		_str[pos] = ch;
		_size++;
	}
	//任意位置开始删除count个字符
	void Erase(const size_t pos,const size_t count)
	{
		if(_size-pos <= count)//删除pos位置后所有元素，添加'\0'即可
		{
			_str[pos] = '\0';
			_size = pos+1;//元素个数比下标大1，(下标从0开始)
		}
		else //部分删除，移动元素
		{
			int cur = pos;
			while(cur <= (int)_size-1)
			{
				_str[cur] = _str[cur+count];
				cur++;
			}
			_size -= count;
		}
	}
	//查找某字符
	int Find(char ch)
	{
		size_t i = 0;
		for(i = 0;i < _size;i++)
		{
			if(_str[i] == ch)
				return i;
		}
		return -1;
	}
	//查找某字符串
	int Find(char* str)
	{
		size_t subsz = strlen(str);
		size_t curindex = 0;//当前原串开始比较下标位置
		size_t nextindex = 0;//当前原串比较位置
		size_t subindex = 0;//当前比较串的比较位置

		while(curindex < _size-subsz)//原串未遍历完(剩余长度大于比较的长度)
		{
			nextindex = curindex;//比较位置 每次从 当前起始比较位置 开始
			while(_str[nextindex++] == str[subindex++])
			{
				if(subindex == subsz)//一直相同遍历完所有待比较字符串，则相同
					return curindex;
			}
			curindex++;//有一个字符不相同，原字符串比较位置后退，待比较字符串从起始位置重新开始比较
			subindex = 0;
		}
		//未从循环内退出，即不相同
		return -1;
	}

	const char* Getstr()
	{
		return _str;
	}
	size_t Size()
	{
		return _size;
	}
	size_t Capacity()
	{
		return _capacity;
	}
	~String()
	{
		if(_str)
		{
			delete []_str;
			_str = NULL;
		}
		_size = 0;
		_capacity = 0;
	}
private:
	char* _str;//char* 类型存储字符串(在文字常量区)，会导致字符串不可修改问题，所以须开辟空间存储在堆中才能修改
	size_t _size;//字符个数
	size_t _capacity;//容量
};

void String_test()
{
	String s("123");
	String s1;//无拷贝构造函数，系统调会自动生成(vs浅拷贝,Linux深拷贝),浅拷贝--直接赋值，对于指针会存在多次析构问题
	s1 = s;
	s1 += "4556";
	s1 = s1 + "789";
	cout << s1.Getstr() << endl;

	s1.Push_Back('a');
	cout << s1.Getstr() << endl;

	s1.Push_Back("def");
	cout << s1.Getstr() << endl;

	s1.Insert(2,"qwe");
	cout << s1.Getstr() << endl;

	s1.Insert(1,'s');
	cout << s1.Getstr() << endl;

	s1.Erase(0,2);
	cout << s1.Getstr() << endl;

	cout << s1.Find('2') << endl;
	cout << s1.Find('s') << endl;
	cout << s1.Find('f') << endl;

	cout << s1.Find("56789") << endl;
	cout << s1.Find("5678a") << endl;
	cout << s1.Find("ef") << endl;
	String s2("13");//使用构造函数
	String s3 = "34";//使用构造函数，进行了隐式转换
	cout << (s2 < s3) << endl;
	cout << (s2 == s3) << endl;
}
