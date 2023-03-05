#pragma once

#include <string>

using namespace std;

class PhoneNumber {
public:
    /*
        * +7-495-111-22-33
        * +7-495-1112233
        * +323-22-460002
        * +1-2-coursera-cpp
        * 1-2-333
        * +7-1233
    */
    explicit PhoneNumber(const string &international_number);

    string GetCountryCode() const;
    string GetCityCode() const;
    string GetLocalNumber() const;
    string GetInternationalNumber() const;

private:
    string country_code_;
    string city_code_;
    string local_number_;
};
