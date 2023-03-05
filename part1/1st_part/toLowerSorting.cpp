#include <locale>
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

int main() {
	int n;
	cin >> n;
	vector<string> strings(n);
	for (int i = 0; i < n; ++i) {
		cin >> strings[i];
	}
	sort(begin(strings), end(strings), [](string l, string r) {
		string l_low = "";
		string r_low = "";
		for (const auto& c : l) {
			l_low += tolower(c);
		}
		for (const auto& c : r) {
					r_low += tolower(c);
		}
		if (l_low < r_low) {
			return true;
		} else {
			return false;
		}
	});
	for (const string& s : strings) {
		cout << s << " ";
	}
	return 0;
}


/* #include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
  int n;
  cin >> n;
  vector<string> v(n);
  for (string& s : v) {
    cin >> s;
  }

  sort(begin(v), end(v),
       [](const string& l, const string& r) {
         return lexicographical_compare(
             begin(l), end(l),
             begin(r), end(r),
             [](char cl, char cr) { return tolower(cl) < tolower(cr); }
         );
       }
  );

  for (const string& s : v) {
    cout << s << ' ';
  }

  return 0;
} */
