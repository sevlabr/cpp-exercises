#include <iostream>
#include <fstream>

using namespace std;

void PrintFile(const string& path) {
	ifstream input(path);
	if (input.is_open()) {
		string line;
		while (getline(input, line)) {
			cout << line << endl;
		}
	}
}

int main() {
	string path = "input.txt";
	PrintFile(path);
	return 0;
}
