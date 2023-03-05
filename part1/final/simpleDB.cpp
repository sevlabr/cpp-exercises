#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <exception>
#include <sstream>
#include <iomanip>

using namespace std;

class Date {
public:
	Date() {
		year = 0;
		month = 0;
		day = 0;
	}
	Date(const int& y, const int& m, const int& d) {
		year = y;
		month = m;
		day = d;
	}
	int GetYear() const {
		return year;
	}
	int GetMonth() const {
		return month;
	}
	int GetDay() const {
		return day;
	}

private:
	int year;
	int month;
	int day;
};

bool operator < (const Date& lhs, const Date& rhs) {
	if (lhs.GetYear() == rhs.GetYear() && lhs.GetMonth() == rhs.GetMonth()) {
		return lhs.GetDay() < rhs.GetDay();
	} else if (lhs.GetYear() == rhs.GetYear()) {
		return lhs.GetMonth() < rhs.GetMonth();
	} else {
		return lhs.GetYear() < rhs.GetYear();
	}
}

void EnsureDateFormat(const int& month, const int& day) {
	if (month < 1 || month > 12) {
		throw out_of_range("Month value is invalid: " + to_string(month));
	} else if (day < 1 || day > 31) {
		throw out_of_range("Day value is invalid: " + to_string(day));
	}
}

// TODO: rewrite
istream& operator >> (istream& stream, Date& date) {
	if (stream) {
		int year;
		if (stream >> year) {
			if (stream.peek() == '-') {
				stream.ignore(1);
				int month;
				if (stream >> month) {
					if (stream.peek() == '-') {
						stream.ignore(1);
						int day;
						if (stream >> day) {
							if (stream.peek() == EOF) {
								EnsureDateFormat(month, day);
								date = {year, month, day};
							} else {
								throw invalid_argument("Wrong date format: ");
							}
						} else {
							throw invalid_argument("Wrong date format: ");
						}
					} else {
						throw invalid_argument("Wrong date format: ");
					}
				} else {
					throw invalid_argument("Wrong date format: ");
				}
			} else {
				throw invalid_argument("Wrong date format: ");
			}
		} else {
			throw invalid_argument("Wrong date format: ");
		}
	}
	return stream;
}

ostream& operator << (ostream& stream, const Date& date) {
	stream << setw(4) << setfill('0') << date.GetYear() << '-'
			<< setw(2) << setfill('0') << date.GetMonth() << '-'
			<< setw(2) << setfill('0') << date.GetDay();
	return stream;
}

class Database {
public:
	void AddEvent(const Date& date, const string& event) {
		data[date].insert(event);
	}

	bool DeleteEvent(const Date& date, const string& event) {
		// .at returns out_of_range exception if data.at(date) is not found
		try {
			if (data.at(date).count(event) == 0) {
				return false;
			} else {
				data.at(date).erase(event);
				return true;
			}
		} catch (const out_of_range&) {
			//cout << "Date is not found (out_of_range .at exception)" << endl;
			return false;
		}
	}

	int  DeleteDate(const Date& date) {
		try {
			int size = data.at(date).size();
			data.erase(date);
			return size;
		} catch (const out_of_range&) {
			return 0;
		}
	}

	void Find(const Date& date) const {
		try {
			for (const string& event : data.at(date)) {
				cout << event << endl;
			}
		} catch (const out_of_range&) {
			//cout << "Date is not found (out_of_range .at exception)" << endl;
		}
	}

	void Print() const {
		for (const auto& [date, events] : data) {
			for (const string& event : events) {
				cout << date << " " << event << endl;
			}
		}
	}

private:
	map<Date, set<string>> data;
};

vector<string> ParseCommand(stringstream& stream) {
	vector<string> command_items;
	string command_item;
	while (stream >> command_item) {
		command_items.push_back(command_item);
	}
	return command_items;
}


