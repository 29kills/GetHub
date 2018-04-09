#pragma once
#include<iostream>
#include<string>
#include<assert.h>

using namespace std;

class String
{
public:
	String(char* str = "\0")
		:_str(new char[strlen(str)+1])
		,_size(strlen(str))
		,_capacity(_size)
		,_count(new int(1))//计数器初始化为1
	{
		strcpy(_str,str);
	}

	String(const String& s)
		:_str(s._str)
		,_size(s._size)
		,_capacity(s._capacity)//指向同一空间，浅拷贝
		,_count(s._count)//指向同一个内存空间的，计数器也为同一个
	{
		//s(s)
		if(this != &s)//不为同一个对象
		(*_count)++;
	}

	String& operator=(String& s)
	{
		if(*this != s)//调用运算符重载！=
		{
			if(--(*_count) == 0)//对象计数器为1时，释放旧空间，指向新空间
			{
				delete []_str;
			}
			//更新数据
			_str = s._str;
			_size  = s._size;
			_capacity = s._capacity;//浅拷贝
			_count = s._count;//为同一计数器

			(*_count)++;//计数器+1
		}
		return *this;
	}
	bool operator!=(const String& s)
	{
		return this != &s;
	}
	bool operator==(const String& s)
	{
		return this == &s;
	}
	bool operator<=(const String& s)
	{
		return strcmp(_str,s._str) == -1 || strcmp(_str,s._str) == 0;
	}
	bool operator<(const String& s)
	{
		return strcmp(_str,s._str) == -1;
	}

	bool operator>=(const String& s)
	{
		return !(*this < s);
	}
	bool operator>(const String& s)
	{
		return !(*this <= s);
	}
	String& operator+(const char* str)
	{
		String tmp(this->_str);
		tmp.PushBack(str);
		return tmp;
	}

	String& operator=(const char* str)
	{
		PushBack(str);
		return *this;
	}
	String& operator+=(const char* str)
	{
		PushBack(str);//尾插字符串
		return *this;
	}
	char* operator<<(const String& str)
	{
		return Show();
	}
	char& operator[](size_t n)//传引用，则可修改
	{
		assert(n <= _size);
		return _str[n-1];
	}
	const char operator[](const size_t n)const//不可修改
	{
		assert(n <= _size);
		return _str[n-1];
	}

	char* Show()
	{
		return _str;
	}

	void PushBack(const char* str)//尾插字符串
	{
		int len = strlen(str);
		//_size = _size+len;//不统计'\0',容量会多开一个空间存'\0‘
		if(_size+len > _capacity)
		{
			Expend(_size+len);
		}
		strcpy(_str+_size,str);
		_size += len;
	}
	void PushBack(const char ch)//尾插字符
	{
		if(_size+1 > _capacity)
		{
			Expend(_size*2);//开二倍空间
		}
		_str[_size++] = ch;
		_str[_size] = '\0';
	}
	void Insert(const size_t pos,const char* str)
	{
		int len = 0;
		int i = 0;
		assert(pos <= _size+1);

		len = strlen(str);
		_size += len;
		if(_size > _capacity)
			Expend(_size);
		for( i = _size; i >= (int)pos; i--)
			_str[i+len] = _str[i];
		strncpy(_str+pos,str,sizeof(char)*len);	//不拷'\0'
	}

	void Insert(const size_t pos,const char ch)
	{
		int i = 0;
		assert(pos <= _size+1);
		_size += 1;
		if(_size > _capacity)
			Expend(_size*2);
		for( i = _size; i >= (int)pos; i--)
			_str[i+1] = _str[i];
		_str[pos] = ch;
	}

	void Erase(const size_t pos,const size_t len)
	{
		int i = 0;
		assert(pos <= _size);
		strcpy(_str+pos,_str+pos+len-1);
	}

	void Expend(int size)//扩容
	{
		_capacity = size;//更新容量
		char* tmp = (char*)malloc(sizeof(char)*_capacity+1);
		assert(tmp);
		strcpy(tmp,_str);//拷贝数据
		free(_str);//释放旧空间
		_str = tmp;//指向新空间
		
	}

	void Replace(char ch1, char ch2)//字符替换
	{
		int i = 0;
		for(i = 0; i < _size; i++)
		{
			if(_str[i] == ch1)
				_str[i] = ch2;
		}
	}
	//123   ab
	void Replace(const char* sub1, const char* sub2) //字符串替换
	{
		int pos = (int)Find(sub1); // ? 
		assert(pos >= 0 && pos <= _size);
		//容量处理
		int len = strlen(sub2);
		int len1 = strlen(sub1);
		int h = len - len1;//判断替换的字符串谁长
		if(_size+len < _capacity)
			Expend(_size+len);
		//搬移数据
		int i = 0;
		if( h > 0)//扩长
		{
			for(i = _size; i >= pos+len1; i--)//向后移
			{
				_str[i+h] = _str[i];
			}
		}
		else if(h < 0)//缩短
		{
			for(i = pos+len1; i <= _size; i++)//向前移
			{
				_str[i+h] = _str[i];
			}
		}
		//相同直接复制
		//放数据
		strncpy(_str+pos,sub2,sizeof(char)*len);
		_size += len;
	}

	size_t Find(char ch)//未找到返回-1(最大值)
	{
		int i = 0;
		for(i = 0; i < _size; i++)
		{
			if(_str[i] == ch)
				return i;
		}
		return -1;
	}

	size_t Find(const char* str) // ? 
	{
		int i =0 ;
		char* pstr = _str;
		const char* ptmp = str;
		for(i = 0; i < _size; i++)
		{
			pstr = &_str[i];
			while(*pstr != '\0' && *ptmp != '\0')
			{
				if(*pstr == *ptmp)
				{
					pstr++;ptmp++;
				}
				else
				{
					ptmp = str;
					break;
				}
			}
			if(*ptmp == '\0')
				return i;
		}
		return -1;
	}

private:
	char* _str;
	int _size;
	int _capacity;
	int* _count;//引用计数器
};

void StringTest()
{
	String str1("123");
	cout << str1.Show() << endl;
	String str2;
	str2 = "1234";
	cout << str2.Show() << endl;
	str1+"456";
	cout << (str1 > str2) << endl;
	//cout << str1 << endl;
	//cout << str1+"741"<< endl;//如何重载<<?
	str2 += "789";
	cout << str2.Show() << endl;

	str1[1]  = '8';
	cout << str1.Show() << endl;
	cout << str1[3] << endl;

	cout << str1.Show() << endl;
	str1.Replace('2','8');
	cout << str1.Show() << endl;

	cout << str2.Show() << endl;
	cout << str2.Find("12345") << endl;
	
	cout << str2.Show() << endl;
	str2.Replace("123","abc");
	cout << str2.Show();

	cout << str2.Show() << endl;
	str2.Replace("7","abcefg");
	cout << str2.Show();

	system("pause");
}