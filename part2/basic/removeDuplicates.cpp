#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

template <typename T>
void RemoveDuplicates(vector<T>& elements) {
	sort(begin(elements), end(elements));
	auto it = unique(begin(elements), end(elements));
	elements.erase(it, end(elements));
}

int main() {
  vector<int> v1 = {6, 4, 7, 6, 4, 4, 0, 1};
  RemoveDuplicates(v1);
  for (int x : v1) {
    cout << x << " ";
  }
  cout << endl;

  vector<string> v2 = {"C", "C++", "C++", "C", "C++"};
  RemoveDuplicates(v2);
  for (const string& s : v2) {
    cout << s << " ";
  }
  cout << endl;
  return 0;
}

/* advanced sorting

bool f(const int& val) {
	if (val % 2 == 0) {
		return true;
	}
	return false;
}



int main() {
  set<int> s = {1, 2, 3, 4, 5, 6, 7};
  vector<int> v;
  v.assign(begin(s), end(s));
  sort(begin(v), end(v),
       [](int lhs, int rhs) { return f(lhs) > f(rhs); });
  for (const int& num : v) {
	  cout << num << " ";
  }
  return 0;
} */

/* cout : OK

int main() {
	set<int> nums = {1, 2, 3};
	auto it1 = nums.find(1);
	auto it2 = nums.find(3);
	if (it1  != it2) {
		cout << "OK" << endl;
	}
	return 0;
} */

/* search function testing. working only with one-by-one seq

int main() {
	vector<int> v1 = {1, 2, 3, 5, 4};
	vector<int> v2 = {1, 2, 3, 5};
	auto it = search(begin(v1), end(v1), begin(v2), end(v2));
	if (it != end(v1)) {
		vector<int> v(it, it + v2.size());
		for (const int& i : v) {
			cout << i << endl;
		}
	} else {
		cout << "Not found" << endl;
	}
	return 0;
} */

/* input iterators:

template <typename It>
void PrintRange(It range_begin, It range_end) {
	for (auto it = range_begin;
		it != range_end; ++it) {
		cout << *it << " ";
	}
	cout << endl;
}

int main() {
	const istream_iterator<string> start(cin);
	const istream_iterator<string> end;
	auto start_copy = start;
	++start_copy;
	cout << (start == start_copy) << endl;
	vector<string> strings(start, end);
	vector<string> strings_copy(start_copy, end);
	vector<string> more_strings(start, end);
	cout << strings.size() << endl;
	for (const string& s : strings) {
		cout << s << ", ";
	}
	cout << endl;
	for (const string& s : strings_copy) {
		cout << s << ", ";
	}
	cout << endl;
	for (const string& s : more_strings) {
		cout << s << ", ";
	}

	return 0;
}

1 //
2 //
1
3 //
4 //
5 //
4
1, 3, 4, 5,
2,
1, */
