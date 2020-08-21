#pragma once

class Date
{
private:
	int day;
	int mounth;
	int year;
	bool leap;
	int amountDayInMounth[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

public:
	Date();

	Date(int _day, int _mounth, int _year);

	Date(long long int _time_sec);

	Date(const Date& other);

	~Date();

	void setDate(int _day, int _mounth, int _year);

	void setDay(int _day);

	void setMounth(int _mounth);

	void setYear(int _year);

	int getDay();

	int getMounth();

	int getYear();

	bool getLeap();

	int range(const Date& other);

	void addDays(int value);

	void subtractDays(int value);

	void printDate();

	Date& operator=(const Date& other);

	bool operator ==(const Date& other);

	bool operator !=(const Date& other);

	bool operator >(const Date& other);

	bool operator <(const Date& other);

	bool operator >=(const Date& other);

	bool operator <=(const Date& other);

	Date& operator+=(int value);

	Date& operator-=(int value);

	Date operator+(int value);

	Date operator-(int value);

	int operator-(const Date& other);

	Date& operator++();

	Date operator++(int value);

	Date& operator--();

	Date operator--(int value);

	friend std::ostream& operator<<(std::ostream&, const Date&);

	friend std::istream& operator>>(std::istream&, Date&);

private:

	int day_count();

};

bool is_leap(int _year);

int absolute(int value);