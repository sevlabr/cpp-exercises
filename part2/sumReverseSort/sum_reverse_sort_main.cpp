#include "sum_reverse_sort.h"
#include <iostream>

using namespace std;

int main() {
	int x = 5;
	int y = -6;
	cout << "Sum: " << Sum(x, y) << endl;
	string s = "kden";
	cout << "Reverse: " << Reverse(s) << endl;
	vector<int> v = {120, 11, -10, 6};
	Sort(v);
	cout << "Sort: ";
	for (const int& i : v) {
		cout << i << " ";
	}
}




