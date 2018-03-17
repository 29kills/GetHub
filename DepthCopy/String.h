#pragma once
#include<iostream>
#include<assert.h>
using namespace std;
//����
//1��ǳ����----����һ��ռ�
//ע��ǳ���������ü�����������һ��ռ�Ķ����������
//2��дʱ����--�Կռ�д����ʱ�����д����¿ռ俼��ԭ���ݣ������¿ռ������д����
class String
{
public:
	String(char* str = " ")//ȱʡֵΪ��('\0')����Ϊ�˱��ڴ���,����ΪNULL
		//ע����ʼ���б��ǰ�������˳���ʼ���ģ������Ǵ˴���˳��
	{
		_capacity = strlen(str)+1;
		_size = _capacity;//�ַ�����ͳ��'\0'
		_str = new char[_capacity];//+1��Ϊ�˿���'\0'
		strcpy(_str,str);
	}
	/*
	//��ǰд��---�Լ������¿ռ���������
	//s1(s)
	String(const String& s)//�Զ��忽�����죬�������---����ָ��ͬһ��ַ�ռ�
	{
		this->_str = new char[strlen(s._str)+1];//���
		strcpy(_str,s._str);
	}

	//s1=s;
	String& operator=(const String& s)//��ֵ����
	{
		if(this == &s)//����s1 = s1
			return *this;

		delete []_str;//�ͷ�ԭ�пռ�
		this->_str = new char[strlen(s._str)+1];//this�����ģ������п���ʾд��Ҳ�ɲ�д(ע���ββ�����ʾд)
		strcpy(_str,s._str);
		return *this;
	}
	*/

	//�ִ�д��---����һ���µĶ��󣬽��������е�����
	//s1(s);
	String(const String& s)
		:_str(NULL)//��ʼ_strΪ��---��ֹ��Ұָ������������³���
	{
		String tmp(s._str);//����һ����ʱ�������ڽ�������
		this->Swap(tmp);//��������(ָ��ĵ�ַ)
		//�˺����˳�ʱ������tmp����ʱtmp��ָ��ԭ����_str�ռ䣬����_str����
	}
	//s1 = s;
	String& operator=(String s)
	{
		this->Swap(s);//�����ββ�������ʱ���������󣩣�������ʱ����������
		return *this;
	}

	void Swap(String& s)//���ڽ������������
	{
		swap(s._str,_str);
		swap(s._capacity,_capacity);
		swap(s._size,_size);
	}
	char*& operator+=(char* ch)//�ַ�������
	{
		return this->operator+(ch);
	}
	char*& operator+(char* ch)
	{
		_capacity += strlen(ch);
		char* newstr = new char[_capacity];//�����¿ռ�
		strcpy(newstr,_str);//��ԭ�ַ������뵽�¿ռ�
		strcat(newstr,ch);//�ַ���ƴ��
		delete []_str;//�ͷ�ԭ�пռ�
		_str = newstr;//ָ���¿ռ�
		return _str;
	}

	char& operator[](const size_t pos)//,����������ɶ�����д
	{
		assert(pos < _size);//λ�úϷ�
		return _str[pos];
	}

	bool operator<(String& s)const //����this
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
	void Reverse(const size_t newcapacity)//����
	{
		//_str = (char*)realloc(_str,newcapacity);
		char* tmp = new char[newcapacity];
		memmove(tmp,_str,sizeof(char)*_size);
		delete []_str;
		_str = tmp;
		assert(_str);
	}
	//�����ַ���
	void Push_Back(const char* str)
	{
		size_t sz = strlen(str);
		if(_size+sz > _capacity)
		{
			_capacity += sz;
		    Reverse(_capacity);
		}
		strcpy(_str+_size-1,str);//��_size-1����λ��(-1�������±��0��ʼ)
		_size += sz;	
	}
	//�����ַ�---β��
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
	//ɾ��
	void Pop_Back()
	{
	}
	//����λ�ò���
	void Insert(const size_t pos,const char* str)
	{
		assert(pos < _size);
        size_t sz = strlen(str);
		if(_size+sz > _capacity)
		{
			_capacity += sz;
		    Reverse(_capacity);
		}
		int cur = _size-1;//ʹ��int ���ͣ�����posΪ0ʱ�ᷢ����ѭ��
		while(cur >= (int)pos)//����ǿ������ת��������ͬ���ͱȽϻ������ʽ����ת������Χ���ת����ת��size_t���ͣ������ѭ��
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
		int cur = _size-1;//ʹ��int ���ͣ�����posΪ0ʱ�ᷢ����ѭ��
		while(cur >= (int)pos)//�轫posת����int���ͱȽϣ�������ѭ��
		{
			_str[cur+1] = _str[cur];
			cur--;
		}
		_str[pos] = ch;
		_size++;
	}
	//����λ�ÿ�ʼɾ��count���ַ�
	void Erase(const size_t pos,const size_t count)
	{
		if(_size-pos <= count)//ɾ��posλ�ú�����Ԫ�أ����'\0'����
		{
			_str[pos] = '\0';
			_size = pos+1;//Ԫ�ظ������±��1��(�±��0��ʼ)
		}
		else //����ɾ�����ƶ�Ԫ��
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
	//����ĳ�ַ�
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
	//����ĳ�ַ���
	int Find(char* str)
	{
		size_t subsz = strlen(str);
		size_t curindex = 0;//��ǰԭ����ʼ�Ƚ��±�λ��
		size_t nextindex = 0;//��ǰԭ���Ƚ�λ��
		size_t subindex = 0;//��ǰ�Ƚϴ��ıȽ�λ��

		while(curindex < _size-subsz)//ԭ��δ������(ʣ�೤�ȴ��ڱȽϵĳ���)
		{
			nextindex = curindex;//�Ƚ�λ�� ÿ�δ� ��ǰ��ʼ�Ƚ�λ�� ��ʼ
			while(_str[nextindex++] == str[subindex++])
			{
				if(subindex == subsz)//һֱ��ͬ���������д��Ƚ��ַ���������ͬ
					return curindex;
			}
			curindex++;//��һ���ַ�����ͬ��ԭ�ַ����Ƚ�λ�ú��ˣ����Ƚ��ַ�������ʼλ�����¿�ʼ�Ƚ�
			subindex = 0;
		}
		//δ��ѭ�����˳���������ͬ
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
	char* _str;//char* ���ʹ洢�ַ���(�����ֳ�����)���ᵼ���ַ��������޸����⣬�����뿪�ٿռ�洢�ڶ��в����޸�
	size_t _size;//�ַ�����
	size_t _capacity;//����
};

void String_test()
{
	String s("123");
	String s1;//�޿������캯����ϵͳ�����Զ�����(vsǳ����,Linux���),ǳ����--ֱ�Ӹ�ֵ������ָ�����ڶ����������
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
	String s2("13");//ʹ�ù��캯��
	String s3 = "34";//ʹ�ù��캯������������ʽת��
	cout << (s2 < s3) << endl;
	cout << (s2 == s3) << endl;
}
