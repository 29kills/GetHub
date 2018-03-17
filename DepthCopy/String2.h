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
			_sz = strlen(str);//�ַ�������ͳ��'\0'
			_capacity = _sz+1;//��������'\0'��
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
			++(*_size);//ע��Ҫ�����ţ������ǵ�ַ++
		}
		//s1=s
		String& operator=(const String& s)
		{
			//ԭ����ļ�����Ϊһʱ���ͷžɿռ䣬ָ���¿ռ�(����)
			//ԭ����ļ�������Ϊһʱ��������-1��ָ���¿ռ�
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
		//����д�йصĲ���(�޸�����)�������ȴ������ĵ�ַ�ռ����⣬���ȵ���CopyWrite();
		//ע�����ڼ��Ƕ��ֿ�д�ĺ�������д������[]��
		char operator[](const size_t n)const//ֻ��
		{
			return _str[n];
		}
		char& operator[](const size_t n)//�ɶ���д
		{
		     CopyWrite();
			return _str[n];
		}
		void Push_Back(char ch)
		{
			//1���ȴ������Ŀռ��ַ���⣬�ͼ���������
		     CopyWrite();
			 //2������ռ��Ƿ��������

			 //3�������޸�����

		}
		//��������1���迪���¿ռ䣬ָ���µ�ַ��������Ӧ�¼�������ԭ������-1
		//дǰ����ռ�ͼ���������
		void CopyWrite()
		{
			if(*_size >1)
			{
				char* tmp = new char[_capacity];//������ԭ��һ���Ŀռ�
				strcpy(tmp,_str);
				(*_size)--;//ԭ���������-1
				//ָ���µ�ַ
				_str = tmp;
				_size = new int(1);//�����¼�����
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
		int* _size;//���ü�����ͬһ���ռ�ӦΪͬһ�����ü���������ʹ��ָ��,
		//�ɲ��������ü��������˼�������_strǰ4���ֽڴ���ʹ�ü�����ʱ��_str��4���ֽھͿ�ȡ�����˷����ɼ����ڴ���Ƭ����
		size_t _sz;//�ַ�����
		size_t _capacity;//����
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