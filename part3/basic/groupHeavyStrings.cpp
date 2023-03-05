#include "test_runner.h"

#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <utility>

using namespace std;

template <typename String>
using Group = vector<String>;

template <typename String>
using Char = typename String::value_type;

template <typename String>
using Identifier = set<Char<String>>;

template <typename String>
vector<Group<String>> GroupHeavyStrings(vector<String> strings) {

	vector<Group<String>> result;
	map<Identifier<String>, Group<String>> strs_by_identifiers;

	for (auto str_it = begin(strings); str_it != end(strings); ++str_it) {
		Identifier<String> str_identifier;
		for (auto symbol_it = begin(*str_it); symbol_it != end(*str_it); ++symbol_it) {
			str_identifier.insert(*symbol_it);
		}
		strs_by_identifiers[move(str_identifier)].push_back(move(*str_it));
	}

	result.reserve(strs_by_identifiers.size());
	for (auto it = begin(strs_by_identifiers); it != end(strs_by_identifiers); ++it) {
		result.push_back(move(it->second));
	}

	return result;
}

void TestGroupingABC() {
  vector<string> strings = {"caab", "abc", "cccc", "bacc", "c"};
  auto groups = GroupHeavyStrings(strings);
  ASSERT_EQUAL(groups.size(), 2);
  sort(begin(groups), end(groups));
  ASSERT_EQUAL(groups[0], vector<string>({"caab", "abc", "bacc"}));
  ASSERT_EQUAL(groups[1], vector<string>({"cccc", "c"}));
}

void TestGroupingReal() {
  vector<string> strings = {"law", "port", "top", "laptop", "pot", "paloalto", "wall", "awl"};
  auto groups = GroupHeavyStrings(strings);
  ASSERT_EQUAL(groups.size(), 4);
  sort(begin(groups), end(groups));
  ASSERT_EQUAL(groups[0], vector<string>({"laptop", "paloalto"}));
  ASSERT_EQUAL(groups[1], vector<string>({"law", "wall", "awl"}));
  ASSERT_EQUAL(groups[2], vector<string>({"port"}));
  ASSERT_EQUAL(groups[3], vector<string>({"top", "pot"}));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestGroupingABC);
  RUN_TEST(tr, TestGroupingReal);
  return 0;
}
