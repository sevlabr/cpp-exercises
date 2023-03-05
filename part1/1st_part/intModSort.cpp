#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

int main() {
	int n;
	cin >> n;
	vector<int> nums(n);
	for (int i = 0; i < n; ++i) {
		cin >> nums[i];
	}
	sort(begin(nums), end(nums), [](int l, int r) {
		if (abs(l) < abs(r)) {
			return true;
		} else {
			return false;
		}
	});
	for (const int& number : nums) {
		cout << number << " ";
	}
	return 0;
}

/* #include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {

  int n;
  cin >> n;
  vector<int> v(n);
  for (int& x : v) {
    cin >> x;
  }

  sort(begin(v), end(v),
       [](int l, int r) {
         return abs(l) < abs(r);
       }
  );
  
  for (int x : v) {
    cout << x << " ";
  }

  return 0;
} */
