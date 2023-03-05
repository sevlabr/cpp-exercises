#include <iostream>

using namespace std;

int Factorial(int n) {
	if (n > 0) {
		return n*Factorial(n - 1);
	} else {
		return 1;
	}
}

int main() {
	int n;
	cin >> n;
	cout << Factorial(n);
	return 0;
}


/*int Factorial(int x) {
  int result = 1;
  for (int i = 2; i <= x; ++i) {
    result *= i;
  }
  return result;
} */

/*int Factorial(int x) {
  if (x <= 1) {
    return 1;
  } else {
    return x * Factorial(x - 1);
  }
} */
