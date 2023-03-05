#include <map>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> FindNamesHistoryByYear(const map<int, string>& names, int year) {
	vector<string> names_history;

	for (const auto& item : names) {
		if (item.first <= year) {
			names_history.push_back(item.second);
		} else {
			break;
		}
	}

	return names_history;
}

string GetOldNames(const vector<string>& names_history, const string& current_name) {
	string old_names = "";
	if (!current_name.empty() && names_history.size() > 1) {
		string subsequent_name = current_name;
		int names_count = 0;
		for (int i = names_history.size() - 2; i >= 0; --i) {
			if (subsequent_name != names_history[i]) {
				if (names_count > 0) {
					old_names += ", ";
				} else {
					old_names += "(";
				}
				old_names += names_history[i];
				++names_count;
				subsequent_name = names_history[i];
			}
		}
		if (names_count > 0) {
			old_names += ")";
		}
	}
	return old_names;
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
    const vector<string> first_names_history = FindNamesHistoryByYear(first_names, year);
    const vector<string> last_names_history = FindNamesHistoryByYear(last_names, year);
    string first_name = "";
    string last_name = "";
    if (first_names_history.size() != 0) {
    	first_name = first_names_history[first_names_history.size() - 1];
    }
    if (last_names_history.size() != 0) {
    	last_name = last_names_history[last_names_history.size() - 1];
    }

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

  string GetFullNameWithHistory(int year) {
    const vector<string> first_names_history = FindNamesHistoryByYear(first_names, year);
    const vector<string> last_names_history = FindNamesHistoryByYear(last_names, year);
    string first_name = "";
    string last_name = "";
    if (first_names_history.size() != 0) {
      first_name = first_names_history[first_names_history.size() - 1];
    }
    if (last_names_history.size() != 0) {
        last_name = last_names_history[last_names_history.size() - 1];
    }

    if (first_name.empty() && last_name.empty()) {
      return "Incognito";
    }

    const string old_first_names = GetOldNames(first_names_history, first_name);
    const string old_last_names = GetOldNames(last_names_history, last_name);

    if (first_name.empty()) {
      if (old_last_names.empty()) {
        return last_name + " with unknown first name";
      } else {
        return last_name + " " + old_last_names + " with unknown first name";
      }

    } else if (last_name.empty()) {
      if (old_first_names.empty()) {
        return first_name + " with unknown last name";
      } else {
        return first_name + " " + old_first_names + " with unknown last name";
      }

    } else {
      if (old_first_names.empty() && old_last_names.empty()) {
        return first_name + " " + last_name;
      } else if (old_first_names.empty()) {
        return first_name + " " + last_name + " " + old_last_names;
      } else if (old_last_names.empty()) {
        return first_name + " " + old_first_names + " " + last_name;
      } else {
        return first_name + " " + old_first_names + " " + last_name + " " + old_last_names;
      }
    }
  }

private:
  map<int, string> first_names;
  map<int, string> last_names;
};


int main() {
  Person person;

  person.ChangeFirstName(1965, "Polina");
  person.ChangeFirstName(1965, "Appolinaria");

  person.ChangeLastName(1965, "Sergeeva");
  person.ChangeLastName(1965, "Volkova");
  person.ChangeLastName(1965, "Volkova-Sergeeva");

  for (int year : {1964, 1965, 1966}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }

  return 0;
}

/* #include <algorithm>
#include <map>
#include <vector>
#include <string>

using namespace std;

vector<string> FindNamesHistory(const map<int, string>& names_by_year,
                                int year) {
  vector<string> names;
  for (const auto& item : names_by_year) {
    if (item.first <= year && (names.empty() || names.back() != item.second)) {
      names.push_back(item.second);
    }
  }
  return names;
}

string BuildJoinedName(vector<string> names) {
  if (names.empty()) {
    return "";
  }
  
  reverse(begin(names), end(names));

  string joined_name = names[0];

  for (int i = 1; i < names.size(); ++i) {
    if (i == 1) {
      joined_name += " (";
    } else {
      joined_name += ", ";
    }
    joined_name += names[i];
  }

  if (names.size() > 1) {
    joined_name += ")";
  }

  return joined_name;
}

string BuildFullName(const string& first_name, const string& last_name) {
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

class Person {
public:
  void ChangeFirstName(int year, const string& first_name) {
    first_names[year] = first_name;
  }
  void ChangeLastName(int year, const string& last_name) {
    last_names[year] = last_name;
  }

  string GetFullName(int year) {
    const vector<string> first_names_history = FindFirstNamesHistory(year);
    const vector<string> last_names_history = FindLastNamesHistory(year);

    string first_name;
    string last_name;
    if (!first_names_history.empty()) {
      first_name = first_names_history.back();
    }
    if (!last_names_history.empty()) {
      last_name = last_names_history.back();
    }
    return BuildFullName(first_name, last_name);
  }

  string GetFullNameWithHistory(int year) {
    const string first_name = BuildJoinedName(FindFirstNamesHistory(year));
    const string last_name = BuildJoinedName(FindLastNamesHistory(year));
    return BuildFullName(first_name, last_name);
  }

private:
  vector<string> FindFirstNamesHistory(int year) {
    return FindNamesHistory(first_names, year);
  }
  vector<string> FindLastNamesHistory(int year) {
    return FindNamesHistory(last_names, year);
  }

  map<int, string> first_names;
  map<int, string> last_names;
}; */
