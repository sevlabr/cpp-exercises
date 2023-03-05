#include <iostream>
#include <vector>

using namespace std;

vector<int> Reversed(const vector<int>& v) {
	vector<int> copy;
	int size = v.size();
	for (int i = 0; i < size; ++i) {
			copy.push_back(v[size - i - 1]);
	}
	return copy;
}

void Reverse(vector<int>& v) {
	vector<int> tmp;
	for (auto n : v) {
		tmp.push_back(n);
	}
	int size = v.size();
	for (int i = 0; i < size; ++i) {
		v[i] = tmp[size - i - 1];
	}
}

int main() {
	vector<int> numbers = {1, 5, 3, 4, 2};
	Reverse(numbers);
	for (auto n : numbers) {
		cout << n << " ";
	}
	cout << endl;
	numbers = {1, 5, 3, 4, 2};
	vector<int> new_numbers = Reversed(numbers);
	for (auto n : new_numbers) {
			cout << n << " ";
	}
	return 0;
}


/*void Reverse(vector<int>& v) {
  int n = v.size();
  for (int i = 0; i < n / 2; ++i) {
    int tmp = v[i];
    v[i] = v[n - 1 - i];
    v[n - 1 - i] = tmp;
  }
} */
