#pragma once
#include<iostream>
using namespace std;

//�򵥵�����ָ��

template<class T>
class Smart//����ָ����
{
public :
	Smart(T* data)//����ͬʱ��ʼ��
		:_ptr(data)	
	{}
	T& operator*()//��ָ���*����
	{
		return *_ptr;//��������
	}
	T* operator->()
	{
		return _ptr;//���ص�ַ
	}
	~Smart()
	{
		if(_ptr)
			delete _ptr;
	}
private:
	T* _ptr;
};

struct Cell
{
	int _x;
	int _y;
};
void Smart_test()
{
	//ָ��---�����Զ��ͷſռ�
	int *p = new int(0);
	cout << *p << endl;

	//��ָ��---����ָ��---�Զ������������ͷſռ�
	Smart<int> s(new int(1));
	cout << *s << endl;
	
	Smart<int> s2(new int);
	*s2 = 2;
	cout << *s2 << endl;

	Smart<Cell> s3(new Cell);//�ṹ������
	s3->_x = 3;//���봦����ʵ����s3->->_x,ʵ�ֵ�
	s3->_y = 4;
	cout << s3->_x << endl;

	/*δ����������---���ָ��(����)ָ��ͬһ��ַ������ͬһ�ռ����ͷ�����
	  s2 = s;//s2Ҳָ��s��ַ�ռ䣬����s��������������
	  ���������
	  1������Ȩת�ƣ�����ȱ�ݵ����---->��Sptr.h�ļ�
	  2�����������򵥴ֱ�-------------->��Scoped_Ptr.h�ļ�
	  3�����ü�����ʵ�ø�����---------->��Shared_Ptr�ļ�
	  4�����(3)ѭ���������⣬��ָ��------>��Weak_Ptr.h�ļ�
	*/

	/*��������ָ�룬���ж���ʵ��
      #include<memory>//ͷ�ļ�
      std::shared_ptr<int> p1(new int[3]);//ʹ�ÿ��е�
	  C++11����ʹ��boost�еķ���
	  boost::shared_ptr<int> p1(new int[3]);//ʹ�ÿ��е�
	  */
}