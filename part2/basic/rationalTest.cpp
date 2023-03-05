#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
  os << "{";
  bool first = true;
  for (const auto& kv : m) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << kv.first << ": " << kv.second;
  }
  return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
  if (t != u) {
    ostringstream os;
    os << "Assertion failed: " << t << " != " << u;
    if (!hint.empty()) {
       os << " hint: " << hint;
    }
    throw runtime_error(os.str());
  }
}

void Assert(bool b, const string& hint) {
  AssertEqual(b, true, hint);
}

class TestRunner {
public:
  template <class TestFunc>
  void RunTest(TestFunc func, const string& test_name) {
    try {
      func();
      cerr << test_name << " OK" << endl;
    } catch (exception& e) {
      ++fail_count;
      cerr << test_name << " fail: " << e.what() << endl;
    } catch (...) {
      ++fail_count;
      cerr << "Unknown exception caught" << endl;
    }
  }

  ~TestRunner() {
    if (fail_count > 0) {
      cerr << fail_count << " unit tests failed. Terminate" << endl;
      exit(1);
    }
  }

private:
  int fail_count = 0;
};

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

void TestDefaultConstructor() {
	Rational r;
	Assert(r.Numerator() == 0, "Def Numerator");
	Assert(r.Denominator() == 1, "Def Denominator");
}

void TestNonZeroNumerator() {
	Rational r_simple(2, 3);
	Assert(r_simple.Numerator() == 2, "Simple Numerator");
	Assert(r_simple.Denominator() == 3, "Simple Denominator");

	Rational r_cancellable_small(3, 9);
	Assert(r_cancellable_small.Numerator() == 1, "Cancellable s Numerator");
	Assert(r_cancellable_small.Denominator() == 3, "Cancellable s Denominator");

	Rational r_cancellable_big(40, 20);
	Assert(r_cancellable_big.Numerator() == 2, "Cancellable b Numerator");
	Assert(r_cancellable_big.Denominator() == 1, "Cancellable b Denominator");

	Rational r_cancellable_neg_num(-4, 16);
	Assert(r_cancellable_neg_num.Numerator() == -1, "Cancellable Neg Numerator");
	Assert(r_cancellable_neg_num.Denominator() == 4, "Cancellable Denominator N");

	Rational r_cancellable_neg_num_reverse(-16, 4);
	Assert(r_cancellable_neg_num_reverse.Numerator() == -4, "rev Cancellable Neg Numerator");
	Assert(r_cancellable_neg_num_reverse.Denominator() == 1, "rev Cancellable Denominator N");

	Rational r_cancellable_neg_denom(15, -5);
	AssertEqual(r_cancellable_neg_denom.Numerator(), -3, "Cancellable Numerator N");
	Assert(r_cancellable_neg_denom.Denominator() == 1, "Cancellable Neg Denominator");

	Rational r_cancellable_neg_denom_rev(5, -15);
	AssertEqual(r_cancellable_neg_denom_rev.Numerator(), -1, "rev Cancellable Numerator N");
	Assert(r_cancellable_neg_denom_rev.Denominator() == 3, "rev Cancellable Neg Denominator");

	Rational r_neg(-10, -25);
	Assert(r_neg.Numerator() == 2, "r_neg Numerator");
	Assert(r_neg.Denominator() == 5, "r_neg Denominator");

	Rational r_neg_rev(-26, -100);
	Assert(r_neg_rev.Numerator() == 13, "r_neg_rev Numerator");
	Assert(r_neg_rev.Denominator() == 50, "r_neg_rev Denominator");
}

void TestZeroNumerator() {
	Rational r_zero_def(0, 1);
	Assert(r_zero_def.Numerator() == 0, "r_zero_def Numerator");
	Assert(r_zero_def.Denominator() == 1, "r_zero_def Denominator");

	Rational r_zero_pos(0, 150);
	Assert(r_zero_pos.Numerator() == 0, "r_zero_pos Numerator");
	Assert(r_zero_pos.Denominator() == 1, "r_zero_pos Denominator");
	Rational r_zero_neg(0, -12320);
	Assert(r_zero_neg.Numerator() == 0, "r_zero_neg Numerator");
	Assert(r_zero_neg.Denominator() == 1, "r_zero_neg Denominator");
}

int main() {
  TestRunner runner;
  runner.RunTest(TestDefaultConstructor, "TestDefaultConstructor");
  runner.RunTest(TestNonZeroNumerator, "TestNonZeroNumerator");
  runner.RunTest(TestZeroNumerator, "TestZeroNumerator");
  return 0;
}

/*
void TestPredefined() {
  AssertEqual(Rational(1, 1).Numerator(), 1, "Canonical form of 1/1 is 1/1");
  AssertEqual(Rational(1, 1).Denominator(), 1, "Canonical form of 1/1 is 1/1");
  AssertEqual(Rational(3, 5).Numerator(), 3, "Canonical form of 3/5 is 3/5");
  AssertEqual(Rational(3, 5).Denominator(), 5, "Canonical form of 3/5 is 3/5");
  AssertEqual(Rational(2147483647, 2147483647).Numerator(), 1, "Canonical form of 2147483647/2147483647 is 1/1");
  AssertEqual(Rational(2147483647, 2147483647).Denominator(), 1, "Canonical form of 2147483647/2147483647 is 1/1");
  AssertEqual(Rational(-5, 4).Numerator(), -5, "Canonical form of -5/4 is -5/4");
  AssertEqual(Rational(-5, 4).Denominator(), 4, "Canonical form of -5/4 is -5/4");
  AssertEqual(Rational(5, -4).Numerator(), -5, "Canonical form of 5/-4 is -5/4");
  AssertEqual(Rational(5, -4).Denominator(), 4, "Canonical form of 5/-4 is -5/4");
  AssertEqual(Rational(-6, -2).Numerator(), 3, "Canonical form of -6/-2 is 3/1");
  AssertEqual(Rational(-6, -2).Denominator(), 1, "Canonical form of -6/-2 is 3/1");
  AssertEqual(Rational(21, 56).Numerator(), 3, "Canonical form of 21/56 is 3/8");
  AssertEqual(Rational(21, 56).Denominator(), 8, "Canonical form of 21/56 is 3/8");
  AssertEqual(Rational(0, 100).Numerator(), 0, "Canonical form of 0/100 is 0/1");
  AssertEqual(Rational(0, 100).Denominator(), 1, "Canonical form of 0/100 is 0/1");
  AssertEqual(Rational().Numerator(), 0, "Canonical form of default constructed is 0/1");
  AssertEqual(Rational().Denominator(), 1, "Canonical form of default constructed is 0/1");
}

int main() {
  TestRunner runner;
  runner.RunTest(TestPredefined, "TestPredefined");
  return 0;
} */
