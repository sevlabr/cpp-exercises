#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int Factorial(int n) {
	if (n == 0) {
		return 1;
	} else {
		return n*Factorial(n-1);
	}
}

int main() {
	int n = 0;
	cin >> n;
	vector<int> v(n);
	for (int i = 0; i < n; ++i) {
		v[i] = i + 1;
	}
	int fact = Factorial(n);
	for (int i = 0; i < fact; ++i) {
		prev_permutation(begin(v), end(v));
		for (const int& val : v) {
			cout << val << " ";
		}
		cout << endl;
	}
	return 0;
}


/* int main() {
  int range_length;
  cin >> range_length;
  vector<int> permutation(range_length);

  // iota             -> http://ru.cppreference.com/w/cpp/algorithm/iota
  iota(permutation.rbegin(), permutation.rend(), 1);

  // prev_permutation ->
  //     http://ru.cppreference.com/w/cpp/algorithm/prev_permutation
  do {
    for (int num : permutation) {
      cout << num << ' ';
    }
    cout << endl;
  } while (prev_permutation(permutation.begin(), permutation.end()));

  return 0;
} */
