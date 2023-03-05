#include <stdexcept>
#include <iostream>

#include "phone_number.h"

using namespace std;

int main() {
	try {
		string international_number;
		cin >> international_number;
		PhoneNumber phone(international_number);
		cout << "Country: " << phone.GetCountryCode() << endl;
		cout << "City: " << phone.GetCityCode() << endl;
		cout << "LocalNumber: " << phone.GetLocalNumber() << endl;
		cout << "InternationalNumber: " << phone.GetInternationalNumber() << endl;
	} catch (const invalid_argument&) {
		cout << "Invalid argument" << endl;
		exit(1);
	}
	return 0;
}
