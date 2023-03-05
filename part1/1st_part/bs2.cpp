#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

int main() {

	int q;
	cin >> q;

	map<vector<string>, int> bus_routes;

	for (int i = 0; i < q; ++i) {

		int n;
		cin >> n;
		vector<string> route;
		for (int j = 0; j < n; ++j) {
			string stop_name;
			cin >> stop_name;
			route.push_back(stop_name);
		}
		if (bus_routes.count(route) == 0) {
			int bus_number = bus_routes.size() + 1;
			bus_routes[route] = bus_number;
			cout << "New bus " << bus_number << endl;
		} else {
			cout << "Already exists for " << bus_routes[route] << endl;
		}

	}

	return 0;
}
