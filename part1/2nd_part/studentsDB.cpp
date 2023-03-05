#include <vector>
#include <string>
#include <iostream>

using namespace std;

struct Student {
	string first_name;
	string last_name;
	long int bday;
	long int bmonth;
	long int byear;
};

int main() {
	int n;
	cin >> n;
	vector<Student> students;
	for (int i = 0; i < n; ++i) {
		string f_name, l_name;
		long int day, month, year;
		cin >> f_name >> l_name >> day >> month >> year;
		students.push_back({f_name, l_name, day, month, year});
	}
	int m;
	cin >> m;
	for (int i = 0; i < m; ++i) {
		string operation_code;
		int k;
		cin >> operation_code >> k;
		--k;
		if (operation_code == "name" && k >= 0 && k <= n - 1) {
			cout << students[k].first_name << " " <<students[k].last_name << endl;
		} else if (operation_code == "date" && k >= 0 && k <= n - 1) {
			cout << students[k].bday << "." << students[k].bmonth << "." << students[k].byear << endl;
		} else {
			cout << "bad request" << endl;
		}
	}
	return 0;
}
