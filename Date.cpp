#include "pch.h"

Date::Date() : day(0), mounth(0), year(0), leap(false) { }

Date::Date(int _day, int _mounth, int _year) : day(_day), mounth(_mounth), year(_year)
{
	if (is_leap(_year))
	{
		leap = true;
		amountDayInMounth[1] = 29;
	}
	else leap = false;
}

Date::Date(long long int _time_sec)
{
	int dayCount = _time_sec / 3600 / 24;
	Date temp(1, 1, 1970);
	temp.addDays(dayCount);
	day = temp.day;
	mounth = temp.mounth;
	year = temp.year;
	leap = temp.leap;
	if (leap) amountDayInMounth[1] = 29;
}

Date::Date(const Date& other) : day(other.day), mounth(other.mounth), year(other.year), leap(other.leap)
{
	if (leap) amountDayInMounth[1] = 29;
}

Date::~Date() { }

void Date::setDate(int _day, int _mounth, int _year)
{
	day = _day;
	mounth = _mounth;
	setYear(_year);
}

void Date::setDay(int _day)
{
	day = _day;
}

void Date::setMounth(int _mounth)
{
	mounth = _mounth;
}

void Date::setYear(int _year)
{
	year = _year;

	if (is_leap(_year))
	{
		leap = true;
		amountDayInMounth[1] = 29;
	}
	else leap = false;
}

int Date::getDay()
{
	return day;
}

int Date::getMounth()
{
	return mounth;
}

int Date::getYear()
{
	return year;
}

bool Date::getLeap()
{
	return leap;
}

int Date::range(const Date& other)
{
	int year_temp = 0, day_temp = 0;

	Date temp(other);
	int day_count_this = day_count(), day_count_other = temp.day_count();

	if (other.year > year)
	{
		if (day_count_other > day_count_this)
		{
			year_temp = absolute(other.year - year);

			day_temp += absolute(day_count_other - day_count_this);
		}
		else
		{
			year_temp = absolute(other.year - year) - 1;

			if (is_leap(other.year))
			{
				day_temp += 366 - day_count_this + day_count_other;
			}
			else
			{
				day_temp += 365 - day_count_this + day_count_other;
			}
		}

		for (int i = 0; i < year_temp; i++)
		{
			if (is_leap(year + i))
			{
				day_temp += 366;
			}
			else day_temp += 365;
		}
	}
	else if (other.year < year)
	{
		if (day_count_this > day_count_other)
		{
			year_temp = absolute(other.year - year);

			day_temp += absolute(day_count_other - day_count_this);
		}
		else
		{
			year_temp = absolute(other.year - year) - 1;

			if (is_leap(other.year))
			{
				day_temp += 366 - day_count_other + day_count_this;
			}
			else
			{
				day_temp += 365 - day_count_other + day_count_this;
			}
		}

		for (int i = 0; i < year_temp; i++)
		{
			if (is_leap(other.year + i))
			{
				day_temp += 366;
			}
			else day_temp += 365;
		}
	}
	else day_temp += absolute(day_count_other - day_count_this);

	return day_temp;
}

void Date::addDays(int value)
{
	int last_mounth = 0;
	while (value > 0)
	{
		if (day + value <= amountDayInMounth[mounth - 1])
		{
			day += value;
			break;
		}
		else
		{
			last_mounth = mounth;
			value -= (amountDayInMounth[last_mounth - 1] - day);
			if (mounth == 12)
			{
				mounth = 1;
				year++;
				if (is_leap(year)) amountDayInMounth[1] = 29;
				else amountDayInMounth[1] = 28;
				day = 0;
			}
			else if (mounth < 12)
			{
				mounth++;
				day = 0;
			}
		}
	}
}

void Date::subtractDays(int value)
{
	int last_mounth = 0;
	while (value > 0)
	{
		if (day - value > 0)
		{
			day -= value;
			break;
		}
		else
		{
			last_mounth = mounth;
			value -= day;
			if (mounth == 1)
			{
				mounth = 12;
				year--;
				if (is_leap(year)) amountDayInMounth[1] = 29;
				else amountDayInMounth[1] = 28;
				day = amountDayInMounth[11];
			}
			else if (mounth > 1)
			{
				mounth--;
				day = amountDayInMounth[mounth - 1];
			}
		}
	}
}

void Date::printDate()
{
	std::cout << day << "." << mounth << "." << year;
}

Date& Date::operator=(const Date& other)
{
	if (this == &other) return *this;
	else
	{
		this->~Date();
		new(this) Date(other);
	}
	return *this;
}

bool Date::operator ==(const Date& other)
{
	if (year == other.year && mounth == other.mounth && day == other.day) return true;
	else return false;
}

bool Date::operator !=(const Date& other)
{
	if (year == other.year && mounth != other.mounth && day == other.day) return true;
	else return false;
}

bool Date::operator >(const Date& other)
{
	Date temp(other);
	int day_count_this = day_count(), day_count_other = temp.day_count();

	if (year > other.year) return true;
	else if (year == other.year && day_count_this > day_count_other) return true;
	else return false;
}

bool Date::operator <(const Date& other)
{
	Date temp(other);
	int day_count_this = day_count(), day_count_other = temp.day_count();

	if (year < other.year) return true;
	else if (year == other.year && day_count_this < day_count_other) return true;
	else return false;
}

bool Date::operator >=(const Date& other)
{
	Date temp(other);
	int day_count_this = day_count(), day_count_other = temp.day_count();

	if (year > other.year) return true;
	else if (year == other.year && day_count_this >= day_count_other) return true;
	else return false;
}

bool Date::operator <=(const Date& other)
{
	Date temp(other);
	int day_count_this = day_count(), day_count_other = temp.day_count();

	if (year < other.year) return true;
	else if (year == other.year && day_count_this <= day_count_other) return true;
	else return false;
}

Date& Date::operator+=(int value)
{
	Date temp(*this);
	temp.addDays(value);

	this->~Date();
	new(this) Date(temp);
	return *this;
}

Date& Date::operator-=(int value)
{
	Date temp(*this);
	temp.subtractDays(value);

	this->~Date();
	new(this) Date(temp);
	return *this;
}

Date Date::operator+(int value)
{
	Date temp(*this);
	temp.addDays(value);
	return temp;
}

Date Date::operator-(int value)
{
	Date temp(*this);
	temp.subtractDays(value);
	return temp;
}

int Date::operator-(const Date& other)
{
	return range(other);
}

Date& Date::operator++()
{
	addDays(1);
	return *this;
}

Date Date::operator++(int value)
{
	Date temp(*this);
	addDays(1);
	return temp;
}

Date& Date::operator--()
{
	subtractDays(1);
	return*this;
}

Date Date::operator--(int value)
{
	Date temp(*this);
	subtractDays(1);
	return temp;
}

std::ostream& operator <<(std::ostream& os, const Date& other)
{
	os << other.day << " " << other.mounth << " " << other.year;
	return os;
}

std::istream& operator >>(std::istream& is, Date& other)
{
	int _year;
	is >> other.day >> other.mounth >> _year;
	other.setYear(_year);
	return is;
}

int Date::day_count()
{
	int temp = 0;
	for (int i = 0; i < mounth - 1; i++)
	{
		temp += amountDayInMounth[i];
	}
	temp += day;
	return temp;
}

bool is_leap(int _year)
{
	if (_year % 4 == 0 && (_year % 400 == 0 || _year % 100 != 0)) return true;
	else return false;
}

int absolute(int value)
{
	if (value >= 0) return value;
	else return -value;
}