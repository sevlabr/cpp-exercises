#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

class Person {
public:
  void ChangeFirstName(int year, const string& first_name) {
	  person[year]["first_name"] = first_name;
	  years_history.push_back(year);
	  sort(begin(years_history), end(years_history));
  }
  void ChangeLastName(int year, const string& last_name) {
	  person[year]["last_name"] = last_name;
	  years_history.push_back(year);
	  sort(begin(years_history), end(years_history));
  }
  string GetFullName(int year) {
	  if (year < years_history[0]) {
		  return "Incognito";

	  } else if (year > years_history[years_history.size() - 1]) {
		  year = years_history[years_history.size() - 1];
		  return GetFullNameIfYearExists(year);

	  } else if (person.count(year) == 1) {
		  return GetFullNameIfYearExists(year);

	  } else {
		  while (person.count(year) == 0) {
			  --year;
		  }
		  return GetFullNameIfYearExists(year);
	  }

  }

private:
  string GetFullNameIfYearExists(int year) {
	  if (person[year].size() == 2) {
		  return person[year]["first_name"] + " " + person[year]["last_name"];

	  } else if (person[year].count("first_name") == 1) {
		  string first_name = person[year]["first_name"];
		  int index = 0;
		  while (years_history[index] != year) {
			  ++index;
		  }
		  for (int i = index; i >= 0; --i) {
			  year = years_history[i];
			  if (person[year].count("last_name") == 1) {
				  return first_name + " " + person[year]["last_name"];
			  }
			  if (i == 0) {
				  return first_name + " with unknown last name";
			  }
		  }

	  } else {
		  string last_name = person[year]["last_name"];
		  int index = 0;
		  while (years_history[index] != year) {
			  ++index;
		  }
		  for (int i = index; i >= 0; --i) {
			  year = years_history[i];
			  if (person[year].count("first_name") == 1) {
				  return person[year]["first_name"] + " " + last_name;
			  }
			  if (i == 0) {
				  return last_name + " with unknown first name";
			  }
		  }
	  }
  }

  map<int, map<string, string>> person;
  vector<int> years_history;
};


int main() {
  Person person;

  person.ChangeFirstName(1965, "Polina");
  person.ChangeLastName(1967, "Sergeeva");
  for (int year : {1900, 1965, 1990}) {
    cout << person.GetFullName(year) << endl;
  }

  person.ChangeFirstName(1970, "Appolinaria");
  for (int year : {1969, 1970}) {
    cout << person.GetFullName(year) << endl;
  }

  person.ChangeLastName(1968, "Volkova");
  for (int year : {1969, 1970}) {
    cout << person.GetFullName(year) << endl;
  }

  return 0;
}

/* #include <map>
#include <string>

string FindNameByYear(const map<int, string>& names, int year) {
  string name;

  for (const auto& item : names) {
    if (item.first <= year) {
      name = item.second;
    } else {
      break;
    }
  }

  return name;
}

class Person {
public:
  void ChangeFirstName(int year, const string& first_name) {
    first_names[year] = first_name;
  }
  void ChangeLastName(int year, const string& last_name) {
    last_names[year] = last_name;
  }
  string GetFullName(int year) {
    const string first_name = FindNameByYear(first_names, year);
    const string last_name = FindNameByYear(last_names, year);

    if (first_name.empty() && last_name.empty()) {
      return "Incognito";
    } else if (first_name.empty()) {
      return last_name + " with unknown first name";
    } else if (last_name.empty()) {
      return first_name + " with unknown last name";
    } else {
      return first_name + " " + last_name;
    }
  }

private:
  map<int, string> first_names;
  map<int, string> last_names;
}; */
