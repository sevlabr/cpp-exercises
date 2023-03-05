/*#include "test_runner.h"

#include <iostream>
#include <string>
#include <cstdint>
#include <stdexcept>
#include <queue>
#include <map>
#include <utility>

using namespace std;

// Q(10^5) - queries, T(2*10^18) - time, S(12) - len(hotel),
// C(10^9) - clients, R(10^3) - rooms

class Hotel {
public:
	Hotel()
		: total_rooms(0),
			total_clients(0),
			clients_book_count(),
			booking_log() {}

	void Adjust() {
		total_rooms -= booking_log.front().second;
		int client_id = booking_log.front().first;
		auto it_client = clients_book_count.lower_bound(client_id);
		--it_client->second;
		if (it_client->second == 0) {
			--total_clients;
		}
		booking_log.pop();
	}

	void AddClient(const int64_t& time, const int& client_id,
									const int& room_count) {
		booking_log.push({client_id, room_count});
		total_rooms += room_count;
		auto it_client = clients_book_count.lower_bound(client_id);
		if (it_client != end(clients_book_count) &&
				it_client->first == client_id) {
			if (it_client->second == 0) {
				++total_clients;
			}
			++it_client->second;
		} else {
			++total_clients;
			clients_book_count.insert(it_client, {client_id, 1});
		}
	}

	int ClientsCount() const {
		return total_clients;
	}

	int64_t RoomsCount() const {
		return total_rooms;
	}

private:
	int64_t total_rooms;
	int total_clients;

	map<int, int> clients_book_count;
	queue<pair<int, int>> booking_log;
};


class BookingManager {
public:
	void Book(const int64_t& time, const string& hotel_name,
						const int& client_id, const int& room_count) {
		Adjust(time);
		events.push({time, hotel_name});
		hotels[hotel_name].AddClient(time, client_id, room_count);
	}

	int ClientsCount(const string& hotel_name) const {
		try {
			return hotels.at(hotel_name).ClientsCount();
		} catch (const out_of_range&) {
			return 0;
		}
	}

	int64_t RoomsCount(const string& hotel_name) const {
		try {
			return hotels.at(hotel_name).RoomsCount();
		} catch (const out_of_range&) {
			return 0;
		}
	}

private:
	static const int SECS_IN_DAY = 86400;

	map<string, Hotel> hotels;
	queue<pair<int64_t, string>> events;

	void Adjust(const int64_t& current_time) {
		while (!events.empty() && current_time - events.front().first >= SECS_IN_DAY) {
			Hotel& clients = hotels[events.front().second];
			clients.Adjust();
			events.pop();
		}
	}
};

void Test() {
	BookingManager bm;
	bm.Book(0, "a", 1, 1);
	ASSERT_EQUAL(bm.ClientsCount("a"), 1);
	ASSERT_EQUAL(bm.RoomsCount("a"), 1);
	bm.Book(86400, "a", 1, 2);
	ASSERT_EQUAL(bm.ClientsCount("a"), 1);
	ASSERT_EQUAL(bm.RoomsCount("a"), 2);
	bm.Book(86400 * 2, "a", 1, 5);
	ASSERT_EQUAL(bm.RoomsCount("a"), 5);
	ASSERT_EQUAL(bm.ClientsCount("a"), 1);
}

void TestAll() {
	TestRunner tr;
	RUN_TEST(tr, Test);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	//TestAll();

	BookingManager bm;

	int query_count;
	cin >> query_count;
	for (int query = 0; query < query_count; ++query) {
		string query_type;
		cin >> query_type;
		if (query_type == "BOOK") {
			int64_t time;
			string hotel_name;
			int client_id, room_count;
			cin >> time >> hotel_name >> client_id >> room_count;
			bm.Book(time, hotel_name, client_id, room_count);
		} else if (query_type == "CLIENTS") {
			string hotel_name;
			cin >> hotel_name;
			cout << bm.ClientsCount(hotel_name) << '\n';
		} else if (query_type == "ROOMS") {
			string hotel_name;
			cin >> hotel_name;
			cout << bm.RoomsCount(hotel_name) << '\n';
		}
	}
	return 0;
} */

