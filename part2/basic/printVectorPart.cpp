#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void PrintVectorPart(const vector<int>& numbers) {
	auto it = find_if(
			begin(numbers), end(numbers),
			[](const int& number) {
			return number < 0;
	});
	while (it != begin(numbers)) {
		--it;
		cout << *it << " ";
	}
    /* for (auto it = negative_it; it != numbers.begin(); ) {
	    cout << *(--it) << " ";
	} */
}

int main() {
  PrintVectorPart({6, 1, 8, -5, 4});
  cout << endl;
  PrintVectorPart({-6, 1, 8, -5, 4});
  cout << endl;
  PrintVectorPart({6, 1, 8, 5, 4});
  cout << endl;
  return 0;
}
