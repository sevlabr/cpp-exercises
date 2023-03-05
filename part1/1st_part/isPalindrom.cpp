#include <iostream>
#include <string>

using namespace std;

bool IsPalindrom(string s) {
	if (s.size() == 0) {
		return true;
	} else {
		int size = s.size();
		for(int i = 0; i <= (size/2 + 1); ++i) {
			if (s[i] == s[size - (i+1)]) {
				if (i == size/2) {
					return true;
				}
			} else {
				return false;
			}
		}
	}
}

int main() {
	string s;
	cin >> s;
	cout << IsPalindrom(s);
	return 0;
}

/* bool IsPalindrom(string s) {
    for (int i = 0; i < s.size() / 2; ++i) {
        if (s[i] != s[s.size() - i - 1]) {
            return false;
        }
    }
    return true;
} */
