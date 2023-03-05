#include <iostream>
#include <vector>
#include <list>

using namespace std;

const int MAX_COUNT = 100'000;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int n;
	cin >> n;

	list<int> athlets;
	vector<list<int>::const_iterator> athlets_its(MAX_COUNT + 1, end(athlets));

	for (int i = 0; i < n; ++i) {
		int new_athlet;
		cin >> new_athlet;
		int position_after;
		cin >> position_after;

		athlets_its[new_athlet] = athlets.insert(athlets_its[position_after], new_athlet);
	}

	for (auto it = begin(athlets); it != end(athlets); ++it) {
		cout << *it << "\n";
	}

	return 0;
}
