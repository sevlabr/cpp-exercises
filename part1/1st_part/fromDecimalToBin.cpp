#include <iostream>
#include <vector>

using namespace std;

int main() {
	int n;
	int radix = 2;
	cin >> n;
	vector<int> result;
	while (n >= radix) {
		result.push_back(n % radix);
		n /= radix;
	}
	result.push_back(n);
	int res_size = result.size();
	for (int i = res_size - 1; i >= 0; --i) {
		cout << result[i];
	}
	return 0;
}

/* #include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    vector<int> bits;

    cin >> n;
    while (n > 0) {
        bits.push_back(n % 2);
        n /= 2;
    }

    for (int i = bits.size() - 1; i >= 0; --i) {
        cout << bits[i];
    }
    return 0;
} */
