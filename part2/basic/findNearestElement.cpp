#include <iostream>
#include <set>
#include <cmath>

using namespace std;

/* #include <iterator>
#include <set>

set<int>::const_iterator FindNearestElement(const set<int>& numbers,
                                            int border) {
  // set::lower_bound ->
  // http://ru.cppreference.com/w/cpp/container/set/lower_bound
  const auto first_not_less = numbers.lower_bound(border);

  if (first_not_less == numbers.begin()) {
    return first_not_less;
  }

  // prev -> http://ru.cppreference.com/w/cpp/iterator/prev
  const auto last_less = prev(first_not_less);
  if (first_not_less == numbers.end()) {
    return last_less;
  }

  const bool is_left = (border - *last_less <= *first_not_less - border);
  return is_left ? last_less : first_not_less;
} */

set<int>::const_iterator FindNearestElement(
    const set<int>& numbers,
    int border) {
	if (numbers.empty()) {
		return end(numbers);
	}
	auto it_border = numbers.find(border);
	if (it_border != end(numbers)) {
		return it_border;
	}
	if (numbers.size() == 1) {
		return begin(numbers);
	}
	auto right = numbers.lower_bound(border);
	if (right == begin(numbers)) {
		return begin(numbers);
	}
	auto left = prev(right);
	int right_difference = abs(border - *right);
	int left_difference = abs(border - *left);
	if (left_difference < right_difference || left_difference == right_difference) {
		return left;
	} else {
		return right;
	}
}

int main() {
  set<int> numbers = {1, 4, 6};
  cout <<
      *FindNearestElement(numbers, 0) << " " <<
      *FindNearestElement(numbers, 3) << " " <<
      *FindNearestElement(numbers, 5) << " " <<
      *FindNearestElement(numbers, 6) << " " <<
      *FindNearestElement(numbers, 100) << endl;

  set<int> empty_set;

  cout << (FindNearestElement(empty_set, 8) == end(empty_set)) << endl;
  return 0;
}
