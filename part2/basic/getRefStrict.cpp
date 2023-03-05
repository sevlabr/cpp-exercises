#include <iostream>
#include <map>
#include <string>
#include <exception>

using namespace std;

template <typename K, typename V>
V& GetRefStrict(map<K, V>& m, const K& key) {
	if (m.count(key) == 0) {
		throw runtime_error("");
	}
	return m.at(key);
}

int main() {
	map<int, string> m = {{0, "value"}};
	string& item = GetRefStrict(m, 0);
	item = "newvalue";
	cout << m[0] << endl;
	return 0;
}

/* #include <map>
#include <stdexcept>

template<typename KeyType, typename ValueType>
ValueType& GetRefStrict(map<KeyType, ValueType>& input_map, KeyType key) {
    if (input_map.count(key) == 0) {
        throw runtime_error("no such key in dictionary");
    }
    return input_map[key];
} */
