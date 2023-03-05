#include <iostream>
#include <string>

using namespace std;

int main() {
	string s;
	cin >> s;
	int i = 0;
	int position = 0;
	for (auto c : s) {
		if (c == 'f') {
			++i;
		}
		if (i == 2) {
			break;
		}
		++position;
	}
	if (i == 0) {
		cout << -2;
	} else if (i == 1) {
		cout << -1;
	} else {
		cout << position;
	}
	return 0;
}


/*
#include <iostream>
#include <string>

using namespace std;

int main() {
  string s;
  cin >> s;

  int result = -2;

  for (int i = 0; i < s.size(); ++i) {
    if (s[i] == 'f') {

      if (result == -2) {
        result = -1;

      } else if (result == -1) {
        result = i;
        break;
      }

    }
  }

  cout << result;

  return 0;
}
*/
