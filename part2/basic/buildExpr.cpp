#include <iostream>
#include <deque>
#include <string>

using namespace std;

int main() {
	int x;
	cin >> x;
	deque<string> result;
	result.push_back(to_string(x));
	int n;
	cin >> n;
	string previous_operation_sign = "*";
	for (int operation_count = 0; operation_count < n; ++operation_count) {
		string operation_sign;
		cin >> operation_sign;
		int operation_number;
		cin >> operation_number;
		if ((previous_operation_sign == "+" || previous_operation_sign == "-") &&
				(operation_sign == "*" || operation_sign == "/")) {
			result.push_front("(");
			result.push_back(")");
		}
		result.push_back(" " + operation_sign + " " + to_string(operation_number));
		previous_operation_sign = operation_sign;
	}
	for (const string& unit : result) {
		cout << unit;
	}
	return 0;
}

/* #include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <numeric>
#include <deque>

using namespace std;

struct Operation {
  char type = 0;
  int number = 0;
};

bool NeedBrackets(char last, char current) {
  return (last == '+' || last == '-') && (current == '*' || current == '/');
}


int main() {
  int initial_number;
  cin >> initial_number;

  int number_of_operations;
  cin >> number_of_operations;
  vector<Operation> operations(number_of_operations);  // (*)
  for (int i = 0; i < number_of_operations; ++i) {
    cin >> operations[i].type;
    cin >> operations[i].number;
  }

  deque<string> expression;
  expression.push_back(to_string(initial_number));
  char last_type = '*';
  for (const auto& operation : operations) {
    if (NeedBrackets(last_type, operation.type)) {
      expression.push_front("(");
      expression.push_back(")");
    }
    expression.push_back(" ");
    expression.push_back(string(1, operation.type));
    expression.push_back(" ");
    expression.push_back(to_string(operation.number));

    last_type = operation.type;
  }

  for (const string& s : expression) {
    cout << s;
  }

  return 0;
} */
