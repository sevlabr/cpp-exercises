#include <iostream>
#include <cmath>

using namespace std;

int main() {
	double a, b, c;
	cin >> a >> b >> c;

	if (b == 0 && c == 0) {
		cout << 0;
	} else if (a == 0 && c == 0) {
		cout << 0;
	} else if (a == 0 && b == 0) {
		cout << " ";
	} else if (a == 0) {
		cout << -c/b;
	} else {
		double d = b*b - 4*a*c;
		if (d > 0) {
			cout << (-b + sqrt(d))/(2*a) << " " << (-b - sqrt(d))/(2*a);
		} else if (d < 0) {
			  cout << " ";
		} else {
			cout << -b/(2*a);
		}
	}

	return 0;
}

/*
#include <iostream>
#include <cmath>

using namespace std;

int main() {
  double A, B, C;
  cin >> A >> B >> C;

  double D = B * B - 4 * A * C;

  if (A == 0) {

    // Bx = -C => x = -C / B
    if (B != 0) {
      cout << -C / B << endl;
    }

  } else if (D == 0) {

    cout << -B / (2 * A) << endl;

  } else if (D > 0) {

    double r1 = (-B + sqrt(D)) / (2 * A);
    double r2 = (-B - sqrt(D)) / (2 * A);

    cout << r1 << " " << r2 << endl;

  }

  return 0;
}
*/
