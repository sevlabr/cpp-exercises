#include "phone_number.h"

#include <stdexcept>
#include <sstream>

using namespace std;

/*PhoneNumber::PhoneNumber(const string& international_number) {
	istringstream is(international_number);

	char sign = is.get();
	getline(is, country_code_, '-');
	getline(is, city_code_, '-');
	getline(is, local_number_);

	if (sign != '+' || country_code_.empty() || city_code_.empty() || local_number_.empty()) {
		throw invalid_argument("Phone number must begin with
		                       '+' symbol and contain 3 parts separated by '-' symbol:"
							   + international_number);
	}
} */

PhoneNumber::PhoneNumber(const string &international_number) {
	if (international_number.empty()) {
		throw invalid_argument("");
	}

	bool first = true;
	bool country = true;
	ostringstream country_ss;
	bool city = true;
	ostringstream city_ss;
	ostringstream number;

	for (const char& c : international_number) {
		if (first && c != '+') {
			throw invalid_argument("");
		} else if (first) {
			first = false;
			continue;
		}

		if (country && c != '-') {
			country_ss << c;
			continue;
		} else if (country) {
			country = false;
			continue;
		}

		if (city && c != '-') {
			city_ss << c;
			continue;
		} else if (city) {
			city = false;
			continue;
		}

		number << c;
	}

	if (country_ss.str().empty() || city_ss.str().empty() || number.str().empty()) {
		throw invalid_argument("");
	} else {
		country_code_ = country_ss.str();
		city_code_ = city_ss.str();
		local_number_ = number.str();
	}
}

string PhoneNumber::GetCountryCode() const {
	return country_code_;
}
string PhoneNumber::GetCityCode() const {
	return city_code_;
}
string PhoneNumber::GetLocalNumber() const {
	return local_number_;
}
string PhoneNumber::GetInternationalNumber() const {
	return "+" + country_code_ + "-" + city_code_ + "-" + local_number_;
}
