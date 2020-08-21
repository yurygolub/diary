#include "pch.h"

Record::Record() : sum(0), info("")
{

}

Record::Record(Date _date, int _sum, string _info) : date(_date), sum(_sum), info(_info)
{

}

Record::Record(const Record& other) : date(other.date), sum(other.sum), info(other.info)
{

}

Record::~Record()
{

}

void Record::printRecord()
{
	std::cout << date << "\t" << sum << "\t" << info << endl;
}

void Record::setRecord(Date _date, int _sum, string _info)
{
	date = _date;
	sum = _sum;
	info = _info;
}


std::ostream& operator <<(std::ostream& os, const Record& other)
{
	os << other.date << " " << other.sum << " " << other.info;
	return os;
}

std::istream& operator >>(std::istream& is, Record& other)
{
	is >> other.date >> other.sum >> other.info;
	return is;
}