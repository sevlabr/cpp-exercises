#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

/*
template <typename T>
vector<T> FindGreaterElements(const set<T>& elements, const T& border) {
  auto it = begin(elements);
  while (it != end(elements) && *it <= border) {
  	++it;
  }
  return {it, end(elements)};
} */

template <typename T>
vector<T> FindGreaterElements(const set<T>& elements, const T& border) {
	const auto it_border = find_if(
			begin(elements), end(elements),
			[border](const T& element) {
			return element > border;
	});

	return vector<T>(it_border, end(elements));
}

int main() {
  for (int x : FindGreaterElements(set<int>{1, 5, 7, 8}, 0)) {
    cout << x << " ";
  }
  cout << endl;

  string to_find = "Python";
  cout << FindGreaterElements(set<string>{"C", "C++"}, to_find).size() << endl;

  cout << FindGreaterElements(set<int>{}, 5).size() << endl;
  return 0;
}
