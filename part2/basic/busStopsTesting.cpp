#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>

using namespace std;

enum class QueryType {
  NewBus,
  BusesForStop,
  StopsForBus,
  AllBuses
};

struct Query {
  QueryType type;
  string bus;
  string stop;
  vector<string> stops;
};

QueryType GetQueryType(const string& query_name) {
	if (query_name == "NEW_BUS") {
		return QueryType::NewBus;
	} else if (query_name == "BUSES_FOR_STOP") {
		return QueryType::BusesForStop;
	} else if (query_name == "STOPS_FOR_BUS") {
		return QueryType::StopsForBus;
	}
	return QueryType::AllBuses;
}

istream& operator >> (istream& is, Query& q) {
  string query_name;
  is >> query_name;
  q.type = GetQueryType(query_name);
  switch(q.type) {
  case QueryType::NewBus: {
	  is >> q.bus;
	  int stop_count;
	  is >> stop_count;
	  q.stops.resize(stop_count);
	  for (string& stop : q.stops) {
		  is >> stop;
	  }
	  break;
  }
  case QueryType::BusesForStop:
	  is >> q.stop;
	  break;
  case QueryType::StopsForBus:
	  is >> q.bus;
	  break;
  case QueryType::AllBuses:
	  break;
  }
  return is;
}

struct BusesForStopResponse {
  vector<string> buses;
};

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

struct StopsForBusResponse {
  map<string, vector<string>> stops_to_buses;
  vector<string> stops;
};

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

struct AllBusesResponse {
  map<string, vector<string>> buses_to_stops;
};

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

class BusManager {
public:
  void AddBus(const string& bus, const vector<string>& stops) {
	buses_to_stops[bus] = stops;
	for (const string& stop : stops) {
		stops_to_buses[stop].push_back(bus);
	}
  }

  BusesForStopResponse GetBusesForStop(const string& stop) const {
    BusesForStopResponse r;
    if (stops_to_buses.count(stop) == 0) {
    	return r;
    }
    r.buses = stops_to_buses.at(stop);
    return r;
  }

  StopsForBusResponse GetStopsForBus(const string& bus) const {
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

  AllBusesResponse GetAllBuses() const {
	  AllBusesResponse r;
	  r.buses_to_stops = buses_to_stops;
	  return r;
  }

private:
  map<string, vector<string>> buses_to_stops;
  map<string, vector<string>> stops_to_buses;
};

int main() {
  int query_count;
  Query q;

  cin >> query_count;

  BusManager bm;
  for (int i = 0; i < query_count; ++i) {
    cin >> q;
    switch (q.type) {
    case QueryType::NewBus:
      bm.AddBus(q.bus, q.stops);
      break;
    case QueryType::BusesForStop:
      cout << bm.GetBusesForStop(q.stop) << endl;
      break;
    case QueryType::StopsForBus:
      cout << bm.GetStopsForBus(q.bus) << endl;
      break;
    case QueryType::AllBuses:
      cout << bm.GetAllBuses() << endl;
      break;
    }
  }

  return 0;
}

/*
#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>

using namespace std;

enum class QueryType {
  NewBus,
  BusesForStop,
  StopsForBus,
  AllBuses
};

struct Query {
  QueryType type;
  string bus;
  string stop;
  vector<string> stops;
};

istream& operator >> (istream& is, Query& q) {
  string typeStr;
  is >> typeStr;
  if (typeStr == "NEW_BUS") {
    q.type = QueryType::NewBus;
    is >> q.bus;
    int stop_count = 0;
    is >> stop_count;
    q.stops.resize(stop_count);
    for (auto& stop : q.stops) {
      is >> stop;
    }
  } else if (typeStr == "BUSES_FOR_STOP") {
    q.type = QueryType::BusesForStop;
    is >> q.stop;
  } else if (typeStr == "STOPS_FOR_BUS") {
    q.type = QueryType::StopsForBus;
    is >> q.bus;
  } else if (typeStr == "ALL_BUSES") {
    q.type = QueryType::AllBuses;
  }

  return is;
}

struct BusesForStopResponse {
  vector<string> buses;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
  if (r.buses.empty()) {
    os << "No stop";
  } else {
    for (const auto& bus : r.buses) {
      os << bus << " ";
    }
  }
  return os;
}

struct StopsForBusResponse {
  string bus;
  vector<pair<string, vector<string>>> stops_for_buses;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
  if (r.stops_for_buses.empty()) {
    os << "No bus";
  } else {
    bool first = true;
    for (const auto& stop_and_buses : r.stops_for_buses) {
      if (!first) {
        os << endl;
      }
      first = false;
      os << "Stop " << stop_and_buses.first << ":";
      if (stop_and_buses.second.size() == 1) {
        os << " no interchange";
      } else {
        for (const auto& bus : stop_and_buses.second) {
          if (bus != r.bus) {
            os << " " << bus;
          }
        }
      }
    }
  }
  return os;
}

struct AllBusesResponse {
  map<string, vector<string>> buses_to_stops;
};

ostream& operator << (ostream& os, const AllBusesResponse& r) {
  if (r.buses_to_stops.empty()) {
    os << "No buses";
  } else {
    bool first = true;
    for (const auto& bus_and_stops : r.buses_to_stops) {
      if (!first) {
        os << endl;
      }
      first = false;
      os << "Bus " << bus_and_stops.first << ":";
      for (const auto& stop : bus_and_stops.second) {
        os << " " << stop;
      }
    }
  }
  return os;
}

class BusManager {
public:
  void AddBus(const string& bus, const vector<string>& stops) {
    buses_to_stops.insert(make_pair(bus, stops));
    for (const auto& stop : stops) {
      stops_to_buses[stop].push_back(bus);
    }
  }

  BusesForStopResponse GetBusesForStop(const string& stop) const {
    if (stops_to_buses.count(stop) == 0) {
      return BusesForStopResponse{vector<string>()};
    } else {
      return BusesForStopResponse{stops_to_buses.at(stop)};
    }
  }

  StopsForBusResponse GetStopsForBus(const string& bus) const {
    vector<pair<string, vector<string>>> result;

    if (buses_to_stops.count(bus) > 0) {
      for (const auto& stop : buses_to_stops.at(bus)) {
        result.push_back(make_pair(stop, stops_to_buses.at(stop)));
      }
    }
    return StopsForBusResponse{bus, result};
  }

  AllBusesResponse GetAllBuses() const {
    return AllBusesResponse{buses_to_stops};
  }

private:
  map<string, vector<string>> buses_to_stops;
  map<string, vector<string>> stops_to_buses;
}; */
