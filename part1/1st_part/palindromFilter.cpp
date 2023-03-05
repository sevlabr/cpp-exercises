#include <iostream>
#include <string>
#include <vector>

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

vector<string> PalindromFilter(vector<string> words, int minLength) {
	vector<string> FilteredWords;
	for (auto s : words) {
		if (s.size() >= minLength && IsPalindrom(s) == true) {
			FilteredWords.push_back(s);
		}
	}
	return FilteredWords;
}

int main() {
	vector<string> words;
	int n;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		string word;
		cin >> word;
		words.push_back(word);
	}
	int minLength;
	cin >> minLength;
	vector<string> FilteredWords = PalindromFilter(words, minLength);
	for (auto s : FilteredWords) {
		cout << s << " ";
	}
	return 0;
}


/*
bool IsPalindrom(string s) {
  for (size_t i = 0; i < s.size() / 2; ++i) {
    if (s[i] != s[s.size() - i - 1]) {
      return false;
    }
  }

  return true;
}

vector<string> PalindromFilter(vector<string> words, int min_length) {
  vector<string> result;
  for (auto s : words) {
    if (s.size() >= min_length && IsPalindrom(s)) {
      result.push_back(s);
    }
  }

  return result;
} */
