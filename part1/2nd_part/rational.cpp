#include <iostream>
#include <cmath>
#include <sstream>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <exception>

using namespace std;

int lcm(const int& lhs, const int& rhs) {
	int greatest_common_divisor = __gcd(lhs, rhs);
	return abs(lhs * rhs) / greatest_common_divisor;
}

class Rational {
public:
    Rational() {
    	p = 0;
    	q = 1;
    }

    Rational(int numerator, int denominator) {
    	if (denominator == 0) {
    		throw invalid_argument("");
    	} else
    	{
    	int greatest_common_divisor = __gcd(numerator, denominator);
    	if (greatest_common_divisor == 1) {
    		p = numerator;
    		q = denominator;
    	} else {
    		p = numerator/greatest_common_divisor;
    		q = denominator/greatest_common_divisor;
    	}
    	if (p == 0) {
    		q = 1;
    	}
    	if (p * q < 0 && q < 0) {
    		q *= -1;
    		p *= -1;
    	} else if (p * q > 0 && q < 0) {
    		q *= -1;
    		p *= -1;
    	}
    	}
    }

    int Numerator() const {
    	return p;
    }

    int Denominator() const {
    	return q;
    }

private:
    int p;
    int q;
};

bool operator == (const Rational& lhs, const Rational& rhs) {
	if (lhs.Numerator() == rhs.Numerator() && lhs.Denominator() == rhs.Denominator()) {
		return true;
	} else {
		return false;
	}
}

Rational operator + (const Rational& lhs, const Rational& rhs) {
	int new_denominator = lcm(lhs.Denominator(), rhs.Denominator());
	return Rational(lhs.Numerator() * (new_denominator / lhs.Denominator()) +
			rhs.Numerator() * (new_denominator / rhs.Denominator()), new_denominator);
}

Rational operator - (const Rational& lhs, const Rational& rhs) {
	int new_denominator = lcm(lhs.Denominator(), rhs.Denominator());
	return Rational(lhs.Numerator() * (new_denominator / lhs.Denominator()) -
			rhs.Numerator() * (new_denominator / rhs.Denominator()), new_denominator);
}

Rational operator * (const Rational& lhs, const Rational& rhs) {
	return Rational(lhs.Numerator() * rhs.Numerator(), lhs.Denominator() * rhs.Denominator());
}

Rational operator / (const Rational& lhs, const Rational& rhs) {
	if (rhs.Numerator() == 0) {
		throw domain_error("");
	} else {
		return Rational(lhs.Numerator() * rhs.Denominator(), lhs.Denominator() * rhs.Numerator());
	}
}

ostream& operator << (ostream& stream, const Rational& r) {
	stream << r.Numerator() << '/' << r.Denominator();
	return stream;
}

istream& operator >> (istream& stream, Rational& r) {
	int num = 0;
	int denom = 1;
	if (stream >> num) {
		stream.ignore(1);
		if (stream >> denom) {
			r = {num, denom};
		}
	}
	return stream;
}

bool operator < (const Rational& lhs, const Rational& rhs) {
	int common_denominator = lcm(lhs.Denominator(), rhs.Denominator());
	return (lhs.Numerator() * (common_denominator / lhs.Denominator())) <
			(rhs.Numerator() * (common_denominator / rhs.Denominator()));
}


int main() {
    try {
    	Rational l, r;
    	char operation_code;
    	cin >> l >> operation_code >> r;
    	if (operation_code == '+') {
    		cout << l + r << endl;
    	} else if (operation_code == '-') {
    		cout << l - r << endl;
    	} else if (operation_code == '*') {
    		cout << l * r << endl;
    	} else if (operation_code == '/') {
    		cout << l / r << endl;
    	}
    } catch (invalid_argument&) {
    		cout << "Invalid argument" << endl;
    } catch (domain_error&) {
    		cout << "Division by zero" << endl;
    }
    return 0;
}


/*
#include <iostream>

using namespace std;

int GreatestCommonDivisor(int a, int b) {
  if (b == 0) {
    return a;
  } else {
    return GreatestCommonDivisor(b, a % b);
  }
}

class Rational {
public:
  Rational() {
    numerator = 0;
    denominator = 1;
  }
  Rational(int new_numerator, int new_denominator) {
    const int gcd = GreatestCommonDivisor(new_numerator, new_denominator);
    
    numerator = new_numerator / gcd;
    denominator = new_denominator / gcd;
    
    if (denominator < 0) {
      denominator = -denominator;
      numerator = -numerator;
    }
  }

  int Numerator() const {
    return numerator;
  }

  int Denominator() const {
    return denominator;
  }

private:
  int numerator;
  int denominator;
};

bool operator == (const Rational& lhs, const Rational& rhs) {
  return lhs.Numerator() == rhs.Numerator() &&
    lhs.Denominator() == rhs.Denominator();
}

Rational operator + (const Rational& lhs, const Rational& rhs) {
  return {
    lhs.Numerator() * rhs.Denominator() + rhs.Numerator() * lhs.Denominator(),
    lhs.Denominator() * rhs.Denominator()
  };
}

Rational operator - (const Rational& lhs, const Rational& rhs) {
  return {
    lhs.Numerator() * rhs.Denominator() - rhs.Numerator() * lhs.Denominator(),
    lhs.Denominator() * rhs.Denominator()
  };
}

Rational operator * (const Rational& lhs, const Rational& rhs) {
  return {
    lhs.Numerator() * rhs.Numerator(),
    lhs.Denominator() * rhs.Denominator()
  };
}

Rational operator / (const Rational& lhs, const Rational& rhs) {
  return lhs * Rational(rhs.Denominator(), rhs.Numerator());
}

istream& operator >> (istream& is, Rational& r) {
  int n, d;
  char c;

  if (is) {
    is >> n >> c >> d;
    if (is && c == '/') {
      r = Rational(n, d);
    }
  }

  return is;
}

ostream& operator << (ostream& os, const Rational& r) {
  return os << r.Numerator() << '/' << r.Denominator();
}

bool operator < (const Rational& lhs, const Rational& rhs) {
  return (lhs - rhs).Numerator() < 0;
}
*/
