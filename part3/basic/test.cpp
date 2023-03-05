/*#include <vector>
#include <iostream>

using namespace std;

template <typename Iterator>
struct IteratorRange {
public:
	IteratorRange(Iterator begin, Iterator end)
		: first(begin)
		, last(end) {}
	Iterator begin() { return first; }
	Iterator end() { return last; }
private:
	Iterator first;
	Iterator last;
};

template <typename C>
auto Head(C& v, const size_t& top) {
	return IteratorRange{v.begin(), v.begin() + min(v.size(), top)};
}

int main() {
	vector<int> nums = {1, 2, 3, 4};
	for (const auto& num : Head(nums, 3)) {
		cout << num;
	}
	cout << endl;
	const vector<int> c_nums = {1, 2, 3, 4};
	for (const auto& num : Head(c_nums, 3)) {
		cout << num;
	}
	cout << endl;
	return 0;
} */

//#include <string_view>
//
//using namespace std;
//
//class Translator {
//public:
//	string_view Add (string_view sv);
//};
//
//int main() {
//	return 0;
//	string_view sv;
//}


#include <iostream>

using namespace std;

int main() {
	size_t item_size = 100;
	int item_num = 120;
	int result = item_num / item_size;
	cout << result;
	return 0;
}
