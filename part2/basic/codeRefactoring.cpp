#include <iostream>
#include <string>
#include <vector>

using namespace std;


class Human {
public:
	Human(const string& type) : Type(type) {}

	string GetType() const {
		return Type;
	}

	void IntroduceSelf() const {
		cout << GetType() << ": " << GetName();
	}

	void JustWalk(const string& destination) const {
		IntroduceSelf();
		cout << " walks to: " << destination << endl;
	}

	virtual void Walk(const string& destination) const = 0;

	virtual string GetName() const = 0;

	virtual ~Human() = default;

private:
	const string Type;
};

class Student : public Human {
public:

    Student(const string& name, const string& favouriteSong)
		: Human("Student"), Name(name), FavouriteSong(favouriteSong) {}

    string GetName() const override {
    	return Name;
    }

    string GetFavouriteSong() const {
    	return FavouriteSong;
    }

    void Learn() {
    	IntroduceSelf();
        cout << " learns" << endl;
    }

    void Walk(const string& destination) const override {
        JustWalk(destination);
        SingSong();
    }

    void SingSong() const {
    	IntroduceSelf();
        cout << " sings a song: " << GetFavouriteSong() << endl;
    }

private:
    const string Name;
    const string FavouriteSong;
};


class Teacher : public Human {
public:

    Teacher(const string& name, const string& subject)
		: Human("Teacher"), Name(name), Subject(subject) {}

    string GetName() const override {
    	return Name;
    }

    string GetSubject() const {
    	return Subject;
    }

    void Teach() {
    	IntroduceSelf();
        cout << " teaches: " << GetSubject() << endl;
    }

    void Walk(const string& destination) const override {
        JustWalk(destination);
    }

private:
    const string Name;
    const string Subject;
};


class Policeman : public Human {
public:
    Policeman(const string& name)
		: Human("Policeman"),  Name(name) {}

    string GetName() const override {
    	return Name;
    }

    void Check(const Human& human) const {
    	IntroduceSelf();
    	cout << " checks " << human.GetType() << ". " << human.GetType()
    			<< "'s name is: " << human.GetName() << endl;
    }

    void Walk(const string& destination) const override {
        JustWalk(destination);
    }

private:
    const string Name;
};

void VisitPlaces(const Human& human, const vector<string>& places) {
	for (const string& place : places) {
		human.Walk(place);
	}
}


int main() {
	{
		Teacher t("Jim", "Math");
		Student s("Ann", "We will rock you");
		Policeman p("Bob");

		VisitPlaces(t, {"Moscow", "London"});
		p.Check(s);
		VisitPlaces(s, {"Moscow", "London"});
	}

	cout << endl;
	cout << "Additional tests:" << endl;
	cout << endl;

	{
		Student s("S", "Song");
		Teacher t("T", "C++");
		Policeman p1("P1");
		Policeman p2("P2");

		vector<string> places = {"City1", "City2", "City3"};

		cout << "Student tests:" << endl;
		cout << "GetType method: " << s.GetType() << endl;
		cout << "IntroduceSelf method: "; s.IntroduceSelf(); cout << endl;
		cout << "JustWalk method: "; s.JustWalk("WalkTown");
		cout << "GetName method: " << s.GetName() << endl;
		cout << "GetFavouriteSong method: " << s.GetFavouriteSong() << endl;
		cout << "Learn method: "; s.Learn();
		cout << "Walk method: "; s.Walk("WalkTown");
		cout << "SingSong method: "; s.SingSong();
		VisitPlaces(s, places);
		cout << endl;

		cout << "Teacher tests:" << endl;
		cout << "GetType method: " << t.GetType() << endl;
		cout << "IntroduceSelf method: "; t.IntroduceSelf(); cout << endl;
		cout << "JustWalk method: "; t.JustWalk("WalkTown");
		cout << "GetName method: " << t.GetName() << endl;
		cout << "GetSubject method: " << t.GetSubject() << endl;
		cout << "Teach method: "; t.Teach();
		cout << "Walk method: "; t.Walk("WalkTown");
		VisitPlaces(t, places);
		cout << endl;

		cout << "Policeman tests:" << endl;
		cout << "GetType method: " << p1.GetType() << endl;
		cout << "IntroduceSelf method: "; p1.IntroduceSelf(); cout << endl;
		cout << "JustWalk method: "; p1.JustWalk("WalkTown");
		cout << "GetName method: " << p1.GetName() << endl;
		cout << "Check method: "; p1.Check(s);
		cout << "Check method: "; p1.Check(t);
		cout << "Check method: "; p1.Check(p2);
		cout << "Walk method: "; p1.Walk("WalkTown");
		VisitPlaces(p1, places);
	}

    return 0;
}
