#include "query.h"

#include <iostream>

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
