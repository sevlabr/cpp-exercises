#include <iostream>

using namespace std;

struct Log {
	Log(string name) : n(name) {
		cout << "+ " << n << endl;
	}

	~Log() {
		cout << "- " << n << endl;
	}

	string n;
};

struct Fruit {
	Fruit (const string& t) : l(t + " (Fruit)") {
	}

	const Log l;
};

struct Apple : public Fruit {
	Apple(const string& t)
	: Fruit(t), la(t) {
	}
	const Log la;
};

class AppleTree {
public:
	AppleTree(const string& t)
		: type(t)
		, a1(type + " a1")
		, a2(type + " a2") {
	}

	string type;
	Apple a1;
	Apple a2;
	Log lt = Log("AppleTree");
};

int main() {
	AppleTree at("AppleTree");
	return 0;
}
