#include <iostream>
#include <string>

using namespace std;

class ReversibleString {
public:
	ReversibleString() {}
	ReversibleString(const string& s) {
		strng = s;
	}
	void Reverse() {
		// reverse(begin(strng), end(strng)); #include <algorithm>
		string tmp = strng;
		int size = strng.length();
		for(int i = size - 1; i >= 0; --i) {
			strng[i] = tmp[size - i - 1];
		}
	}
	string ToString() const {
		return strng;
	}

private:
	string strng;
};

int main() {
  ReversibleString s("live");
  s.Reverse();
  cout << s.ToString() << endl;

  s.Reverse();
  const ReversibleString& s_ref = s;
  string tmp = s_ref.ToString();
  cout << tmp << endl;

  ReversibleString empty;
  cout << '"' << empty.ToString() << '"' << endl;

  return 0;
}

