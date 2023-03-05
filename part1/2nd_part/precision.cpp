#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>

using namespace std;

int main() {
	ifstream input("input.txt");
	if (input.is_open()) {
		double number = 0;
		cout << fixed << setprecision(3);
		while (input >> number) {
			cout << number << endl;
		}
	}
	return 0;
}
