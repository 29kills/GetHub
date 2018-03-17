//ʵ��һ�������࣬�ɽ������ڵļӼ�
#pragma once 
#include<iostream>
using namespace std;

class Data
{
public:
	Data()
	{}
	Data(size_t year,size_t month,size_t day)
		:_year(year)
		,_month(month)
		,_day(day)
	{}
	void Display()
	{
		cout << _year <<'-'<<_month << '-' <<_day << endl;
	}
	void Add(size_t count)//��������
	{
		_day += count;//��������
		while(_day > month_day(count))//���ͷ����м���
		{
			_day -= month_day(count) ;
			if(_month == 12)
			{
				_month = 1;
				_year++;
			}
			else//ע��˴����else,��Ϊif������ʱ���Զ�_month�ı䣬�����ٱ�
			_month++;//ȡ��������������һ����
		}
	}
	void Sub(int count)//������С
	{
		if(count < 0)
			count = -count;//����ȡ��
		_day -= count ;//��������
		while(_day < 0)//���ͷ����м���
		{
			if(_month == 1)//����1�£�����12�£���-1
			{
				_month = 12;
				_year--;
			}
			else//ע��˴����else,��Ϊif������ʱ���Զ�_month�ı䣬�����ٱ�
			_month--;
			_day = month_day(count) + _day ;//ȥ��һ���µ���������
		}
	}
	//����С���ۼӵ���ģ��ķ���ͳ������
	size_t num(Data d)//�����������ڵĲ�ֵ
	{
		Data small(*this);
		Data big(d);
		int day =  0;
		if(*this < big)//�������رȽ����������
		{
			 small = *this;
			 big = d;
		}
		else
		{
			 small = d;
			 big = *this;
		}
		
		while(small != big)//�������رȽ����������
		{
			small++;
			day++;
		}
		return day;
	}
	//��1.1.1Ϊ��1����Ĳ�ֵ%7+1��Ϊ�ܼ�
	size_t Weak()//�ж��ܼ�
	{
		Data tmp(1,1,1);
		size_t weak = 2;
		size_t day = num(tmp);
		weak = day%7+weak;
		if(weak > 7 )
			weak -= 7;
		return weak;
	}
	//���������
	bool operator!=(const Data d)
	{
		return (!(this->_year == d._year && this->_month == d._month && this->_day == d._day));
	}
	void operator++()
	{
		this->Add(1);//�������ӣ�ͬʱ��������
	}
	bool operator<(const Data d)
	{
		if((this->_year < d._year) || 
		   (this->_year == this->_year && this->_month < d._month)||
		   (this->_year == d._year && this->_month == d._month && this->_day < d._day))
			return true;
		else
			return false;
	}
	size_t month_day(const size_t count)//���ص�������
	{
		size_t arr[]={31,29,31,30,31,30,31,30,31,30,31,30};
		if(check())//�����ж�
			arr[1] = 28;
		else
			arr[1] = 29;
		return arr[_month-1];
	}
	bool check()//�����ж�
	{
		if(_year % 400 == 0 || (_year % 100 != 0 && _year % 4 == 0))
			return false;
		return true;
	}
private:
	int _year;
	int _month;//�·��������У�ֱ�Ӽ�⸳ֵ
	int _day;
};

void Data_test()
{
	Data d(2016,1,27);
	Data d2(2018,3,1);
	cout << d.Weak() << endl;//��ͬ���겻��ȷ������
	cout << d.num(d2) << endl;
	d.Display();
	d.Add(366);
	d.Display();
	d.Sub(366);
	d.Display();

}