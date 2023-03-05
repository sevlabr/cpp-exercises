#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int main() {
	ifstream input("input.txt");
	int M, N;
	input >> M >> N;
	for (int i = 0; i < M; ++i) {
		for (int j = 0; j < N; ++j) {
			int number;
			input >> number;
			input.ignore(1);
			cout << setw(10) << number;
			if (j < N - 1) {
				cout << " ";
			}
		}
		if (i < M - 1) {
			cout << endl;
		}
	}
	return 0;
}
