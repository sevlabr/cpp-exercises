#include "test_runner.h"
#include <algorithm>
#include <iterator>
#include <memory>
#include <vector>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
	const auto range_size = range_end - range_begin;
	if (range_size > 1) {
		vector<typename RandomIt::value_type> sorted(
				make_move_iterator(range_begin),
				make_move_iterator(range_end)
		);

		MergeSort(begin(sorted), begin(sorted) + range_size / 3);
		MergeSort(begin(sorted) + range_size / 3, begin(sorted) + 2 * range_size / 3);
		MergeSort(begin(sorted) + 2 * range_size / 3, end(sorted));

		vector<typename RandomIt::value_type> tmp;
		tmp.reserve(2 * range_size / 3);
		merge(make_move_iterator(begin(sorted)),
				make_move_iterator(begin(sorted) + range_size / 3),
				make_move_iterator(begin(sorted) + range_size / 3),
				make_move_iterator(begin(sorted) + 2 * range_size / 3),
				back_inserter(tmp)
		);

		merge(make_move_iterator(begin(tmp)),
				make_move_iterator(end(tmp)),
				make_move_iterator(begin(sorted) + 2 * range_size / 3),
				make_move_iterator(end(sorted)),
				range_begin
		);
	}
}

void TestIntVector() {
  vector<int> numbers = {6, 1, 3, 9, 1, 9, 8, 12, 1};
  MergeSort(begin(numbers), end(numbers));
  //cerr << numbers << endl;
  ASSERT(is_sorted(begin(numbers), end(numbers)));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestIntVector);
  return 0;
}