int main() {
	Database db;

	string command;
	while (getline(cin, command)) {
		stringstream stream(command);
		if (command != "") {
			const vector<string> command_items = ParseCommand(stream);
			const string command_code = command_items.front();

			if (command_code == "Add") {
				const string new_date = command_items[1];
				stringstream stream(new_date);
				Date date;
				try {
					stream >> date;
				} catch (const invalid_argument& ex) {
					cout << ex.what() << new_date << endl;
					return 2;
				} catch (const out_of_range& ex) {
					cout << ex.what() << endl;
					return 3;
				}
				const string new_event = command_items[2];
				db.AddEvent(date, new_event);

			} else if (command_code == "Find") {
				const string considering_date = command_items[1];
				stringstream stream(considering_date);
				Date date;
				try {
					stream >> date;
				} catch (const invalid_argument& ex) {
					cout << ex.what() << considering_date << endl;
					return 2;
				} catch (const out_of_range& ex) {
					cout << ex.what() << endl;
					return 3;
				}
				db.Find(date);

			} else if (command_code == "Print") {
				db.Print();

			} else if (command_code == "Del") {
				if (command_items.size() == 2) {
					const string considering_date = command_items[1];
					stringstream stream(considering_date);
					Date date;
					try {
						stream >> date;
					} catch (const invalid_argument& ex) {
						cout << ex.what() << considering_date << endl;
						return 2;
					} catch (const out_of_range& ex) {
						cout << ex.what() << endl;
						return 3;
					}
					cout << "Deleted " << db.DeleteDate(date) << " events" << endl;

				} else {
					const string considering_date = command_items[1];
					stringstream stream(considering_date);
					Date date;
					try {
						stream >> date;
					} catch (const invalid_argument& ex) {
						cout << ex.what() << considering_date << endl;
						return 2;
					} catch (const out_of_range& ex) {
						cout << ex.what() << endl;
						return 3;
					}
					string event = command_items[2];
					if (db.DeleteEvent(date, event)) {
						cout << "Deleted successfully" << endl;
					} else {
						cout << "Event not found" << endl;
					}
				}

			} else {
				cout << "Unknown command: " << command_code << endl;
				return 1;
			}
		}
	}

	return 0;
}

/*#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

class Date {
public:
  Date(int new_year, int new_month, int new_day) {
    year = new_year;
    if (new_month > 12 || new_month < 1) {
      throw logic_error("Month value is invalid: " + to_string(new_month));
    }
    month = new_month;
    if (new_day > 31 || new_day < 1) {
      throw logic_error("Day value is invalid: " + to_string(new_day));
    }
    day = new_day;
  }

  int GetYear() const {
    return year;
  }
  int GetMonth() const {
    return month;
  }
  int GetDay() const {
    return day;
  }

private:
  int year;
  int month;
  int day;
};

bool operator<(const Date& lhs, const Date& rhs) {
  return vector<int>{lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()} <
      vector<int>{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()};
}

ostream& operator<<(ostream& stream, const Date& date) {
  stream << setw(4) << setfill('0') << date.GetYear() <<
      "-" << setw(2) << setfill('0') << date.GetMonth() <<
      "-" << setw(2) << setfill('0') << date.GetDay();
  return stream;
}

class Database {
public:
  void AddEvent(const Date& date, const string& event) {
    storage[date].insert(event);
  }

  bool DeleteEvent(const Date& date, const string& event) {
    if (storage.count(date) > 0 && storage[date].count(event) > 0) {
      storage[date].erase(event);
      return true;
    }
    return false;
  }

  int DeleteDate(const Date& date) {
    if (storage.count(date) == 0) {
      return 0;
    } else {
      const int event_count = storage[date].size();
      storage.erase(date);
      return event_count;
    }
  }

  set<string> Find(const Date& date) const {
    if (storage.count(date) > 0) {
      return storage.at(date);
    } else {
      return {};
    }
  }

  void Print() const {
    for (const auto& item : storage) {
      for (const string& event : item.second) {
        cout << item.first << " " << event << endl;
      }
    }
  }

private:
  map<Date, set<string>> storage;
};

Date ParseDate(const string& date) {
  istringstream date_stream(date);
  bool ok = true;

  int year;
  ok = ok && (date_stream >> year);
  ok = ok && (date_stream.peek() == '-');
  date_stream.ignore(1);

  int month;
  ok = ok && (date_stream >> month);
  ok = ok && (date_stream.peek() == '-');
  date_stream.ignore(1);

  int day;
  ok = ok && (date_stream >> day);
  ok = ok && date_stream.eof();

  if (!ok) {
    throw logic_error("Wrong date format: " + date);
  }
  return Date(year, month, day);
}

int main() {
  try {
    Database db;

    string command_line;
    while (getline(cin, command_line)) {
      stringstream ss(command_line);

      string command;
      ss >> command;

      if (command == "Add") {

        string date_str, event;
        ss >> date_str >> event;
        const Date date = ParseDate(date_str);
        db.AddEvent(date, event);

      } else if (command == "Del") {

        string date_str;
        ss >> date_str;
        string event;
        if (!ss.eof()) {
          ss >> event;
        }
        const Date date = ParseDate(date_str);
        if (event.empty()) {
          const int count = db.DeleteDate(date);
          cout << "Deleted " << count << " events" << endl;
        } else {
          if (db.DeleteEvent(date, event)) {
            cout << "Deleted successfully" << endl;
          } else {
            cout << "Event not found" << endl;
          }
        }

      } else if (command == "Find") {

        string date_str;
        ss >> date_str;
        const Date date = ParseDate(date_str);
        for (const string& event : db.Find(date)) {
          cout << event << endl;
        }

      } else if (command == "Print") {

        db.Print();

      } else if (!command.empty()) {

        throw logic_error("Unknown command: " + command);

      }
    }
  } catch (const exception& e) {
    cout << e.what() << endl;
  }

  return 0;
} */
