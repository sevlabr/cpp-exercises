#include "test_runner.h"
#include <string>
#include <string_view>
#include <map>

using namespace std;

class Translator {
public:
  void Add(string_view source, string_view target) {
  	string source_copy = string(source);
  	string target_copy = string(target);
  	source_dict[source_copy] = target;
  	target_dict[target_copy] = source;

  	source_dict[source_copy] = target_dict.lower_bound(target_copy)->first;
  	target_dict[target_copy] = source_dict.lower_bound(source_copy)->first;
  }

  string_view TranslateForward(string_view source) const {
  	string_view result;
  	auto it = source_dict.lower_bound(string(source));
  	if (it != source_dict.end() && it->first == source) {
  		return it->second;
  	} else {
  		return result;
  	}
  }

  string_view TranslateBackward(string_view target) const {
  	string_view result;
  	auto it = target_dict.lower_bound(string(target));
  	if (it != target_dict.end() && it->first == target) {
  		return it->second;
  	} else {
  		return result;
  	}
  }

  void Print() const {
  	cout << "Source:" << endl;
  	cout << source_dict << endl;
  	cout << "Target:" << endl;
  	cout << target_dict << endl;
  }

private:
  map<string, string_view> source_dict;
  map<string, string_view> target_dict;
};


void TestSimple() {
  Translator translator;
  translator.Add(string("okno"), string("window"));
  translator.Add(string("stol"), string("table"));

  ASSERT_EQUAL(translator.TranslateForward("okno"), "window");
  ASSERT_EQUAL(translator.TranslateBackward("table"), "stol");
  //translator.Print();
  ASSERT_EQUAL(translator.TranslateBackward("stol"), "");
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSimple);
  return 0;
}
