#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>

using namespace std;

struct CompChar {
	int letter_index;
	bool operator() (const string& left, const char& val) const { return left[letter_index] < val; }
	bool operator() (const char& val, const string& left) const { return val < left[letter_index]; }
};

template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWithChar(
    RandomIt range_begin, RandomIt range_end,
    const char prefix, const int& count) {
	CompChar comp = CompChar{};
	comp.letter_index = count;
	return equal_range(range_begin, range_end, prefix, comp);
}

template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(
    RandomIt range_begin, RandomIt range_end,
    const string& prefix) {
	if (prefix.empty()) {
		return make_pair(range_begin, range_begin);
	}
	RandomIt lower_bound = range_begin;
	RandomIt upper_bound = range_end;
	int count = 0;
	for (const char& letter : prefix) {
		const auto result = FindStartsWithChar(lower_bound, upper_bound,
																	letter, count);
		lower_bound = result.first;
		upper_bound = result.second;
		++count;
	}
	return {lower_bound, upper_bound};
}

int main() {
  const vector<string> sorted_strings = {"moscow", "motovilikha", "murmansk"};

  const auto mo_result =
      FindStartsWith(begin(sorted_strings), end(sorted_strings), "mo");
  for (auto it = mo_result.first; it != mo_result.second; ++it) {
    cout << *it << " ";
  }
  cout << endl;

  const auto mt_result =
      FindStartsWith(begin(sorted_strings), end(sorted_strings), "mt");
  cout << (mt_result.first - begin(sorted_strings)) << " " <<
      (mt_result.second - begin(sorted_strings)) << endl;

  const auto na_result =
      FindStartsWith(begin(sorted_strings), end(sorted_strings), "na");
  cout << (na_result.first - begin(sorted_strings)) << " " <<
      (na_result.second - begin(sorted_strings)) << endl;

  return 0;
}

/* #include <algorithm>
#include <utility>
#include <string>


template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(
    RandomIt range_begin, RandomIt range_end, char prefix) {

  auto left = lower_bound(range_begin, range_end, string(1, prefix));

  char next_prefix = static_cast<char>(prefix + 1);

  auto right = lower_bound(range_begin, range_end, string(1, next_prefix));

  return {left, right};
} */

/* #include <algorithm>
#include <utility>
#include <string>


template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(
	RandomIt range_begin, RandomIt range_end, string prefix) {

  auto left = lower_bound(range_begin, range_end, prefix);

  string upper_bound = prefix;
  ++upper_bound[upper_bound.size() - 1];

  auto right = lower_bound(range_begin, range_end, upper_bound);

  return {left, right};
} */
