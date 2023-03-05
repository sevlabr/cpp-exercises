#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


template <typename RandomIt>
void Print(RandomIt range_begin, RandomIt range_end, const string& message) {
	cout << message << ":" << endl;
	for (RandomIt it = range_begin; it != range_end; ++it) {
		cout << *it << " ";
	}
	cout << endl;
}

template <typename RandomIt>
void MergeSortDiv2(RandomIt range_begin, RandomIt range_end) {
	if (range_end - range_begin >= 2) {
		vector<typename RandomIt::value_type> elements(range_begin, range_end);
		RandomIt middle = begin(elements) + elements.size() / 2;
		MergeSort(begin(elements), middle);
		MergeSort(middle, end(elements));
		merge(begin(elements), middle,
				middle, end(elements),
				range_begin);
	}
}

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
	if (range_end - range_begin >= 3) {
		vector<typename RandomIt::value_type> elements(range_begin, range_end);
		RandomIt one_third = begin(elements) + elements.size() / 3;
		RandomIt two_thirds = one_third + elements.size() / 3;
		MergeSort(begin(elements), one_third);
		MergeSort(one_third, two_thirds);
		MergeSort(two_thirds, end(elements));
		vector<typename RandomIt::value_type> temp;
		merge(begin(elements), one_third,
				one_third, two_thirds,
				back_inserter(temp));
		merge(begin(temp), end(temp),
				two_thirds, end(elements),
				range_begin);
	}
}

int main() {
  vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1, 5};
  MergeSort(begin(v), end(v));
  for (int x : v) {
    cout << x << " ";
  }
  cout << endl;
  return 0;
}


/* template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
  int range_length = range_end - range_begin;
  if (range_length < 2) {
    return;
  }

  vector<typename RandomIt::value_type> elements(range_begin, range_end);

  auto one_third = elements.begin() + range_length / 3;
  auto two_third = elements.begin() + range_length * 2 / 3;

  MergeSort(elements.begin(), one_third);
  MergeSort(one_third, two_third);
  MergeSort(two_third, elements.end());

  // back_inserter -> http://ru.cppreference.com/w/cpp/iterator/back_inserter
  vector<typename RandomIt::value_type> interim_result;
  merge(elements.begin(), one_third, one_third, two_third,
        back_inserter(interim_result));

  // merge -> http://ru.cppreference.com/w/cpp/algorithm/merge
  merge(interim_result.begin(), interim_result.end(), two_third, elements.end(),
        range_begin);
} */
