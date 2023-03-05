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

string FindNameByYear(const map<int, string>& names, int year) {
  string name;

  for (const auto& item : names) {
    if (item.first <= year) {
      name = item.second;
    } else {
      break;
    }
  }

  return name;
}

class Person {
public:
  void ChangeFirstName(int year, const string& first_name) {
	first_names[year] = first_name;
  }

  void ChangeLastName(int year, const string& last_name) {
	last_names[year] = last_name;
  }

  string GetFullName(int year) {
	const string first_name = FindNameByYear(first_names, year);
	const string last_name = FindNameByYear(last_names, year);

	if (first_name.empty() && last_name.empty()) {
	  return "Incognito";

	} else if (first_name.empty()) {
	  return last_name + " with unknown first name";

	} else if (last_name.empty()) {
	  return first_name + " with unknown last name";

	} else {
	  return first_name + " " + last_name;
	}
  }

private:
  map<int, string> first_names;
  map<int, string> last_names;
};

void TestEmpty() {
  Person person;

  AssertEqual(person.GetFullName(190), "Incognito", "190");
  AssertEqual(person.GetFullName(0), "Incognito", "0");
  AssertEqual(person.GetFullName(-1), "Incognito", "-1");
}

void TestFirstName() {
  const string F_CONST = " with unknown last name";

  Person person;

  person.ChangeFirstName(1, "A");
  AssertEqual(person.GetFullName(0), "Incognito", "before initial");
  AssertEqual(person.GetFullName(1), "A" + F_CONST, "initial");
  AssertEqual(person.GetFullName(2), "A" + F_CONST, "after initial");

  person.ChangeFirstName(4, "B");
  AssertEqual(person.GetFullName(4), "B" + F_CONST, "future change");
  AssertEqual(person.GetFullName(0), "Incognito", "future change, Incognito check");
  AssertEqual(person.GetFullName(1), "A" + F_CONST, "future change, previous name check 1");
  AssertEqual(person.GetFullName(3), "A" + F_CONST, "future change, previous name check 3");
  AssertEqual(person.GetFullName(10), "B" + F_CONST, "future change, future check 10");

  person.ChangeFirstName(-1, "C");
  AssertEqual(person.GetFullName(-1), "C" + F_CONST, "past change");
  AssertEqual(person.GetFullName(-2), "Incognito", "past change, Incognito check");
  AssertEqual(person.GetFullName(0), "C" + F_CONST, "past change, future name check 0");
  AssertEqual(person.GetFullName(1), "A" + F_CONST, "past change, future name check 1");
  AssertEqual(person.GetFullName(3), "A" + F_CONST, "past change, future name check 3");
  AssertEqual(person.GetFullName(10), "B" + F_CONST, "past change, future name check 10");

  person.ChangeFirstName(3, "D");
  AssertEqual(person.GetFullName(3), "D" + F_CONST, "D change");
  AssertEqual(person.GetFullName(10), "B" + F_CONST, "D change, future name check 10");
  AssertEqual(person.GetFullName(4), "B" + F_CONST, "D change, future name check 4");
  AssertEqual(person.GetFullName(2), "A" + F_CONST, "D change, past name check 2");
  AssertEqual(person.GetFullName(1), "A" + F_CONST, "D change, past name check 1");
  AssertEqual(person.GetFullName(-1), "C" + F_CONST, "D change, past name check -1");
  AssertEqual(person.GetFullName(0), "C" + F_CONST, "D change, past name check 0");
}

void TestLastName() {
	const string F_CONST = " with unknown first name";

	Person person;

	person.ChangeLastName(1, "A");
	AssertEqual(person.GetFullName(0), "Incognito", "before initial");
	AssertEqual(person.GetFullName(1), "A" + F_CONST, "initial");
	AssertEqual(person.GetFullName(2), "A" + F_CONST, "after initial");

	person.ChangeLastName(4, "B");
	AssertEqual(person.GetFullName(4), "B" + F_CONST, "future change");
	AssertEqual(person.GetFullName(0), "Incognito", "future change, Incognito check");
	AssertEqual(person.GetFullName(1), "A" + F_CONST, "future change, previous name check 1");
	AssertEqual(person.GetFullName(3), "A" + F_CONST, "future change, previous name check 3");
	AssertEqual(person.GetFullName(10), "B" + F_CONST, "future change, future check 10");

	person.ChangeLastName(-1, "C");
	AssertEqual(person.GetFullName(-1), "C" + F_CONST, "past change");
	AssertEqual(person.GetFullName(-2), "Incognito", "past change, Incognito check");
	AssertEqual(person.GetFullName(0), "C" + F_CONST, "past change, future name check 0");
	AssertEqual(person.GetFullName(1), "A" + F_CONST, "past change, future name check 1");
	AssertEqual(person.GetFullName(3), "A" + F_CONST, "past change, future name check 3");
	AssertEqual(person.GetFullName(10), "B" + F_CONST, "past change, future name check 10");

	person.ChangeLastName(3, "D");
	AssertEqual(person.GetFullName(3), "D" + F_CONST, "D change");
	AssertEqual(person.GetFullName(10), "B" + F_CONST, "D change, future name check 10");
	AssertEqual(person.GetFullName(4), "B" + F_CONST, "D change, future name check 4");
	AssertEqual(person.GetFullName(2), "A" + F_CONST, "D change, past name check 2");
	AssertEqual(person.GetFullName(1), "A" + F_CONST, "D change, past name check 1");
	AssertEqual(person.GetFullName(-1), "C" + F_CONST, "D change, past name check -1");
	AssertEqual(person.GetFullName(0), "C" + F_CONST, "D change, past name check 0");
}

