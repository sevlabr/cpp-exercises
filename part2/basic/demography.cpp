#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

enum class Gender {
  FEMALE,
  MALE
};


struct Person {
  int age;
  Gender gender;
  bool is_employed;
};

template <typename InputIt>
int ComputeMedianAge(InputIt range_begin, InputIt range_end) {
  if (range_begin == range_end) {
    return 0;
  }
  vector<typename InputIt::value_type> range_copy(range_begin, range_end);
  auto middle = begin(range_copy) + range_copy.size() / 2;
  nth_element(
      begin(range_copy), middle, end(range_copy),
      [](const Person& lhs, const Person& rhs) {
        return lhs.age < rhs.age;
      }
  );
  return middle->age;
}

string GetStrGender(const Gender& current_gender) {
	string gender;
	switch(current_gender){
	case Gender::FEMALE:
		gender = "females";
		break;
	case Gender::MALE:
		gender = "males";
		break;
	}
	return gender;
}

void PrintGenderBasedStats(vector<Person>& persons, const Gender& current_gender) {
	auto it = partition(begin(persons), end(persons),
						[current_gender](const Person& person){
						return person.gender == current_gender;
	});
	string gender = GetStrGender(current_gender);
	cout << "Median age for " << gender << " = " << ComputeMedianAge(begin(persons), it) << endl;
}

string GetStrStatus(const bool& work_status) {
	string status;
	if (work_status == true) {
		status = "employed";
	} else {
		status = "unemployed";
	}
	return status;
}

void PrintDetailedStats(vector<Person>& persons, const Gender& current_gender,
							const bool& work_status) {
	auto it = partition(begin(persons), end(persons),
						[current_gender, work_status](const Person& person){
						return person.gender == current_gender && person.is_employed == work_status;
	});
	string gender = GetStrGender(current_gender);
	string status = GetStrStatus(work_status);
	cout << "Median age for " << status << " " << gender << " = "
			<< ComputeMedianAge(begin(persons), it) << endl;
}

void PrintStats(vector<Person> persons) {
	cout << "Median age = " << ComputeMedianAge(begin(persons), end(persons)) << endl;
	PrintGenderBasedStats(persons, Gender::FEMALE);
	PrintGenderBasedStats(persons, Gender::MALE);

	PrintDetailedStats(persons, Gender::FEMALE, true);
	PrintDetailedStats(persons, Gender::FEMALE, false);

	PrintDetailedStats(persons, Gender::MALE, true);
	PrintDetailedStats(persons, Gender::MALE, false);
}

/* void PrintStats(vector<Person> persons) {
    //                  persons
    //                 /      \
    //          females        males
    //         /       \     /      \
    //      empl.  unempl. empl.   unempl.
    auto females_end = partition(
        begin(persons), end(persons), [](const Person& p) {
            return p.gender == Gender::FEMALE;
        }
    );
    auto employed_females_end = partition(
        begin(persons), females_end, [](const Person& p) {
            return p.is_employed;
        }
    );
    auto employed_males_end = partition(
        females_end, end(persons), [](const Person& p) {
            return p.is_employed;
        }
    );

    cout << "Median age = "
         << ComputeMedianAge(begin(persons), end(persons))          << endl;
    cout << "Median age for females = "
         << ComputeMedianAge(begin(persons), females_end)           << endl;
    cout << "Median age for males = "
         << ComputeMedianAge(females_end, end(persons))             << endl;
    cout << "Median age for employed females = "
         << ComputeMedianAge(begin(persons),  employed_females_end) << endl;
    cout << "Median age for unemployed females = "
         << ComputeMedianAge(employed_females_end, females_end)     << endl;
    cout << "Median age for employed males = "
         << ComputeMedianAge(females_end, employed_males_end)       << endl;
    cout << "Median age for unemployed males = "
         << ComputeMedianAge(employed_males_end, end(persons))      << endl;
} */

int main() {
  vector<Person> persons = {
      {31, Gender::MALE, false},
      {40, Gender::FEMALE, true},
      {24, Gender::MALE, true},
      {20, Gender::FEMALE, true},
      {80, Gender::FEMALE, false},
      {78, Gender::MALE, false},
      {10, Gender::FEMALE, false},
      {55, Gender::MALE, true},
  };
  PrintStats(persons);
  return 0;
}
