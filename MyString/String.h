#pragma once

#include<iostream>
#include<malloc.h>
#include<string.h>
#include<assert.h>
#include<algorithm>
using namespace std;

/*
class String
{
public:
	String(char* str = "\0")
		:_str(new char[strlen(str)+1])
		,_size(strlen(str))
		,_capacity(_size)
		,_count(new int(1))//��������ʼ��Ϊ1
	{
		strcpy(_str,str);
	}

	String(const String& s)
		:_str(s._str)
		,_size(s._size)
		,_capacity(s._capacity)//ָ��ͬһ�ռ䣬ǳ����
		,_count(s._count)//ָ��ͬһ���ڴ�ռ�ģ�������ҲΪͬһ��
	{
		//s(s)
		if(this != &s)//��Ϊͬһ������
		(*_count)++;
	}

	String& operator=(String& s)
	{
		if(*this != s)//������������أ�=
		{
			if(--(*_count) == 0)//���������Ϊ1ʱ���ͷžɿռ䣬ָ���¿ռ�
			{
				delete []_str;
			}
			//��������
			_str = s._str;
			_size  = s._size;
			_capacity = s._capacity;//ǳ����
			_count = s._count;//Ϊͬһ������

			(*_count)++;//������+1
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
		PushBack(str);//β���ַ���
		return *this;
	}
	char* operator<<(const String& str)
	{
		return Show();
	}
	char& operator[](size_t n)//�����ã�����޸�
	{
		assert(n <= _size);
		return _str[n-1];
	}
	const char operator[](const size_t n)const//�����޸�
	{
		assert(n <= _size);
		return _str[n-1];
	}

	char* Show()
	{
		return _str;
	}

	void PushBack(const char* str)//β���ַ���
	{
		int len = strlen(str);
		//_size = _size+len;//��ͳ��'\0',������࿪һ���ռ��'\0��
		if(_size+len > _capacity)
		{
			Expend(_size+len);
		}
		strcpy(_str+_size,str);
		_size += len;
	}
	void PushBack(const char ch)//β���ַ�
	{
		if(_size+1 > _capacity)
		{
			Expend(_size*2);//�������ռ�
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
		strncpy(_str+pos,str,sizeof(char)*len);	//����'\0'
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

	void Expend(int size)//����
	{
		_capacity = size;//��������
		char* tmp = (char*)malloc(sizeof(char)*_capacity+1);
		assert(tmp);
		strcpy(tmp,_str);//��������
		free(_str);//�ͷžɿռ�
		_str = tmp;//ָ���¿ռ�
		
	}

	void Replace(char ch1, char ch2)//�ַ��滻
	{
		int i = 0;
		for(i = 0; i < _size; i++)
		{
			if(_str[i] == ch1)
				_str[i] = ch2;
		}
	}
	//123   ab
	void Replace(const char* sub1, const char* sub2) //�ַ����滻
	{
		int pos = (int)Find(sub1); // ? 
		assert(pos >= 0 && pos <= _size);
		//��������
		int len = strlen(sub2);
		int len1 = strlen(sub1);
		int h = len - len1;//�ж��滻���ַ���˭��
		if(_size+len < _capacity)
			Expend(_size+len);
		//��������
		int i = 0;
		if( h > 0)//����
		{
			for(i = _size; i >= pos+len1; i--)//�����
			{
				_str[i+h] = _str[i];
			}
		}
		else if(h < 0)//����
		{
			for(i = pos+len1; i <= _size; i++)//��ǰ��
			{
				_str[i+h] = _str[i];
			}
		}
		//��ֱͬ�Ӹ���
		//������
		strncpy(_str+pos,sub2,sizeof(char)*len);
		_size += len;
	}

	size_t Find(char ch)//δ�ҵ�����-1(���ֵ)
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
	int* _count;//���ü�����
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
	//cout << str1+"741"<< endl;//�������<<?
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

*/

//���---vs 12+16���ֽ�
class Str
{
	public:
		Str(const char* str = "")
			:_str(new char[strlen(str)+1])
			,_size(strlen(str))
			,_capacity(_size)
			{
				strcpy(_str,str);
			}

		Str(const Str& s)
			:_str(new char[s._capacity+1])
			 ,_size(s._size)
			 ,_capacity(s._capacity)
		{
			strcpy(_str,s._str);
		}

