#include <set>
#include <map>
#include <string>
#include <iostream>

using namespace std;

set<string> BuildMapValuesSet(const map<int, string>& m) {
	set<string> strings;
	for (const auto& item : m) {
		strings.insert(item.second);
	}
	return strings;
}

int main() {
	set<string> values = BuildMapValuesSet({
	    {1, "odd"},
	    {2, "even"},
	    {3, "odd"},
	    {4, "even"},
	    {5, "odd"}
	});

	for (const string& value : values) {
	  cout << value << endl;
	}
	return 0;
}
