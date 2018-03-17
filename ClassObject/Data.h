//实现一个日期类，可进行日期的加减
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
	void Add(size_t count)//天数增加
	{
		_day += count;//计算天数
		while(_day > month_day(count))//不和法进行计算
		{
			_day -= month_day(count) ;
			if(_month == 12)
			{
				_month = 1;
				_year++;
			}
			else//注意此处需加else,因为if成立的时，以对_month改变，不可再变
			_month++;//取当月天数计算下一个月
		}
	}
	void Sub(int count)//天数减小
	{
		if(count < 0)
			count = -count;//负数取反
		_day -= count ;//计算天数
		while(_day < 0)//不和法进行计算
		{
			if(_month == 1)//到达1月，退至12月，年-1
			{
				_month = 12;
				_year--;
			}
			else//注意此处需加else,因为if成立的时，以对_month改变，不可再变
			_month--;
			_day = month_day(count) + _day ;//去上一个月的天数计算
		}
	}
	//采用小的累加到大的，的方法统计天数
	size_t num(Data d)//计算两个日期的差值
	{
		Data small(*this);
		Data big(d);
		int day =  0;
		if(*this < big)//调用重载比较运算符函数
		{
			 small = *this;
			 big = d;
		}
		else
		{
			 small = d;
			 big = *this;
		}
		
		while(small != big)//调用重载比较运算符函数
		{
			small++;
			day++;
		}
		return day;
	}
	//设1.1.1为周1，天的差值%7+1即为周几
	size_t Weak()//判断周几
	{
		Data tmp(1,1,1);
		size_t weak = 2;
		size_t day = num(tmp);
		weak = day%7+weak;
		if(weak > 7 )
			weak -= 7;
		return weak;
	}
	//运算符重载
	bool operator!=(const Data d)
	{
		return (!(this->_year == d._year && this->_month == d._month && this->_day == d._day));
	}
	void operator++()
	{
		this->Add(1);//天数增加，同时修正日期
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
	size_t month_day(const size_t count)//返回当月天数
	{
		size_t arr[]={31,29,31,30,31,30,31,30,31,30,31,30};
		if(check())//闰年判断
			arr[1] = 28;
		else
			arr[1] = 29;
		return arr[_month-1];
	}
	bool check()//闰年判断
	{
		if(_year % 400 == 0 || (_year % 100 != 0 && _year % 4 == 0))
			return false;
		return true;
	}
private:
	int _year;
	int _month;//月放在数组中，直接检测赋值
	int _day;
};

void Data_test()
{
	Data d(2016,1,27);
	Data d2(2018,3,1);
	cout << d.Weak() << endl;//不同的年不正确？？？
	cout << d.num(d2) << endl;
	d.Display();
	d.Add(366);
	d.Display();
	d.Sub(366);
	d.Display();

}