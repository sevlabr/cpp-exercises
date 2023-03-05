#include <iostream>
#include <vector>
#include <memory>
#include <sstream>
#include <istream>
#include <iomanip>
#include <cmath>

using namespace std;

class Figure {
public:
	Figure(const string& type) : type_(type) {}
	virtual string Name() const = 0;
	virtual double Perimeter() const = 0;
	virtual double Area() const = 0;

	virtual ~Figure() = default;

	const string type_;
};

class Triangle : public Figure {
public:

	Triangle(const string& type, const double& a, const double& b, const double& c)
	: Figure(type), a_(a), b_(b), c_(c) {}

	string Name() const override {
		return type_;
	}

	double Perimeter() const override {
		return a_ + b_ + c_;
	}

	double Area() const override {
		const double p = (a_ + b_ + c_) / 2;
		return sqrt((p * (p - a_) * (p - b_) * (p - c_)));
	}

private:
	const double a_, b_, c_;
};

class Rect : public Figure {
public:

	Rect(const string& type, const int& w, const int& h)
	: Figure(type), w_(w), h_(h) {}

	string Name() const override {
		return type_;
	}

	double Perimeter() const override {
		return static_cast<double>( (w_ + h_) * 2 );
	}

	double Area() const override {
		return static_cast<double>(w_ * h_);
	}

private:
	const int w_, h_;
};

class Circle : public Figure {
public:

	Circle(const string& type, const int& r)
	: Figure(type), r_(r) {}

	string Name() const override {
		return type_;
	}

	double Perimeter() const override {
		return static_cast<double>( 2 * Pi * r_ );
	}

	double Area() const override {
		return static_cast<double>( Pi * r_ * r_);
	}

private:
	const int r_;
	const double Pi = 3.14;
};

shared_ptr<Figure> CreateFigure(istream& is) {
	shared_ptr<Figure> new_figure;
	string name;
	is >> name;
	if (name == "RECT") {
		int width, height;
		is >> width >> height;
		new_figure = make_shared<Rect>(name, width, height);
	} else if (name == "TRIANGLE") {
		double a, b, c;
		is >> a >> b >> c;
		new_figure = make_shared<Triangle>(name, a, b, c);
	} else if (name == "CIRCLE") {
		int r;
		is >> r;
		new_figure = make_shared<Circle>(name, r);
	}
	return new_figure;
}

int main() {
  vector<shared_ptr<Figure>> figures;
  for (string line; getline(cin, line); ) {
    istringstream is(line);

    string command;
    is >> command;
    if (command == "ADD") {
      // https://en.cppreference.com/w/cpp/io/manip/ws
      is >> ws;
      figures.push_back(CreateFigure(is));
    } else if (command == "PRINT") {
      for (const auto& current_figure : figures) {
        cout << fixed << setprecision(3)
             << current_figure->Name() << " "
             << current_figure->Perimeter() << " "
             << current_figure->Area() << endl;
      }
    /* } else if (command == "Terminate") {
    	return 1; */
    }
  }
  return 0;
}
