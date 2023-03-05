#include <iostream>

using namespace std;

int main() {
	int a, b;
	cin >> a >> b;

	if (a == b) {
		if (a % 2 == 0) {
			cout << a;
		}
	} else {
		int i = a;
		while (i <= b) {
			if (i % 2 == 0) {
				cout << i << " ";
			}
			++i;
		}
	}
	return 0;
}

/* #include <iostream>

using namespace std;

int main() {
    int a, b;
    cin >> a >> b;
    for (int i = a; i <= b; ++i) {
        if (i % 2 == 0) {
            cout << i << ' ';
        }
    }
    return 0;
} */