		Str& operator=(const Str& s)
		{
			if(_str != s._str)
			{
				Str tmp(s._str);

				swap(_str,tmp._str);
				swap(_size,tmp._size);
				swap(_capacity,tmp._capacity);
			//    swap(tmp,*this);//����ֱ��ʹ��swap��������
			}
			return *this;
		}
/*
		//�޷�����s = s�Ĳ����������һ��
		Str& operator=(Str s)//��ʹ����,ֱ��ʹ��ʵ�����Ķ������
		{	
				swap(_str,s._str);
				swap(_size,s._size);
				swap(_capacity,s._capacity);
				return *this;
		}
*/
		~Str()
		{
			if(_str)
			{
				delete []_str;
				_size = 0;
				_capacity = 0;
			}
		}
		char& operator[](const size_t n)
		{
			return _str[n];
		}
		
		Str& operator=(const char* str)
		{
			Str tmp(str);
			swap(_str,tmp._str);
			swap(_size,tmp._size);
			swap(_capacity,tmp._capacity);

			return *this;
		}

		char* Show()
		{
			return _str;
		}
	private:
		char* _str;
		int _size;
		int _capacity;
};



void Str_test()
{
	Str s;
	s = "123";
	cout << s.Show() << endl;

	Str s2("12345");
	cout << s2.Show() << endl;

	cout << "s3" << endl;
	Str s3(s);
	cout << s3.Show() << endl;
	//	cout << s3._count << endl;

	Str s4;
	s4 = s2;
	cout << s4.Show() << endl;
	//	cout << s2._count<< endl;

	s4 = "abc";
	cout << s2.Show() << endl;
	cout << s4.Show() << endl;

	Str s5 = s4;
	cout << s5[1] << endl;
	cout << s5.Show() << endl;

	s5[1] = '5';	
	cout << s5.Show() << endl;
}



//����+дʱ����---����+����
class String
{
	public:
		String(const char* str = " ")//ע���˴�����ʹ��const���Σ���Ϊȱʡ��char*���ʹ洢�ڳ����������Ա���ʹ��const�����ַ��������޸�(str)
			:_str(new char[strlen(str)+1])//ĩβ���'\0'
			 ,_count(new int(1))
	{
		strcpy(_str,str);
	}
		//	s1(s)
		String(String& s )
			:_str(s._str)
			 ,_count(s._count)
	{
		(*_count)++;
	}

		//s1 = s;
		String& operator=(String& s)
		{
			if(_str == s._str)
				return *this;
			Delete();//����ɿռ�
			_str = s._str;
			_count = s._count;
			(*_count)++;
			return *this;
		}

		void Delete()
		{
			if(--(*_count) == 0)
			{
				delete []_str;
				delete _count;
			}
		}

		~String()//��Ҫ��ʾ�ĵ���������������������ܲ���ִ����������ʱ����ʾ����
		{
			Delete();
			_str = NULL;
		}

		void CopyWrite()//дʱ����
		{
			if((*_count) > 1)
			{
				*_count--;
				String tmp(_str);
				swap(_str,tmp._str);
				swap(_count,tmp._count);
			}	
			
			//String tmp(_str);
		//	_str = new char[strlen(_str)+1];
		//	assert(_str);
		//	strcpy(_str,tmp._str);
		//	_count = new int(1);
		//	tmp.Delete();
			//swap(_str,tmp._str);
			//swap(_count,tmp._count);
		}
		String& operator=(const char* str)
		{
			CopyWrite();
			strcpy(_str,str);
			return *this;
		}
		char& operator[](const size_t n)//��д�ɶ�
		{
			CopyWrite();
			return _str[n];
		}	
		const char& operator[](const size_t n) const//ֻ�ɶ�
		{
			return _str[n];//����ʱ���ַ������ڴ��У�Ϊ�˱������ز����޸ģ����Է���ֵҲ���β��ɸģ����󲻿��޸�����ʹ������
		}
		char* Show()
		{
			return _str;
		}
	public :
		char* _str;
		int* _count;
};

void String_test()
{
	String s;
	s = "123";
	cout << s.Show() << endl;

	String s2("12345");
	cout << s2.Show() << endl;

	cout << "s3" << endl;
	String s3(s);
	cout << s3.Show() << endl;
	printf("%d\n",*s3._count);
	//	cout << s3._count << endl;
	cout << "s4" << endl;
	String s4;
	s4 = s2;
	cout << s4.Show() << endl;
	//	cout << s2._count<< endl;
	printf("%d\n",*s2._count);

	cout << "s4="<< endl;
	s4 = "abc";
	cout << s2.Show() << endl;
	printf("%d\n",*s2._count);
	cout << s4.Show() << endl;
	printf("%d\n",*s4._count);

	cout << "s5"<< endl;
	String s5 = s4;
	cout << s5[1] << endl;
	cout << s5.Show() << endl;
	printf("%d\n",*s5._count);

	cout << "s5[]"<< endl;
	s5[1] = '5';
	cout << s4.Show() << endl;	
	cout << s5.Show() << endl;
	printf("%d\n",*s5._count);

}

