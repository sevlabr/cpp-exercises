#include <iomanip>
#include <iostream>
#include <map>
#include <vector>
#include <stdexcept>

using namespace std;

class ReadingManager {
public:
	ReadingManager()
		: page_to_already_read(NUMBER_OF_PAGES + 1, 0),
		user_to_page_count() {}

	void Read(const int& user_id, const int& page_count) {
		int prev_page_count;
		try {
			prev_page_count = user_to_page_count.at(user_id);
			++prev_page_count;
		} catch (const out_of_range&) {
			prev_page_count = 1;
		}
		for (int page = prev_page_count; page <= page_count; ++page) {
			page_to_already_read[page] += 1;
		}
		user_to_page_count[user_id] = page_count;
	}

	double Cheer(const int& user_id) const {
		try {
			const int page = user_to_page_count.at(user_id);
			if (user_to_page_count.size() == 1) {
				return 1;
			}
			return (user_to_page_count.size() - page_to_already_read[page]) * 1.0
					/ (user_to_page_count.size() - 1);
		} catch (const out_of_range&) {
			return 0;
		}
	}

private:
	static const int NUMBER_OF_PAGES = 1'000;
	vector<int> page_to_already_read;
	map<int, int> user_to_page_count;
};


int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  ReadingManager manager;

  int query_count;
  cin >> query_count;

  for (int query_id = 0; query_id < query_count; ++query_id) {
    string query_type;
    cin >> query_type;
    int user_id;
    cin >> user_id;

    if (query_type == "READ") {
      int page_count;
      cin >> page_count;
      manager.Read(user_id, page_count);
    } else if (query_type == "CHEER") {
      cout << setprecision(6) << manager.Cheer(user_id) << "\n";
    }
  }
  return 0;
}
