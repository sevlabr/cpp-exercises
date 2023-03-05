#pragma once

#include "date.h"

#include <map>
#include <vector>
#include <string>
#include <ostream>
#include <utility>
#include <set>

using namespace std;

template <class First, class Second>
ostream& operator << (ostream& os, const pair<First, Second>& p) {
	os << p.first << " " << p.second;
	return os;
}

class Database {
public:
	void Add(const Date& date, const string& event);
	void Print(ostream& os) const;
	template <class Func> int RemoveIf(Func predicate);
	template <class Func> vector<pair<Date, string>> FindIf(Func predicate) const;
	pair<Date, string> Last(const Date& date) const;
private:
	map<Date, vector<string>> storage;
	map<Date, set<string>> unordered_storage;
};


template <class Func> int Database::RemoveIf(Func predicate) {
	int count = 0;
	map<Date, vector<string>> updated_storage;
	map<Date, set<string>> updated_unordered_storage;
	for (const auto& [date, events] : storage) {
		for (auto it = events.begin(); it != events.end(); ++it) {
			if (predicate(date, *it)) {
				++count;
				//storage.at(date).erase(it);
			} else {
				updated_storage[date].push_back(*it);
				updated_unordered_storage[date].insert(*it);
			}
		}
	}
	unordered_storage = updated_unordered_storage;
	storage = updated_storage;
	return count;
}

template <class Func> vector<pair<Date, string>> Database::FindIf(Func predicate) const {
	vector<pair<Date, string>> elements;
	for (const auto& [date, events] : storage) {
		for (const string& event : events) {
			if (predicate(date, event)) {
				elements.push_back({date, event});
			}
		}
	}
	return elements;
}
