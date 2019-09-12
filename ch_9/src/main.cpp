#include <iostream>
#include "std_lib_facilities.h"

// things to do
// 1. Define a date today: June 25th, 1978
// 2. Define a date tomorrow, copying 'today' into it and increasing it be one using add_day()
// 3. Output today and tomorrow using << defined in 9.8
// 4. Report one error

enum class Month{
jan=1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
};

Month operator++(Month& m)
{
	if(Month::dec == m)
	{
		m = Month::jan;
		return m;
	}
	else
	{
		m = Month(int(m) + 1);
		return m;
	}
}

std::ostream& operator<<(std::ostream& os, const Month& d)
{
	switch(d)
	{
		case Month::jan:
			return os << "January";
		break;

		case Month::feb:
			return os << "Feburary";
		break;

		case Month::mar:
			return os << "March";
		break;

		case Month::apr:
			return os << "April";
		break;

		case Month::may:
			return os << "May";
		break;

		case Month::jun:
			return os << "June";
		break;

		case Month::jul:
			return os << "July";
		break;

		case Month::aug:
			return os << "August";
		break;

		case Month::sep:
			return os << "September";
		break;

		case Month::oct:
			return os << "October";
		break;

		case Month::nov:
			return os << "November";
		break;

		case Month::dec:
			return os << "December";
		break;
	}
}

class Date{

	int m_y;
	Month m_m;
	int m_d;

	public:

	class Invalid{};

	Date(int y, Month m, int d);
	void add_day(int n);
	bool is_valid_day(int y, Month m, int d);
	Month month() const {return m_m;}
	int year() const {return m_y;}
	int day() const {return m_d;}
	bool is_leap_year(int y);
};

Date::Date(int yy, Month mm, int dd)
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

bool Date::is_leap_year(int y)
{
	if(y%4 == 0)
	{
		if(y%100 == 0)
		{
			if(y%400 == 0)
				return true;
			else
				return false;
		}
		else
			return true;
	}
	else
		return false;
}

void Date::add_day(int n)
{	
	int year = m_y;
	Month month = m_m;
	int day = m_d;

	for(int ii = 1; ii < n+1; ii++)
	{
		switch(month)
		{

			case Month::feb:
				if(true == is_leap_year(year))
				{
					// its a leap year
					if(29 == day)
					{
						++month;
						day = 1;
					}
					else
						++day;
				}
				else
				{
					// not a leap year
					// its a leap year
					if(28 == day)
					{
						++month;
						day = 1;
					}
					else
						++day;
				}
				
			break;

			case Month::apr:
			case Month::jun:
			case Month::sep:
			case Month::nov:
				if(30 == day)
				{
					++month;
					day = 1;
				}
				else
					++day;
			break;

			case Month::jan:
			case Month::mar:
			case Month::may:
			case Month::jul:
			case Month::aug:
			case Month::oct:
				if(31 == day)
				{
					++month;
					day = 1;
				}
				else
					++day;
			break;

			case Month::dec:
				if(31 == day)
				{
					++month;
					++year;
					day = 1;
				}
				else
					++day;
			break;
		}
	}

	if(false == is_valid_day(year, month, day))
		throw Invalid{};
	
	m_y = year;
	m_m = month;
	m_d = day;
}

bool Date::is_valid_day(int y, Month m, int d)
{
		switch(m)
		{
			case Month::jan:
				if(d < 1 || d > 31)
					return false;
			break;

			case Month::feb:
				if(true == is_leap_year(m_y))
				{
					// its a leap year
					if(d < 1 || d > 29)
						return false;
				}
				else
				{
					// not a leap year
					if(d < 1 || d > 28)
						return false;
				}
				
			break;

			case Month::mar:
				if(d < 1 || d > 31)
					return false;
			break;

			case Month::apr:
				if(d < 1 || d > 30)
					return false;
			break;

			case Month::may:
				if(d < 1 || d > 31)
					return false;
			break;

			case Month::jun:
				if(d < 1 || d > 30)
					return false;
			break;

			case Month::jul:
				if(d < 1 || d > 31)
					return false;
			break;

			case Month::aug:
				if(d < 1 || d > 31)
					return false;
			break;

			case Month::sep:
				if(d < 1 || d > 30)
					return false;
			break;

			case Month::oct:
				if(d < 1 || d > 31)
					return false;
			break;

			case Month::nov:
				if(d < 1 || d > 30)
					return false;
			break;

			case Month::dec:
				if(d < 1 || d > 31)
					return false;
			break;

			default:
				return false;
		}

	if(y < 1800)
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
		Date today{1979, Month::jun, 25};

		//1.
		std::cout<<"today is "<< today <<std::endl;

		//2.
		Date tomorrow{today};
		tomorrow.add_day(1);
		std::cout<<"tomorrow is "<< tomorrow <<std::endl;

		//3.
		tomorrow.add_day(7);
		std::cout<<"adding 7 days to tomorrow becomes: "<< tomorrow <<std::endl;

		//4.
		tomorrow.add_day(187);
		std::cout<<"adding 187 days to tomorrow becomes: "<< tomorrow <<std::endl;

		//5. an invalid day
		Date randomDat{1979, Month::jun, 32};

	}
	catch(Date::Invalid)
	{
		error("Invalid Date");
	}

	return 0;
}