#pragma once

class Record
{
private:
	Date date;
	int sum;
	string info;


public:
	Record();

	Record(Date _date, int _sum, string _info);

	Record(const Record & other);

	~Record();

	void printRecord();

	void setRecord(Date _date, int _sum, string _info);


	friend std::ostream& operator<<(std::ostream&, const Record&);

	friend std::istream& operator>>(std::istream&, Record&);
};

