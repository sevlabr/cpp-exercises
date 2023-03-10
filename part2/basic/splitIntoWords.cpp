#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

/* vector<string> SplitIntoWords(const string& str) {
  vector<string> result;

  auto str_begin = begin(str);
  const auto str_end = end(str);

  while (true) {

    auto it = find(str_begin, str_end, ' ');

    result.push_back(string(str_begin, it));

    if (it == str_end) {
      break;
    } else {
      str_begin = it + 1;
    }

  }

  return result;
} */

vector<string> SplitIntoWords(const string& s) {
	vector<string> result;
	auto it_begin = begin(s);
	while (it_begin != end(s)) {
		auto it_end = find(it_begin, end(s), ' ');
		result.push_back(string(it_begin, it_end));
		it_begin = it_end;
		if (it_end != end(s)) {
			++it_begin;
		}
	}
	return result;
}

int main() {
  string s = "C Cpp Java Python";

  vector<string> words = SplitIntoWords(s);
  cout << words.size() << " ";
  for (auto it = begin(words); it != end(words); ++it) {
    if (it != begin(words)) {
      cout << "/";
    }
    cout << *it;
  }
  cout << endl;

  return 0;
}
