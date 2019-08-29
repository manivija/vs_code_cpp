#include <iostream>
#include "std_lib_facilities.h"

// things to do
// 1. Define a date today: June 25th, 1978
// 2. Define a date tomorrow, copying 'today' into it and increasing it be one using add_day()
// 3. Output today and tomorrow using << defined in 9.8
// 4. Report one error

class Date{

	int m_y;
	int m_m;
	int m_d;

	public:

	class Invalid{};

	Date(int y, int m, int d);
	void add_day(int n);
	bool is_valid_day(int y, int m, int d);
	int month() const {return m_m;}
	int year() const {return m_y;}
	int day() const {return m_d;}
};

Date::Date(int yy, int mm, int dd)
{
	if(true == is_valid_day(yy, mm, dd))
	{
		m_y = yy;
		m_m = mm;
		m_d = dd;
	}
	else
	{
		throw Invalid{};
	}
	
}

void Date::add_day(int n)
{
	if(false == is_valid_day(m_y, m_m, m_d+n))
		throw Invalid{};
	
	m_d+=n;
}

bool Date::is_valid_day(int y, int m, int d)
{
	if(m < 1 || m > 12)
		return false;

	if(d < 1 || d > 31)
		return false;

	return true; 
}

std::ostream& operator<<(std::ostream& os, const Date& d)
{
	return os << '(' << d.day() << ',' << d.month() << ',' << d.year() << ')';
}

int main(int argc, char *argv[]) 
{
	std::cout << "C++ ch9 Drill-3" << std::endl;
	
	try
	{
		Date today{1979, 6, 25};

		//1.
		std::cout<<"today is "<< today <<std::endl;

		//2.
		Date tomorrow{today};
		tomorrow.add_day(1);
		std::cout<<"tomorrow is "<< tomorrow <<std::endl;

		//3.
		tomorrow.add_day(7);
	}
	catch(Date::Invalid)
	{
		error("Invalid Date");
	}

	return 0;
}