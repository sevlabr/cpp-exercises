#include "responses.h"

#include <iostream>

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
	if (r.buses.empty()) {
		os << "No stop";
		return os;
	}
	for (const auto& bus : r.buses) {
		os << bus;
		if (bus != r.buses.back()) {
			os << " ";
		}
	}
	return os;
}

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
	if (r.stops_to_buses.empty()) {
		os << "No bus";
	}
	for (const string& stop : r.stops) {
		const vector<string>& buses = r.stops_to_buses.at(stop);
		os << "Stop " << stop << ": ";
		if (buses.empty()) {
			os << "no interchange";
		} else {
			for (const string& bus : buses) {
				os << bus;
				if (bus != buses.back()) {
					os << " ";
				}
			}
		}
		if (stop != r.stops.back()) {
			os << endl;
		}
	}
	return os;
}

ostream& operator << (ostream& os, const AllBusesResponse& r) {
	if (r.buses_to_stops.empty()) {
		os << "No buses";
		return os;
	}
	int size = static_cast<int>(r.buses_to_stops.size());
	int count = 0;
	for (const auto& [bus, stops] : r.buses_to_stops) {
		os << "Bus " << bus << ": ";
		for (const string& stop : stops) {
			os << stop;
			if (stop != stops.back()) {
				os << " ";
			}
		}
		++count;
		if (count != size) {
			os << endl;
		}
	}
	return os;
}
