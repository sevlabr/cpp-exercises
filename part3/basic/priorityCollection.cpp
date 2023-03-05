#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <set>
#include <utility>
#include <vector>

#include <list>
#include <map>
#include <cstdint>

using namespace std;

template <typename T>
class PriorityCollection {
public:
  using Id = uint64_t;

  PriorityCollection()
  	: elements(),
			elements_info(MAX_SIZE, {end(elements), 0}),
			element_to_add(0)
  {
  }

  Id Add(T object) {
  	auto it = elements.insert(begin(elements), move(object));
  	elements_info[element_to_add].first = it;
  	Id id = element_to_add;
  	priorities[0].insert(element_to_add);
  	++element_to_add;
  	return id;
  }

  template <typename ObjInputIt, typename IdOutputIt>
  void Add(ObjInputIt range_begin, ObjInputIt range_end,
           IdOutputIt ids_begin) {
  	for ( ; range_begin != range_end; ++range_begin, ++ids_begin) {
  		*ids_begin = Add(move(*range_begin));
  	}
  }

  bool IsValid(Id id) const {
  	return elements_info[id].first == end(elements) ? false : true;
  }

  const T& Get(Id id) const {
  	return *(elements_info[id].first);
  }

  void Promote(Id id) {
  	int current_priority = elements_info[id].second;
  	priorities[current_priority].erase(id);
  	if (priorities[current_priority].size() == 0) {
  		priorities.erase(current_priority);
  	}
  	++elements_info[id].second;
  	++current_priority;
  	priorities[current_priority].insert(id);
  }

  pair<const T&, int> GetMax() const {
  	pair<Id, int> max_info = FindMax();
  	return {Get(max_info.first), move(max_info.second)};
  }

  pair<T, int> PopMax() {
  	pair<Id, int> max_info = FindMaxAndDel();
  	auto it_max = elements_info[max_info.first].first;
  	T tmp = move(*it_max);
  	elements.erase(it_max);
  	elements_info[max_info.first].first = end(elements);
  	elements_info[max_info.first].second = 0;
  	return {move(tmp), move(max_info.second)};
  }

  void PrintFields() {
  	cerr << "Elements size: " << elements.size() << '\n';
  	cerr << "Elements info size: " << elements_info.size() << '\n';
  	cerr << "Element to add: " << element_to_add << '\n';
  	cerr << priorities << '\n';
  }

private:
  static const size_t MAX_SIZE = 1'000'000;

  list<T> elements;

  vector<pair<typename list<T>::iterator, int>> elements_info;
  Id element_to_add;

  map<int, set<Id>> priorities;

  pair<Id, int> FindMaxAndDel() {
  	auto it_max = prev(end(priorities));
  	int max_priority = it_max->first;
  	set<Id>& ids_with_max_priority = it_max->second;
  	auto it_max_id = prev(end(ids_with_max_priority));
  	Id id_max = *it_max_id;
  	ids_with_max_priority.erase(it_max_id);
  	if (ids_with_max_priority.size() == 0) {
  		priorities.erase(max_priority);
  	}
  	return {id_max, max_priority};
  }

  pair<Id, int> FindMax() const {
    	auto it_max = prev(end(priorities));
    	int max_priority = it_max->first;
    	auto it_max_id = prev(end(it_max->second));
    	Id id_max = *it_max_id;
    	return {id_max, max_priority};
    }
};

class StringNonCopyable : public string {
public:
  using string::string;
  StringNonCopyable(const StringNonCopyable&) = delete;
  StringNonCopyable(StringNonCopyable&&) = default;
  StringNonCopyable& operator=(const StringNonCopyable&) = delete;
  StringNonCopyable& operator=(StringNonCopyable&&) = default;
};

void TestNoCopy() {
  PriorityCollection<StringNonCopyable> strings;
  const auto white_id = strings.Add("white");
  const auto yellow_id = strings.Add("yellow");
  const auto red_id = strings.Add("red");

  cerr << "Adding OK" << endl;

  strings.Promote(yellow_id);
  for (int i = 0; i < 2; ++i) {
    strings.Promote(red_id);
  }
  strings.Promote(yellow_id);
  cerr << "Promoting OK" << endl;
  {
  	//strings.PrintFields();
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "red");
    ASSERT_EQUAL(item.second, 2);
  }
  cerr << "1st Pop is OK" << endl;
  {
  	//strings.PrintFields();
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "yellow");
    ASSERT_EQUAL(item.second, 2);
  }
  cerr << "2nd Pop is OK" << endl;
  {
  	//strings.PrintFields();
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "white");
    ASSERT_EQUAL(item.second, 0);
  }
  cerr << "3rd Pop is OK" << endl;
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestNoCopy);
  return 0;
}
