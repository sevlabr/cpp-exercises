#include "database.h"
#include "date.h"

#include <string>
#include <algorithm>
#include <utility>
#include <exception>

using namespace std;

/*
void Database::Add(const Date& date, const string& event) {
	auto begin = storage[date].begin();
	auto end = storage[date].end();
	auto duplicate = find(begin, end, event);
	if (duplicate == end) {
		storage[date].push_back(event);
	}
} */

void Database::Add(const Date& date, const string& event) {
	auto equal_or_greater = unordered_storage[date].lower_bound(event);
	if (equal_or_greater == unordered_storage[date].end()
			|| *equal_or_greater != event) {
		unordered_storage[date].insert(event);
		storage[date].push_back(event);
	}
}

void Database::Print(ostream& os) const {
	for (const auto& [date, events] : storage) {
		for (const string& event : events) {
			os << date << " " << event << endl;
		}
	}
}

pair<Date, string> Database::Last(const Date& date) const {
	auto iter_after = storage.upper_bound(date);
	if (iter_after != storage.begin()) {
		auto it = prev(iter_after);
		return {it->first, (it->second).back()};
	} else {
		throw invalid_argument("");
	}
}
