#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {

	int q;
	cin >> q;

	map<string, vector<string>> bus_stops;
	vector<string> ordered_bus_names;

	for (int i = 0; i < q; ++i) {

		string operation_code;
		cin >> operation_code;

		if (operation_code == "NEW_BUS") {

			string bus;
			int stop_count;
			cin >> bus >> stop_count;
			ordered_bus_names.push_back(bus);
			for (int j = 0; j < stop_count; ++j) {
				string stop;
				cin >> stop;
				bus_stops[bus].push_back(stop);
			}

		} else if (operation_code == "BUSES_FOR_STOP") {

			string stop;
			cin >> stop;

			int j = 0;
			for (const string& bus : ordered_bus_names) {
				const vector<string>& stops = bus_stops[bus];
				if (count(begin(stops), end(stops), stop) == 1) {
					cout << bus << " ";
					++j;
				}
			}
			/*for (const auto& [bus, stops] : bus_stops) {
				if (count(begin(stops), end(stops), stop) == 1) {
					cout << bus << " ";
					++j;
				}
			} */
			if (j == 0) {
				cout << "No stop";
			}
			cout << endl;

		} else if (operation_code == "STOPS_FOR_BUS") {

			string current_bus;
			cin >> current_bus;

			if (bus_stops.count(current_bus) == 0) {
				cout << "No bus" << endl;
			} else {
				const vector<string>& current_stops = bus_stops[current_bus];
				for (const string& stop : current_stops) {
					cout << "Stop " << stop << ": ";
					int j = 0;
					for (const string& bus : ordered_bus_names) {
						const vector<string>& stops = bus_stops[bus];
						if (count(begin(stops), end(stops), stop) == 1 && bus != current_bus) {
							cout << bus << " ";
							++j;
						}
					}
					/*for (const auto& [bus, stops] : bus_stops) {
						if (count(begin(stops), end(stops), stop) == 1 && bus != current_bus) {
							cout << bus << " ";
							++j;
						}
					} */
					if (j == 0) {
						cout << "no interchange";
					}
					cout << endl;
				}
			}

		} else if (operation_code == "ALL_BUSES") {

			if (bus_stops.size() == 0) {
				cout << "No buses" << endl;

			} else {
				for (const auto& [bus, stops] : bus_stops) {
					cout << "Bus " << bus <<": ";
					for (const string& stop : stops) {
						cout << stop << " ";
					}
					cout << endl;
				}
			}

		}

	}

	return 0;
}


/* #include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

void PrintBusesForStop(map<string, vector<string>>& stops_to_buses,
                       const string& stop) {
  if (stops_to_buses.count(stop) == 0) {
    cout << "No stop" << endl;
  } else {
    for (const string& bus : stops_to_buses[stop]) {
      cout << bus << " ";
    }
    cout << endl;
  }
}

void PrintStopsForBus(map<string, vector<string>>& buses_to_stops,
                      map<string, vector<string>>& stops_to_buses,
                      const string& bus) {
  if (buses_to_stops.count(bus) == 0) {
    cout << "No bus" << endl;
  } else {
    for (const string& stop : buses_to_stops[bus]) {
      cout << "Stop " << stop << ": ";

      if (stops_to_buses[stop].size() == 1) {
        cout << "no interchange";
      } else {
        for (const string& other_bus : stops_to_buses[stop]) {
          if (bus != other_bus) {
            cout << other_bus << " ";
          }
        }
      }
      cout << endl;
    }
  }
}

void PrintAllBuses(const map<string, vector<string>>& buses_to_stops) {
  if (buses_to_stops.empty()) {
    cout << "No buses" << endl;
  } else {
    for (const auto& bus_item : buses_to_stops) {
      cout << "Bus " << bus_item.first << ": ";
      for (const string& stop : bus_item.second) {
        cout << stop << " ";
      }
      cout << endl;
    }
  }
}

int main() {
  int q;
  cin >> q;

  map<string, vector<string>> buses_to_stops, stops_to_buses;

  for (int i = 0; i < q; ++i) {
    string operation_code;
    cin >> operation_code;

    if (operation_code == "NEW_BUS") {

      string bus;
      cin >> bus;
      int stop_count;
      cin >> stop_count;

      vector<string>& stops = buses_to_stops[bus];
      stops.resize(stop_count);

      for (string& stop : stops) {
        cin >> stop;
        stops_to_buses[stop].push_back(bus);
      }

    } else if (operation_code == "BUSES_FOR_STOP") {

      string stop;
      cin >> stop;
      PrintBusesForStop(stops_to_buses, stop);

    } else if (operation_code == "STOPS_FOR_BUS") {

      string bus;
      cin >> bus;
      PrintStopsForBus(buses_to_stops, stops_to_buses, bus);

    } else if (operation_code == "ALL_BUSES") {

      PrintAllBuses(buses_to_stops);

    }
  }

  return 0;
} */