// My 2nd solution (need to optimize):
/*class Hotel {
public:
	Hotel()
		: total_rooms(0),
			total_clients(0),
			booking_log() {}

	void Adjust(const int64_t& current_time) {
		auto it_begin = begin(booking_log);
		while (it_begin != end(booking_log) &&
				current_time - it_begin->first >= SECS_IN_DAY) {
			total_rooms -= (it_begin->second).second;
			--clients_book_count[(it_begin->second).first];
			if (clients_book_count[(it_begin->second).first] == 0) {
				--total_clients;
			}
			advance(it_begin, 1);
		}
		booking_log.erase(begin(booking_log), it_begin);
	}

	void AddClient(const int64_t& time, const int& client_id,
									const int& room_count) {
		booking_log[time] = make_pair(client_id, room_count);
		total_rooms += room_count;
		if (clients_book_count[client_id] == 0) {
			++total_clients;
		}
		++clients_book_count[client_id];
	}

	int ClientsCount() const {
		return total_clients;
	}

	int64_t RoomsCount() const {
		return total_rooms;
	}

private:
	static const int SECS_IN_DAY = 86400;

	int64_t total_rooms;
	int total_clients;

	map<int, int> clients_book_count;
	map<int64_t, pair<int, int>> booking_log;
};


class BookingManager {
public:
	void Book(const int64_t& time, const string& hotel_name,
						const int& client_id, const int& room_count) {
		Adjust(time);
		events.push(time);
		hotels[hotel_name].AddClient(time, client_id, room_count);
	}

	int ClientsCount(const string& hotel_name) const {
		try {
			return hotels.at(hotel_name).ClientsCount();
		} catch (const out_of_range&) {
			return 0;
		}
	}

	int64_t RoomsCount(const string& hotel_name) const {
		try {
			return hotels.at(hotel_name).RoomsCount();
		} catch (const out_of_range&) {
			return 0;
		}
	}

private:
	static const int SECS_IN_DAY = 86400;

	map<string, Hotel> hotels;
	queue<int64_t> events;

	void Adjust(const int64_t& current_time) {
		if (!events.empty() && current_time - events.front() >= SECS_IN_DAY) {
			for (auto& [hotel, clients] : hotels) {
				clients.Adjust(current_time);
			}
			while (!events.empty() && current_time - events.front() >= SECS_IN_DAY) {
				events.pop();
			}
		}
	}
}; */


// My 1st solution (slow):
/*class Hotel {
public:
	Hotel()
		: total_rooms(0),
			clients_rooms(),
			events_clients() {}

	// Q*log(C) + log(Q) + Q
	void Adjust(const int64_t& current_time) {
		auto it_begin = begin(events_clients);
		// Q*log(C)
		while (it_begin != end(events_clients) &&
				current_time - it_begin->first >= SECS_IN_DAY) {
			int client_id = it_begin->second;
			total_rooms -= clients_rooms[client_id]; // log(C)
			advance(it_begin, 1);
		}
		// log(Q) + Q
		events_clients.erase(begin(events_clients), it_begin);
	}

	// log(T) + log(C)
	void AddClient(const int64_t& time, const int& client_id,
									const int& room_count) {
		events_clients[time] = client_id; // log(T)
		clients_rooms[client_id] = room_count; // log(C)
		total_rooms += room_count; // O(1)
	}

	int ClientsCount() const {
		return clients_rooms.size();
	}

	int64_t RoomsCount() const {
		return total_rooms;
	}

private:
	static const int SECS_IN_DAY = 86400;

	int64_t total_rooms;

	map<int, int> clients_rooms;
	map<int64_t, int> events_clients;
};

class BookingManager {
public:
	void Book(const int64_t& time, const string& hotel_name,
						const int& client_id, const int& room_count) {
		Adjust(time);
		events.push(time);
		hotels[hotel_name].AddClient(time, client_id, room_count); // S * log(Q) * (log(T) + log(C)) ~ 10^4
		//cout << "Booking" << endl;
	}

	int ClientsCount(const string& hotel_name) const {
		try {
			return hotels.at(hotel_name).ClientsCount();
		} catch (const out_of_range&) {
			return 0;
		}
	}

	int64_t RoomsCount(const string& hotel_name) const {
		try {
			return hotels.at(hotel_name).RoomsCount();
		} catch (const out_of_range&) {
			return 0;
		}
	}

private:
	static const int SECS_IN_DAY = 86400;

	map<string, Hotel> hotels;
	queue<int64_t> events;

	void Adjust(const int64_t& current_time) {
		if (!events.empty() && current_time - events.front() >= SECS_IN_DAY) {
			// Q
			for (auto& [hotel, clients] : hotels) {
				clients.Adjust(current_time); // Q*log(C) + log(Q) + Q
			}
			while (!events.empty() && current_time - events.front() >= SECS_IN_DAY) {
				events.pop();
			}
		}
	}
}; */
