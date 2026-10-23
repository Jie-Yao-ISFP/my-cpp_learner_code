#define _CRT_SECURE_NO_WARNINGS
#include"date.h"
#include<assert.h>
//构造函数
Date::Date(int year, int month, int day)
{
	assert(month > 12 || day > GetMonthDay(year, month));
	_year = year;
	_month = month;
	_day = day;
}

//拷贝构造函数,但是编译器给的足够用
Date::Date(const Date& d) {
	_year = d._year;
	_month = d._month;
	_day = d._day;
}

// 赋值运算符重载
  // d2 = d3 -> d2.operator=(&d2, d3)
Date& Date::operator=(const Date& d)
{
	_year = d._year;
	_month = d._month;
	_day = d._day;
	return *this;
}

// 获取某年某月的天数
int GetMonthDay(int year, int month) 
{
	int a[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
	if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
	{
		a[2] = 29;
	}
	return a[month];
}

// 日期+=天数
Date& Date::operator+=(int day)
{
	if (day < 0) {
		return *this -= -day;
	}
	_day += day;
	while (_day > GetMonthDay(_year, _month)) {
		_day -= GetMonthDay(_year, _month);
		_month++;
		if (_month > 12) {
			_year++;
			_month = 1;
		}
	}
	return *this;
}

// 日期+天数
Date Date::operator+(int day) {
	Date tmp = *this;
	tmp += day;
	return tmp;
}

// 日期-=天数
Date& Date::operator-=(int day) {
	if (day < 0) {
		return *this += -day;
	}
	_day -= day;
	while (_day < 1) {
		_month--;
		if (_month < 1) {
			_year--;
			_month = 12;
		}
		_day += GetMonthDay(_year, _month);
	}
	return *this;
}

// 日期-天数
Date Date::operator-(int day) {
	Date tmp = *this;
	tmp -= day;
	return tmp;
}

// 前置++
Date& Date::operator++() {
	_day++;
	if (_day > GetMonthDay(_year, _month)) {
		_day = 1;
		_month++;
		if (_month > 12) {
			_year++;
			_month = 1;
		}
	}
	return *this;
}

// 后置++
Date Date::operator++(int) {
	Date tmp = *this;
	++*this;
	return tmp;
}

// 前置--
Date& Date::operator--() {
	_day--;
	if (_day < 1) {
		_month--;
		if (_month < 1) {
			_year--;
			_month = 12;
		}
		_day = GetMonthDay(_year, _month);

	}
	return *this;
}

// 后置--
Date Date::operator--(int)
{
	Date tmp = *this;
	--*this;
	return tmp;
}

// >运算符重载
bool Date::operator>(const Date& d) {
	if (_year > d._year)
		return true;
	if (_year == d._year) {
		if (_month > d._month)
			return true;
		else if (_month == d._month) {
			if (_day > d._day)
				return true;
			else
				return false;
		}
		else
			return false;
	}
	else
		return false;
}

// ==运算符重载
bool Date::operator==(const Date& d) {
	return (_year == d._year && _month == d._month && _day == d._day);
}

// >=运算符重载
bool Date::operator >= (const Date& d) {
	if (*this == d)
		return true;
	if (*this > d)
		return true;
	return false;
}

// <运算符重载
bool Date::operator < (const Date& d) {
	return !(*this >= d);
}

// <=运算符重载
bool Date::operator <= (const Date& d) {
	if (*this == d)
		return true;
	if (*this < d)
		return true;
	return false;
}

// !=运算符重载
bool Date::operator != (const Date& d) {
	return !(*this == d);
}


// 日期-日期 返回天数
int Date::operator-(const Date& d) {
	int count = 0;
	Date big = *this;
	Date small = d;
	int flag = 1;
	if (*this < d) {
		big = d;
		small = *this;
		flag = -1;
	}
	while (small != big) {
	
		small++;
		count++;
	}
	return count*flag;
}

int main()
{
	Date d1(2000, 8, 9);
	Date d2 = d1;
	d1 += 30;
	d1.Print();
	Date d3 = d2 + 30;
	d3.Print();

	Date d4(2026, 8, 7);
	d4+=1433;
	d4.Print();

	return 0;
}