#include <iostream>

using namespace std;

int main() {
	double n, a, b, x, y;
	cin >> n >> a >> b >> x >> y;

	if (n >= 0) {
		if (n > a && n <= b) {
			cout << n* (1 - x/100.0) << endl;
		} else if (n > b) {
			cout << n* (1 - y/100.0) << endl;
		} else {
			cout << n << endl;
		}
	}
	return 0;
}

/*
#include <iostream>

using namespace std;

int main() {
    double n, a, b, x, y;
    cin >> n >> a >> b >> x >> y;
    if (n > b) {
        n *= (1 - y / 100);
    } else if (n > a) {
        n *= (1 - x / 100);
    }
    cout << n;

    return 0;
} */
