#include <vector>
#include <string>
#include <utility>
#include <iostream>

using namespace std;

string ReadTitle() {
	return string(80, 'a');
}

int main() {
	{
		string title = ReadTitle();
		vector<string> titles;
		titles.push_back(title.substr(8));
		cout << title.size() << ' ' << titles.back().size() << endl;
	}
	{
		const vector<string> titles_pool = {"a", "b", "c"};
		//titles_pool.push_back("d");
		//titles_pool[2] = "d";
	}
	{
		string title = ReadTitle();
		cout << title << endl;
		string new_title = title.replace(0, 4, "C++");
		cout << new_title << '\n' << title << endl;
	}
	{
		string title = ReadTitle();
		cout << title << endl;
		vector<string> titles;
		titles.push_back(title.append(1, '+'));
		cout << title << endl;
		cout << titles.back() << endl;
	}
	{
		string title = ReadTitle();
		cout << title.size() << endl;
		string new_title = move(title.replace(0, 4, "C++"));
		cout << title.size() << ' ' << new_title.size() << endl;
	}
	return 0;
}
