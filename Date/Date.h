#pragma once 
#include<iostream>
#include<algorithm>
using namespace std;

class Date
{
public:
	Date(const int year = 1990,const int month = 1,const int day = 1)
		:_year(year)
		,_month(month)
		,_day(day)
	{}
	//d(d1)
	Date(const Date& d)
	{
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}
	//d1 = d
	Date& operator=(const Date& d)
	{
		//if(!(_year == d._year && _month == d._month && _day == d._day))
		if(*this != d)
		{
			_year = d._year;
			_month = d._month;
			_day = d._day;
			//Date d1(d);
			//swap(*this,d1);
		}
		return *this;
	}

	bool IsInvalid()//检测日期合法
	{
		int month[12] = {31,29,31,30,31,30,31,31,30,31,30,31};
		if(_year >= 0)
		{
			if(LeapYear(_year))
				month[1] = 28;
				if(_month >= 1 && _month <= 12)
					if(month[_month-1] == _day)
						return true;
		}
		return false;
	}

	bool LeapYear(const int year)//判断闰年
	{
		if(year%400 ==0 ||(year%4 == 0 && year%100 != 0))
			return true;
		return false;
	}
	int GetMonthDay(int year, int month) 
	{
		int monthday[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
		if(LeapYear(_year))
			monthday[1] = 29;
		return monthday[month-1];
	}

	void Show() 
	{
		printf("%d-%d-%d\n",_year,_month,_day);
	}

	bool operator==(const Date& d) 
	{
		if(_year == d._year && _month == d._month && _day == d._day)
			return true;
		return false;
	}
	bool operator!=(const Date& d) 
	{
		return !(*this == d);
	}
	bool operator>=(const Date& d) 
	{
		if((_year > d._year) ||
			(_year == d._year && _month > d._month) ||
			(_year == d._year && _month == d._month && _day > d._day))
			return true;
		else
			return false;
	}

	bool operator<=(const Date& d)
	{
		if(!(*this >= d) || *this == d)
			return true;
		else
			return false;
	}
	bool operator>(const Date& d)
	{
		if(!(*this <= d))
			return true;
		else
			return false;
	}
	bool operator<(const Date& d)
	{
		return !(*this >= d);
	}
	
	Date operator+(int day) 
	{
		if(day < 0)
		{
			return *this-day;
		}
		_day += day;
		int n = GetMonthDay(_year,_month);//获取月的天数
		while(n < _day)
		{
			if(_month == 12)
			{
				_year++;
				_month = 1;
			}
			else
				_month++;
			_day -= n;
			n = GetMonthDay(_year,_month);//获取月的天数
		}
		return *this;
	}

	Date& operator+=(int day)
	{
		return *this+day;
	}
	Date operator-(int day)
	{
		if(day < 0)
		{
			return *this+day;
		}
		_day -= day;
		int n = GetMonthDay(_year,_month);//获取月的天数
		while(_day <= 0)
		{
			if(_month == 1)
			{
				_year--;
				_month = 12;
			}
			else
				_month--;
			n = GetMonthDay(_year,_month);//获取月的天数
			_day += n;
		}
		return *this; 
	}

	Date& operator-=(int day)
	{
		return *this-day;
	}

	int operator-(const Date& d)
	{
		int count = 0;
		Date max;
		Date min;
		int tmp = 1;//默认>0
		if(*this < d)
		{
			min = *this;
			max = d;
			tmp = -1;
		}

		if(*this > d)
		{
			max = *this;
			min = d;
		}

		while(min < max)
		{
			min+30;
			count += 30;
		}
		while(min != max)
		{
			min-1;
			count--;
		}
		return count*tmp;
	}

	Date& operator++() // 前置 
	{
		return (*this)++;
	}
//d1++ 
	Date operator++(int) // 后置
	{
		Date tmp(*this);
		(*this)++;
		return tmp;
	}
	Date operator--()
	{
		return (*this)--;
	}

	Date operator--(int)
	{
		Date tmp(*this);
		(*this)--;
		return tmp;
	}

	int weak()
	{
		Date tmp(1990,1,1);
		int w = 1;
		w = (*this-tmp)%7+1;
		return w;
	}

	~Date()
	{}
private:
	int _year;
	int _month;
	int _day;
};

void DateTest()
{
	Date d1(2018,4,5);
	Date d2(2019,4,25);
	cout << (d1>d2) << endl;
	cout << (d1<d2) << endl;
	d1.Show();
	d2.Show();
	
	d1.Show();
	d1-1000;
	d1.Show();
	
	d1 += 10000;
	d1.Show();

	d1 -= 10000;
	d1.Show();

	d1-10;
	d1.Show();
	
	cout << d1-d2 << endl;
	cout << d2-d1 << endl;
	
	cout << d2.weak() << endl;
}
