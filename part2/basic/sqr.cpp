#include <iostream>
#include <vector>
#include <map>
#include <utility>
//#include <type_info>
#include <string>

using namespace std;

/*
enum class CollectionName {
	VECTOR,
	MAP,
	PAIR
};

template <typename T> Sqr(const T& val);
template <typename Collection> Collection SqrC(const Collection& c, const CollectionName& name);
template <typename T> vector<T> Sqr(const vector<T>& v);
template <typename Key, typename Value> map<Key, Value> Sqr(const map<Key, Value>& m);
template <typename First, typename Second> pair<First, Second> Sqr(const pair<First, Second>& p);

template <typename T>
Sqr(const T& val) {
	return val*val;
}

template <typename T>
vector<T> Sqr(const vector<T>& v) {
	return SqrC(v, CollectionName::VECTOR);
}

template <typename Key, typename Value>
map<Key, Value> Sqr(const map<Key, Value>& m) {
	return SqrC(m, CollectionName::MAP);
}

template <typename First, typename Second>
pair<First, Second> Sqr(const pair<First, Second>& p) {
	return SqrC(p, CollectionName::PAIR);
}

template <typename Collection>
Collection SqrC(const Collection& c, const CollectionName& name) {
	Collection result(c.size());
	int i = 0;
	for (const auto& item : c) {
		switch(name) {
		case CollectionName::VECTOR:
			result[i] = Sqr(item);
			++i;
			break;
		case CollectionName::MAP:
			result[item.first] = Sqr(result.second);
			break;
		case CollectionName::PAIR:
			result.first = Sqr(c.first);
			result.second = Sqr(c.second);
			break;
		}
	}
	return result;
} */

/*
template <typename T> T Sqr(const T& val);
template <typename T> vector<T> Sqr(const vector<T>& v);
template <typename Key, typename Value> map<Key, Value> Sqr(const map<Key, Value>& m);
template <typename First, typename Second> pair<First, Second> Sqr(const pair<First, Second>& p);

template <typename T>
T Sqr(const T& val) {
	return val*val;
}

template <typename T>
vector<T> Sqr(const vector<T>& v) {
	vector<T> result;
	for (const auto& item : v) {
		result.push_back(Sqr(item));
	}
	return result;
}

template <typename First, typename Second>
pair<First, Second> Sqr(const pair<First, Second>& p) {
	return {Sqr(p.first), Sqr(p.second)};
}

template <typename Key, typename Value>
map<Key, Value> Sqr(const map<Key, Value>& m) {
	map<Key, Value> result;
	Value value;
	for (const auto& item : m) {
		result[item.first] = Sqr(item.second);
	}
	return result;
}
*/


// working variant

template <typename Collection> Collection Sqr(const Collection& c);

template <typename T> vector<T> operator * (const vector<T>& lhs, const vector<T>& rhs);

template <typename Key, typename Value>
map<Key, Value> operator * (const map<Key, Value>& lhs, const map<Key, Value>& rhs);

template <typename First, typename Second>
pair<First, Second> operator * (const pair<First, Second>& lhs, const pair<First, Second>& rhs);

template <typename T>
vector<T> operator * (const vector<T>& lhs, const vector<T>& rhs) {
	int size = lhs.size();
	vector<T> result(size);
	for (int i = 0; i < size; ++i) {
		result[i] = lhs[i]*rhs[i];
	}
	return result;
}

template <typename Key, typename Value>
map<Key, Value> operator * (const map<Key, Value>& lhs, const map<Key, Value>& rhs) {
	map<Key, Value> result;
	for (const auto& [key, value] : lhs) {
		result[key] = value*rhs.at(key);
	}
	return result;
}

template <typename First, typename Second>
pair<First, Second> operator * (const pair<First, Second>& lhs, const pair<First, Second>& rhs) {
	pair<First, Second> result;
	result.first = lhs.first*rhs.first;
	result.second = lhs.second*rhs.second;
	return result;
}

template <typename Collection>
Collection Sqr(const Collection& c) {
	return c*c;
}


int main() {
	vector<int> v = {1, 2, 3};
	cout << "vector:";
	for (int x : Sqr(v)) {
		cout << ' ' << x;
	}
	cout << endl;

	map<int, pair<int, int>> map_of_pairs = {
			{4, {2, 2}},
			{7, {4, 3}}
	};
	cout << "map of pairs:" << endl;
	for (const auto& x : Sqr(map_of_pairs)) {
		cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
	}

	return 0;
}


/*
template<typename T>
T Sqr(T value);

template<typename T>
vector<T> Sqr(const vector<T>& value);

template<typename K, typename V>
map<K, V> Sqr(const map<K, V>& value);

template<typename K, typename V>
pair<K, V> Sqr(const pair<K, V>& value);

template<typename T>
T Sqr(T value) {
  return value * value;
}

template<typename T>
vector<T> Sqr(const vector<T>& value) {
  vector<T> result;
  for (const T& x : value) {
    result.push_back(Sqr(x));
  }

  return result;
}

template<typename K, typename V>
map<K, V> Sqr(const map<K, V>& value) {
  map<K, V> result;
  for (const auto& element : value) {
    result[element.first] = Sqr(element.second);
  }
  return result;
}

template<typename K, typename V>
pair<K, V> Sqr(const pair<K, V>& value) {
  return {Sqr(value.first), Sqr(value.second)};
} */
