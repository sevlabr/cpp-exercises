/* map<string, set<string>>
set<map<string, string>> */
#include <iostream>
#include <set>
#include <map>
#include <string>

using namespace std;

int main() {
	int q;
	cin >> q;
	map<string, set<string>> synonyms;
	for (int i = 0; i < q; ++i) {

		string operation_code;
		cin >> operation_code;

		if (operation_code == "ADD") {
			string word1, word2;
			cin >> word1 >> word2;
			synonyms[word1].insert(word2);
			synonyms[word2].insert(word1);

		} else if (operation_code == "COUNT") {
			string word;
			cin >> word;
			cout << synonyms[word].size() << endl;

		} else if (operation_code == "CHECK") {
			string word1, word2;
			cin >> word1 >> word2;
			if (synonyms[word1].count(word2) == 1) {
				cout << "YES" << endl;
			} else {
				cout << "NO" << endl;
			}

		}

	}

	return 0;
}

