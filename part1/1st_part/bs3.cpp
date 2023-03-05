#include <set>
#include <map>
#include <string>
#include <iostream>

using namespace std;

int main() {
	int q;
	cin >> q;
	map<set<string>, int> bus_routes;
	for (int i = 0; i < q; ++i) {
		int n;
		cin >> n;
		set<string> route;
		for (int j = 0; j < n; ++j) {
			string stop;
			cin >> stop;
			route.insert(stop);
		}
		if (bus_routes.count(route) == 0) {
			int route_number = bus_routes.size() + 1;
			bus_routes[route] = route_number;
			cout << "New bus " << route_number << endl;
		} else {
			cout << "Already exists for " << bus_routes[route] << endl;
		}
	}
	return 0;
}
