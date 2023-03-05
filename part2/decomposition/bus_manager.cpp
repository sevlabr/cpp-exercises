#include "bus_manager.h"

void BusManager::AddBus(const string& bus, const vector<string>& stops) {
	buses_to_stops[bus] = stops;
	for (const string& stop : stops) {
		stops_to_buses[stop].push_back(bus);
	}
  }

BusesForStopResponse BusManager::GetBusesForStop(const string& stop) const {
	BusesForStopResponse r;
	if (stops_to_buses.count(stop) == 0) {
		return r;
	}
	r.buses = stops_to_buses.at(stop);
	return r;
}

StopsForBusResponse BusManager::GetStopsForBus(const string& bus) const {
	StopsForBusResponse r;
	if (buses_to_stops.count(bus) == 0) {
		return r;
	}
	vector<string>& stops = r.stops;
	for (const string& stop : buses_to_stops.at(bus)) {
		stops.push_back(stop);
		vector<string>& buses = r.stops_to_buses[stop];
		for (const string& interchange_bus : stops_to_buses.at(stop)) {
			if (interchange_bus != bus) {
				buses.push_back(interchange_bus);
			}
		}
	}
	return r;
}

AllBusesResponse BusManager::GetAllBuses() const {
	AllBusesResponse r;
	r.buses_to_stops = buses_to_stops;
	return r;
}
