#pragma once
#include<iostream>
#include"Copy.h"
using namespace std;
//�����飬˳���ȴ洢�ṹ ����ԭ�����һ��������
template<class T>
class myvector//˳���
{
public :
	typedef T* Iterator;//�����ǹ������ͣ������ⲿ����ʹ��
	typedef const T* const_Iterator;
	myvector()
		:_start(0)
		,_finish(0)
		,_end(0)
	{}
	void Puch_Back(const T& data)//β��
	{
		Inserve(End(),data);//����
	}

	 Iterator Erase(Iterator pos)//ɾ��
	{
		//��δ��������ʧЧ����
		//�ж�λ�úϷ�
		assert(pos <= _finish);
		//Iterator begin = pos + 1;
		//while(pos < _finish)
		//{
		//	*(begin-1) = *begin;
		//}
		Iterator begin = pos ;
		Iterator next = pos + 1;//�Ӻ�һ�����ݿ�ʼ��ǰ�ƶ�
		while(next < _finish)//�ƶ�����
		{
			*begin++ = *next++;
		}
	    _finish--;
		return pos;//���ص�ǰλ��
	}
	void Inserve(Iterator pos,const T& data)//����
	{
		//ע�����ݵ��µ�����ʧЧ���⣨pos��ΪNULL��
		//���ݺ�ָ���µĵ�ַ��pos��ַʧЧ
		int gap = pos - _start;//�������λ��
		if(_finish == _end)//����
		{
			size_t size = Capacity();
			size_t newsize = size > 0 ? size*2 : 3;
			Expand(newsize);//����--posλ��ʧЧ
		}
		pos = _start + gap;//pos�����ҵ���Ӧλ��		
		assert(pos <= _finish);//�Ϸ�λ��
		Iterator end = _finish - 1;//������һ�����ݵ�λ��
		while(end >= pos)//��������
		{
			*end = *--end;
		}
		_finish++;
		*pos = data;
	}

	void Resize(size_t count,const T& val = T())//valΪȱʡ���������򴫣����򲻴���
	{
		//1������--���������Ƿ��ʼ�������ռ�
		//count < size--����finish
		//cout > size---�踳ֵ��val�͸���finish
		size_t size = Size();//��ȡԭ��Ԫ�ظ���
		Expand(count);//����

		Iterator cur = _start + size;//ָ���Ӧ���ʼ���ĵ�һ��λ�ã�ԭ��Ӧfinish��
		_finish = _start + count;//�µ�����λ��
		if(count > size)
		{
			while(cur < _finish)//��ʼ��
			{
				*(cur++) = val; 
			}
		}
	}
	void Reserve(size_t count)//������
	{
		//����
		Expand(count);//����
	}
	size_t Size()//��Ԫ�ظ���
	{
		return _finish - _start;//ָ�����=Ԫ�ظ���
	}
	size_t Capacity()//������
	{
		return _end - _start;
	}
	void Expand(size_t count)//����
	{
		size_t size = Size();
		size_t capacity = Capacity();
		if(count > capacity)
		{
			T* tmp = new T[count];//T[count]--����count���ռ�,T(count)--����һ���ռ��ʼ��Ϊcount
			if(_start)
			    __TypeCopy(tmp,_start,size);//����size��Ӧ��ʹ�������
		    delete []_start;//����
			_start = tmp;
			_finish = _start + size;
			_end = _start + count;
		}
	}
	void Print()
	{
		Iterator tmp = _start;
		while(tmp < _finish)
		{
			cout << *tmp++ << ' ';
		}
		cout << endl;
	}
	Iterator Begin()
	{
		return _start;
	}
	Iterator End()
	{
		return _finish;
	}

	const_Iterator Begin() const
	{
		return _start;
	}
	const_Iterator End() const
	{
		return _finish;
	}
	T& operator[](const size_t n)
	{
		return _start[n];
	}
private :
	Iterator _start;//ͷָ��(����ͷ)
    Iterator _finish;//����β�������ݣ�
	Iterator _end;//���β��������
};

template<class T>
void print_vector(const myvector<T>& V1)
{
	myvector<int>::const_Iterator v = V1.Begin();
	while(v != V1.End())
	{
		//*v = 4;//const�����������޸�
		cout << *v << ' ';
		v++;
	}
	cout << endl;
}

template<class T>
void Erase_vector(myvector<T>& V1)
{
	myvector<int>::Iterator v = V1.Begin();
	T* tmp =  V1.End();
	while(v != V1.End())//˳�������ݵ�ַ�ᷢ���仯����������ݵ�ַ���ᷢ���仯
	{
		if(*v%2 == 0)
		   v = V1.Erase(v);//ɾ��������3��ô����
		else
		++v;
	}
	cout << endl;
}


void myvector_test()
{
	size_t i = 0;
	myvector<int> V1;
	V1.Puch_Back(1);
	V1.Puch_Back(2);
	V1.Puch_Back(3);
	V1.Puch_Back(4);
	V1.Puch_Back(6);
	V1.Puch_Back(3);
	V1.Puch_Back(5);
	V1.Puch_Back(8);

	V1.Print();
	Erase_vector(V1);
	V1.Print();

	V1.Erase(V1.Begin());//ɾ��
	V1.Erase(V1.End());//ɾ��
	V1.Print();


	//V1.Erase(V1.End());//ɾ��
	//print_vector(V1);

	cout << "size=" << V1.Size() << endl;
	cout << "������" << V1.Capacity() << endl;

	V1.Reserve(8);
	cout << "size=" << V1.Size() << endl;
	cout << "������" << V1.Capacity() << endl;

	
	V1.Resize(10,6);
	i =  V1.Size();
	cout << "size=" << V1.Size() << endl;
	cout << "������" << V1.Capacity() << endl;

	for(i = 0;i < V1.Size();i++)
	{
		printf("V1[%d]=%d ",i,V1[i]);//�������ص�[]����
	}
	cout << endl;

	print_vector(V1);
	
}