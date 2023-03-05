#include <vector>
#include <cstdint>
#include <iostream>

using namespace std;

int main() {
	int n;
	cin >> n;
	vector<int> temps(n);
	int64_t sum = 0;
	for (auto& temp : temps) {
		cin >> temp;
		sum += temp;
	}
	int size = static_cast<int>(temps.size());
	int64_t avg = sum / size;
	vector<int> days;
	for (int i = 0; i < size; ++i) {
		if (temps[i] > avg) {
			days.push_back(i);
		}
	}
	cout << days.size() << endl;
	for (const auto& day : days) {
		cout << day << " ";
	}
	cout << endl;
	return 0;
}

/* #include <iostream>
#include <vector>

using namespace std;

int main() {
  int n;
  cin >> n;
  vector<int> temperatures(n);
  int64_t sum = 0;
  for (int& temperature : temperatures) {
    cin >> temperature;
    sum += temperature;
  }

  int average = sum / n;

  vector<int> above_average_indices;
  for (int i = 0; i < n; ++i) {
    if (temperatures[i] > average) {
      above_average_indices.push_back(i);
    }
  }

  cout << above_average_indices.size() << endl;
  for (int i : above_average_indices) {
    cout << i << " ";
  }
  cout << endl;

  return 0;
} */
