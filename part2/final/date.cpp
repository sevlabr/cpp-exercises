#include "date.h"

#include <string>
#include <stdexcept>
#include <tuple>
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

Date::Date(const int& new_year, const int& new_month, const int& new_day) {
	try {
		year = new_year;
		if (new_month > 12 || new_month < 1) {
			throw logic_error("Month value is invalid: " + to_string(new_month));
		}
		month = new_month;
		if (new_day > 31 || new_day < 1) {
			throw logic_error("Day value is invalid: " + to_string(new_day));
		}
		day = new_day;

	} catch (const logic_error& err) {
		cerr << err.what() << endl;
	}
}

int Date::GetYear() const {
	return year;
}

int Date::GetMonth() const {
	return month;
}

int Date::GetDay() const {
	return day;
}

bool operator < (const Date& lhs, const Date& rhs) {
	return make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) <
			make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}

bool operator <= (const Date& lhs, const Date& rhs) {
	return make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) <=
			make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}

bool operator > (const Date& lhs, const Date& rhs) {
	return make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) >
			make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}

bool operator >= (const Date& lhs, const Date& rhs) {
	return make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) >=
			make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}

bool operator == (const Date& lhs, const Date& rhs) {
	return make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) ==
			make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}

bool operator != (const Date& lhs, const Date& rhs) {
	return make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) !=
			make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}

ostream& operator << (ostream& os, const Date& date) {
	os << setw(4) << setfill('0') << date.GetYear()
			<< '-' << setw(2) << setfill('0') << date.GetMonth()
			<< '-' << setw(2) << setfill('0') << date.GetDay();
	return os;
}

Date ParseDate(istream& is) {
	try {
		bool ok = true;

		int year;
		ok = ok && (is >> year);
		ok = ok && (is.peek() == '-');
		is.ignore(1);

		int month;
		ok = ok && (is >> month);
		ok = ok && (is.peek() == '-');
		is.ignore(1);

		int day;
		ok = ok && (is >> day);

		if (!ok) {
			throw logic_error("Wrong date format");
		}

		return Date(abs(year), abs(month), abs(day));

	} catch (const logic_error& err) {
		cerr << err.what() << endl;
	}
}