void TestFirstNameAndLast() {
	{
		Person person;

		person.ChangeFirstName(81, "Vova");
		person.ChangeLastName(81, "Vovanovec");
		AssertEqual(person.GetFullName(81), "Vova Vovanovec", "81 both");
		AssertEqual(person.GetFullName(80), "Incognito", "80 both");
		AssertEqual(person.GetFullName(82), "Vova Vovanovec", "82 both");
	}
	{
		Person person;

		person.ChangeFirstName(81, "Vova");
		person.ChangeLastName(83, "Vovanovec");
		AssertEqual(person.GetFullName(81), "Vova with unknown last name", "81 1) f, 2) l");
		AssertEqual(person.GetFullName(82), "Vova with unknown last name", "82 1) f, 2) l");
		AssertEqual(person.GetFullName(83), "Vova Vovanovec", "83 1) f, 2) l");
		AssertEqual(person.GetFullName(84), "Vova Vovanovec", "84 1) f, 2) l");
		AssertEqual(person.GetFullName(80), "Incognito", "80 1) f, 2) l");
	}
	{
		Person person;

		person.ChangeLastName(81, "Vovanovec");
		person.ChangeFirstName(83, "Vova");
		AssertEqual(person.GetFullName(81), "Vovanovec with unknown first name", "81 1) l, 2) f");
		AssertEqual(person.GetFullName(82), "Vovanovec with unknown first name", "82 1) l, 2) f");
		AssertEqual(person.GetFullName(83), "Vova Vovanovec", "83 1) l, 2) f");
		AssertEqual(person.GetFullName(84), "Vova Vovanovec", "84 1) l, 2) f");
		AssertEqual(person.GetFullName(80), "Incognito", "80 1) l, 2) f");
	}
}

void TestDifferent() {
	{
	Person p;

	p.ChangeLastName(91, "L91");
	p.ChangeFirstName(85, "F85");
	p.ChangeFirstName(75, "F75");
	p.ChangeLastName(67, "L67");

	AssertEqual(p.GetFullName(99), "F85 L91", "99 F85 L91");
	AssertEqual(p.GetFullName(87), "F85 L67", "87 F85 L67");
	AssertEqual(p.GetFullName(84), "F75 L67", "84 F75 L67");
	AssertEqual(p.GetFullName(74), "L67 with unknown first name", "74 L67 with unknown first name");

	p.ChangeFirstName(55, "F55");
	AssertEqual(p.GetFullName(74), "F55 L67", "74 F55 L67");
	AssertEqual(p.GetFullName(64), "F55 with unknown last name", "64 F55 with unknown last name");
	AssertEqual(p.GetFullName(54), "Incognito", "54 Incognito");
	}
	{
	Person p;

	p.ChangeLastName(-91, "-L91");
	p.ChangeFirstName(-85, "-F85");
	p.ChangeFirstName(-75, "-F75");
	p.ChangeLastName(-67, "-L67");

	AssertEqual(p.GetFullName(-99), "Incognito", "-99 Incognito");
	AssertEqual(p.GetFullName(-87), "-L91 with unknown first name", "-87 -L91 with unknown first name");
	AssertEqual(p.GetFullName(-84), "-F85 -L91", "-84 -F85 -L91");
	AssertEqual(p.GetFullName(-74), "-F75 -L91", "-74 -F75 -L91");

	p.ChangeFirstName(-55, "-F55");
	AssertEqual(p.GetFullName(-74), "-F75 -L91", "-74 -F75 -L91");
	AssertEqual(p.GetFullName(-64), "-F75 -L67", "-64 -F75 -L67");
	AssertEqual(p.GetFullName(-54), "-F55 -L67", "-54 -F55 -L67");
	}
}

int main() {
  TestRunner runner;
  runner.RunTest(TestEmpty, "TestEmpty");
  runner.RunTest(TestFirstName, "TestFirstName");
  runner.RunTest(TestLastName, "TestLastName");
  runner.RunTest(TestFirstNameAndLast, "TestFirstNameAndLast");
  runner.RunTest(TestDifferent, "TestDifferent");

  return 0;
}

/*
void TestPredefinedLastNameFirst() {
    Person person;

    person.ChangeLastName(1965, "Sergeeva");
    person.ChangeFirstName(1967, "Polina");

    AssertEqual(person.GetFullName(1964), "Incognito");
    AssertEqual(person.GetFullName(1966), "Sergeeva with unknown first name");
    AssertEqual(person.GetFullName(1968), "Polina Sergeeva");
}

void TestPredefined() {
    Person person;

    person.ChangeFirstName(1965, "Polina");
    person.ChangeLastName(1967, "Sergeeva");

    AssertEqual(person.GetFullName(1964), "Incognito");
    AssertEqual(person.GetFullName(1966), "Polina with unknown last name");
    AssertEqual(person.GetFullName(1968), "Polina Sergeeva");

    person.ChangeFirstName(1969, "Appolinaria");
    AssertEqual(person.GetFullName(1968), "Polina Sergeeva");
    AssertEqual(person.GetFullName(1969), "Appolinaria Sergeeva");
    AssertEqual(person.GetFullName(1970), "Appolinaria Sergeeva");

    person.ChangeLastName(1968, "Volkova");
    AssertEqual(person.GetFullName(1967), "Polina Sergeeva");
    AssertEqual(person.GetFullName(1968), "Polina Volkova");
    AssertEqual(person.GetFullName(1969), "Appolinaria Volkova");

} */
