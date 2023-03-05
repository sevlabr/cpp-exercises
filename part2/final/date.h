#pragma once

#include <iostream>

using namespace std;

class Date {
public:
	Date(const int& new_year, const int& new_month, const int& new_day);

	int GetYear() const;
	int GetMonth() const;
	int GetDay() const;

private:
	int year;
	int month;
	int day;
};


bool operator < (const Date& lhs, const Date& rhs);
bool operator <= (const Date& lhs, const Date& rhs);
bool operator > (const Date& lhs, const Date& rhs);
bool operator >= (const Date& lhs, const Date& rhs);
bool operator == (const Date& lhs, const Date& rhs);
bool operator != (const Date& lhs, const Date& rhs);

ostream& operator << (ostream& os, const Date& date);

Date ParseDate(istream& is);
