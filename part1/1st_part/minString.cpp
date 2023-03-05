#include <iostream>
#include <string>
using namespace std;

int main() {
	string a, b, c;
	string m;
	cin >> a >> b >> c;
	if (a < b) {
		m = a;
	} else {
		m = b;
	}
	if (c < m) {
		m = c;
	}
	cout << m;
	return 0;
}

/*
#include <iostream>
#include <string>

using namespace std;

int main() {
  string a, b, c;
  cin >> a >> b >> c;

  if (a <= b && a <= c) {
    cout << a;
  } else if (b <= a && b <= c) {
    cout << b;
  } else {
    cout << c;
  }
  return 0;
} */
