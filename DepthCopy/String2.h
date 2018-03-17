#include<iostream>
using namespace std;

namespace Cow
{
	class String
	{
	public:
		String(const char* str = "")
			:_str(new char[strlen(str)+1])
			,_size(new int(1))
		{
			_sz = strlen(str);//字符个数不统计'\0'
			_capacity = _sz+1;//容量包含'\0'；
			strcpy(_str,str);
		}
		//s1(s)
		String(const String& s)
			:_str(s._str)
			,_size(s._size)
			,_sz(s._sz)
			,_capacity(s._capacity)
		{
			if(this != &s)
			++(*_size);//注意要加括号，否则是地址++
		}
		//s1=s
		String& operator=(const String& s)
		{
			//原对象的计数器为一时，释放旧空间，指向新空间(对象)
			//原对象的计数器不为一时，计数器-1，指向新空间
			if(_str != s._str)
			{
				if(--(*_size) == 0)
				{
					delete []_str;
					delete _size;
					_sz = 0;
					_capacity = 0;
				}
				_str = s._str;
				_size = s._size;
				_sz = s._sz;
				_capacity = s._capacity;
				(*_size)++;
			}
			return *this;
		}
		//对于写有关的操作(修改内容)，都需先处理对象的地址空间问题，即先调用CopyWrite();
		//注：对于既是读又可写的函数，以写处理，如[]等
		char operator[](const size_t n)const//只读
		{
			return _str[n];
		}
		char& operator[](const size_t n)//可读可写
		{
		     CopyWrite();
			return _str[n];
		}
		void Push_Back(char ch)
		{
			//1、先处理对象的空间地址问题，和计数器问题
		     CopyWrite();
			 //2、处理空间是否充足问题

			 //3、数据修改问题

		}
		//计数大于1，需开辟新空间，指向新地址，产生对应新计数器，原计数器-1
		//写前处理空间和计数器问题
		void CopyWrite()
		{
			if(*_size >1)
			{
				char* tmp = new char[_capacity];//开辟与原来一样的空间
				strcpy(tmp,_str);
				(*_size)--;//原对象计数器-1
				//指向新地址
				_str = tmp;
				_size = new int(1);//产生新计数器
			}
		}
		~String()
		{
			if((*_size)-- == 1)
			{
				cout << "~String()" << endl;
				delete []_str;
				delete _size;
			}
		}
	private:
		char* _str;
		int* _size;//引用计数，同一个空间应为同一个引用计数，所以使用指针,
		//可不创建引用计数，将此计数放在_str前4个字节处，使用计数器时，_str减4个字节就可取到。此方法可减少内存碎片问题
		size_t _sz;//字符个数
		size_t _capacity;//容量
	};
}

void test()
{
	Cow::String s("123");
	Cow::String s1(s);
	Cow::String s2(s1);
	Cow::String s3("456");
	Cow::String s4;
	s = s3;
	s4 = s3;

	cout << s[2] << endl;
	s[2] = '9';
	cout << s[2] << endl;
	//s1(s);
}