#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<string> ReadFile(const string& path) {
	ifstream input(path);
	vector<string> result;
	if (input.is_open()) {
		string line;
		while(getline(input, line)) {
			result.push_back(line);
		}
	}
	return result;
}

void WriteToFile(const vector<string>& input, const string& output_path) {
	ofstream output(output_path);
	for (const auto& s : input) {
		output << s << endl;
	}
}

int main() {
	string input_path = "input.txt";
	vector<string> input = ReadFile(input_path);
	string output_path = "output.txt";
	WriteToFile(input, output_path);
	return 0;
}
