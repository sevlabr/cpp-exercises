#include <iostream>
#include <fstream>
using namespace std;

void MakeHead(istream& document, const string& name) {
	const int BATCH_SIZE = 100;

	ofstream part(name + ".txt");
	int line_count = 0;
	for (string line; getline(document, line) && line_count < BATCH_SIZE; ++line_count) {
		part << line << '\n';
	}
}

int main() {
	ifstream check("check.txt");
	MakeHead(check, "head");
	return 0;
}
