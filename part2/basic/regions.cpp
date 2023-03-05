#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <tuple>

using namespace std;

enum class Lang {
  DE, FR, IT
};

struct Region {
  string std_name;
  string parent_std_name;
  map<Lang, string> names;
  int64_t population;
};

/*
int FindMaxRepetitionCount(const vector<Region>& regions) {
	unsigned result = 0;
	for (const Region& region : regions) {
		unsigned count = 0;
		for (size_t i = 0; i < regions.size(); ++i) {
			count += tie(region.std_name, region.parent_std_name, region.names, region.population) ==
				tie(regions[i].std_name, regions[i].parent_std_name, regions[i].names, regions[i].population);
		}
		if (count > result) {
			result = count;
		}
	}
	return result;
}
*/

bool operator < (const Region& lhs, const Region& rhs) {
	return tie(lhs.std_name, lhs.parent_std_name, lhs.names, lhs.population) <
			tie(rhs.std_name, rhs.parent_std_name, rhs.names, rhs.population);
}

/*
int FindMaxRepetitionCount(const vector<Region>& regions) {
	unsigned result = 0;
	map<Region, unsigned> count;
	for (const Region& region : regions) {
		++count[region];
	}
	for (const auto& [region, count_number] : count) {
		if (count_number > result) {
			result = count_number;
		}
	}
	return result;
}
*/

int FindMaxRepetitionCount(const vector<Region>& regions) {
	unsigned result = 0;
	map<Region, unsigned> count;
	for (const Region& region : regions) {
			result = max(result, ++count[region]);
	}
	return result;
}


int main() {
  cout << FindMaxRepetitionCount({
      {
          "Moscow",
          "Russia",
          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
          89
      }, {
          "Russia",
          "Eurasia",
          {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
          89
      }, {
          "Moscow",
          "Russia",
          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
          89
      }, {
          "Moscow",
          "Russia",
          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
          89
      }, {
          "Russia",
          "Eurasia",
          {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
          89
      },
  }) << endl;

  cout << FindMaxRepetitionCount({
      {
          "Moscow",
          "Russia",
          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
          89
      }, {
          "Russia",
          "Eurasia",
          {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
          89
      }, {
          "Moscow",
          "Russia",
          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou deux"}, {Lang::IT, "Mosca"}},
          89
      }, {
          "Moscow",
          "Toulouse",
          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
          89
      }, {
          "Moscow",
          "Russia",
          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
          31
      },
  }) << endl;

  return 0;
}

