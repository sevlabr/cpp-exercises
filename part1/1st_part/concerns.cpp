#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {

	int q;
	cin >> q;

	vector<vector<string>> concerns(31);
	vector<int> number_of_dates = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int current_month_index = 0;


	for (int i = 0; i < q; ++i) {

		string operation_code;
		cin >> operation_code;

		if (operation_code == "ADD") {
			int day;
			string concern;
			cin >> day >> concern;
			concerns[day - 1].push_back(concern);

		} else if (operation_code == "DUMP") {
			int day;
			cin >> day;
			cout << concerns[day - 1].size() << " ";
			if (concerns[day - 1].size() > 0) {
				for (auto concern : concerns[day - 1]) {
					cout << concern << " ";
				}
			}
			cout << endl;


		} else if (operation_code == "NEXT") {
			int previous_month_index = current_month_index;
			current_month_index += 1;
			current_month_index %= 12;
			int current_number_of_dates = number_of_dates[current_month_index];
			int previous_number_of_dates = number_of_dates[previous_month_index];

			if (current_number_of_dates > previous_number_of_dates) {
				concerns.resize(current_number_of_dates);

			} else if (current_number_of_dates < previous_number_of_dates) {
				int new_last_day_index = current_number_of_dates - 1;
				for (int i = new_last_day_index + 1; i < previous_number_of_dates; ++i){
					concerns[new_last_day_index].insert(end(concerns[new_last_day_index]),
							begin(concerns[i]), end(concerns[i]));
				}
				concerns.resize(current_number_of_dates);
			}
		}

	}

	return 0;
}


/* #include <iostream>
#include <string>
#include <vector>

using namespace std;

const vector<int> MONTH_LENGTHS =
  {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
const int MONTH_COUNT = MONTH_LENGTHS.size();

int main() {
  int q;
  cin >> q;

  int month = 0;

  vector<vector<string>> days_concerns(MONTH_LENGTHS[month]);

  for (int i = 0; i < q; ++i) {
    string operation_code;
    cin >> operation_code;

    if (operation_code == "ADD") {

      int day;
      string concern;
      cin >> day >> concern;
      --day;
      days_concerns[day].push_back(concern);

    } else if (operation_code == "NEXT") {

      const int old_month_length = MONTH_LENGTHS[month];

      month = (month + 1) % MONTH_COUNT;

      const int new_month_length = MONTH_LENGTHS[month];

      if (new_month_length < old_month_length) {

        vector<string>& last_day_concerns = days_concerns[new_month_length - 1];

        for (int day = new_month_length; day < old_month_length; ++day) {
          last_day_concerns.insert(
              end(last_day_concerns),
              begin(days_concerns[day]), end(days_concerns[day]));
        }
      }
      days_concerns.resize(new_month_length);

    } else if (operation_code == "DUMP") {

      int day;
      cin >> day;
      --day;

      cout << days_concerns[day].size() << " ";
      for (const string& concern : days_concerns[day]) {
        cout << concern << " ";
      }
      cout << endl;

    }
  }

  return 0;
} */
