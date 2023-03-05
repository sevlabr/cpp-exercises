#include <string>
#include <set>
#include <iostream>

using namespace std;

int main() {

	int q;
	cin >> q;

	set<set<string>> synonyms;

	for (int i = 0; i < q; ++i) {

		string operation_code;
		cin >> operation_code;

		if (operation_code == "ADD") {
			string word1, word2;
			cin >> word1 >> word2;
			set<string> words;
			words.insert(word1);
			words.insert(word2);
			synonyms.insert(words);

		} else if (operation_code == "COUNT") {
			string word;
			cin >> word;
			int count = 0;
			for (const set<string>& pair : synonyms) {
				if (pair.count(word) == 1) {
					++count;
				}
			}
			cout << count << endl;

		} else if (operation_code == "CHECK") {
			string word1, word2;
			cin >> word1 >> word2;
			set<string> words;
			words.insert(word1);
			words.insert(word2);
			if (synonyms.count(words) == 1) {
				cout << "YES" << endl;
			} else {
				cout << "NO" << endl;
			}
		}

	}
	return 0;
}
