#pragma once
#include<iostream>
//��������ָ�룬���ж���ʵ��
#include<memory>
using namespace std;
//std::shared_ptr<int> p1(new int[3]);//ʵ�ÿ��еģ�

//����2��������--->ֻ����������򽫿�����������Ϊ˽�еģ����ⲻ��ʹ�ã��Ӷ���ֹ���п�������
//�Լ����delete[]���⣿����---ScopedArry
template<class T>
class Scptr
{
public :
	Scptr(T* sp)//���캯��
		:_spr(sp)
	{}
	//���������,���ж�˽�����ݽ��в���
	T& operator*()
	{
		return *_spr;
	}
	T* operator->()
	{
		return _spr;
	}
	~Scptr()
	{
		if(_spr)
		delete _spr;
	}
private:
	Scptr(const Scptr<T>& sp);//�����������ó�˽�еģ���ֹ����
	Scptr<T>& operator=(const Scptr<T>& sp);//��ֵ����������
private: //˽����ֵ�ⲿ����ֱ�ӷ���
	T* _spr;
};

void Scptr_test()
{
	Scptr<int> sp(new int(2));
	*sp = 1;//sp.operator*()=1;
	cout << *sp << endl;
	//Scptr<int> sp2(sp);//���󿽱�����Ϊ˽�У����ɿ���
}
