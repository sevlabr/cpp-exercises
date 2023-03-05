#include <cmath>
#include <iterator>
#include <iostream>
#include <map>
#include <set>
#include <string>

using namespace std;

class RouteManager {
public:
  void AddRoute(const int& start, const int& finish) {
    reachable_lists_[start].insert(finish);
    reachable_lists_[finish].insert(start);
  }
  int FindNearestFinish(const int& start, const int& finish) const {
    int result = abs(start - finish);
    if (reachable_lists_.count(start) < 1) {
      return result;
    }
    const set<int>& reachable_stations = reachable_lists_.at(start);
    if (!reachable_stations.empty()) {
    	auto it_lb = reachable_stations.lower_bound(finish);
    	if (it_lb != reachable_stations.end() && *it_lb == finish) {
    		return 0;
    	}
    	int min_distance;
    	if (it_lb == reachable_stations.begin()) {
    		min_distance = *it_lb - finish;
    		return min(result, min_distance);
    	} else if (it_lb == reachable_stations.end()) {
    		--it_lb;
    		min_distance = finish - *it_lb;
    		return min(result, min_distance);
    	}
    	auto it_prev = prev(it_lb);
    	min_distance = *it_lb - finish < finish - *it_prev ? *it_lb - finish : finish - *it_prev;
    	return min(result, min_distance);
    }
    return result;
  }
private:
  map<int, set<int>> reachable_lists_;
};


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

  RouteManager routes;

  int query_count;
  cin >> query_count;

  for (int query_id = 0; query_id < query_count; ++query_id) {
    string query_type;
    cin >> query_type;
    int start, finish;
    cin >> start >> finish;
    if (query_type == "ADD") {
      routes.AddRoute(start, finish);
    } else if (query_type == "GO") {
      cout << routes.FindNearestFinish(start, finish) << "\n";
    }
  }

  return 0;
}
