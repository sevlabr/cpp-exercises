#include <iostream>
#include <vector>

using namespace std;

int main() {
	int n;
	cin >> n;
	vector<int> v(n);
	for (int i = 0; i < n; ++i) {
		int temp;
		cin >> temp;
		v[i] = temp;
	}
	int avg = 0;
	for (auto temp : v) {
		avg += temp;
	}
	avg /= n;
	vector<int> days;
	for (int i = 0; i < n; ++i) {
		if (v[i] > avg) {
			days.push_back(i);
		}
	}
	cout << days.size() << endl;
	for (auto day : days) {
		cout << day << " ";
	}
	return 0;
}

/*#include <iostream>
#include <vector>

using namespace std;

int main() {
  int n;
  cin >> n;
  vector<int> temperatures(n);
  int sum = 0;
  for (int& temperature : temperatures) {
    cin >> temperature;
    sum += temperature;
  }

  int average = sum / n;
  vector<int> result_indices;
  for (int i = 0; i < n; ++i) {
    if (temperatures[i] > average) {
      result_indices.push_back(i);
    }
  }

  cout << result_indices.size() << endl;
  for (int result_index : result_indices) {
    cout << result_index << " ";
  }
  cout << endl;

  return 0;
} */
