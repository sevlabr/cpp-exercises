#include <iostream>
#include <string>
#include <vector>

using namespace std;

void UpdateQueue(vector<bool>& queue, vector<int>& worried_people, const string& operation_name, const int& k)
{
	int n = queue.size();
	if (operation_name == "COME") {
		queue.resize(n + k, false);
	} else if (operation_name == "WORRY") {
		queue[k] = true;
	} else if (operation_name == "QUIET") {
		queue[k] = false;
	} else if (operation_name == "WORRY_COUNT") {
		int worried_people_current = 0;
		for (auto person : queue) {
			if (person == true) {
				++worried_people_current;
			}
		}
		worried_people.push_back(worried_people_current);
	}
}

int main() {
	int Q;
	cin >> Q;
	vector<bool> queue;
	vector<int> worried_people;
	for (int i = 0; i < Q; ++i) {
		string operation_name;
		int k;
		cin >> operation_name;
		if (operation_name != "WORRY_COUNT") {
			cin >> k;
		}
		UpdateQueue(queue, worried_people, operation_name, k);
	}
	for (auto worried_people_number : worried_people) {
		cout << worried_people_number << endl;
	}
	return 0;
}


/* #include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
  int q;
  cin >> q;
  vector<bool> is_nervous;

  for (int i = 0; i < q; ++i) {
    string operation_code;
    cin >> operation_code;

    if (operation_code == "WORRY_COUNT") {

      cout << count(begin(is_nervous), end(is_nervous), true) << endl;

    } else {

      if (operation_code == "WORRY" || operation_code == "QUIET") {

        int person_index;
        cin >> person_index;

        is_nervous[person_index] = (operation_code == "WORRY");

      } else if (operation_code == "COME") {

        int person_count;
        cin >> person_count;

        is_nervous.resize(is_nervous.size() + person_count, false);

      }
    }
  }

  return 0;
} */
