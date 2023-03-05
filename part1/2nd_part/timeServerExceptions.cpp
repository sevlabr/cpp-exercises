#include <iostream>
#include <exception>
#include <string>
using namespace std;

string AskTimeServer() {
	throw runtime_error("other error");
	return "01:02:59";
}

class TimeServer {
public:
    string GetCurrentTime() {
    	try {
    		last_fetched_time = AskTimeServer();
    		return last_fetched_time;
    	} catch (const system_error&) {
    		return last_fetched_time;
    	}
    }

private:
    string last_fetched_time = "00:00:00";
};

int main() {
    TimeServer ts;
    try {
        cout << ts.GetCurrentTime() << endl;
    } catch (exception& e) {
        cout << "Exception got: " << e.what() << endl;
    }
    return 0;
}
