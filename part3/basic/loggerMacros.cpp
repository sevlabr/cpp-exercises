#include "test_runner.h"

#include <sstream>
#include <string>

using namespace std;

/*
#define FILE_LINE __FILE__ << ":" << __LINE__
#define LINE "Line " << __LINE__
#define FILE __FILE__

class Logger {
public:
  explicit Logger(ostream& output_stream) : os(output_stream) {
  }

  void SetLogLine(bool value) { log_line = value; }
  void SetLogFile(bool value) { log_file= value; }

  void Log(const string& message);

  bool LineStatus() const {
	  return log_line;
  }

  bool FileStatus() const {
	  return log_file;
  }

  ostream& OStream() {
	  return os;
  }

private:
  ostream& os;
  bool log_line = false;
  bool log_file = false;
};

void Logger::Log(const string& message) {
	os << message << endl;
}

#define LOG(logger, message) 						  					\
	if (logger.LineStatus() && logger.FileStatus()) { \
		logger.OStream() << FILE_LINE << " "; 					\
		logger.Log(message);											      \
	} else if (logger.LineStatus()) {									\
		logger.OStream() << LINE << " ";								\
		logger.Log(message);											      \
	} else if (logger.FileStatus()) { 								\
		logger.OStream() <<	FILE << " ";								\
		logger.Log(message); 											      \
	} else {															            \
		logger.Log(message); 											      \
	}
*/

class Logger {
public:
  explicit Logger(ostream& output_stream) : os(output_stream) {
  }

  void SetLogLine(bool value) { log_line = value; }
  void SetLogFile(bool value) { log_file= value; }

  void Log(const string& message);

  void SetFile(const string& file) {
	  file_name = file;
  }

  void SetLine(const int& line) {
	  line_number = line;
  }

private:
  ostream& os;
  bool log_line = false;
  bool log_file = false;
  string file_name = "";
  int line_number = 0;
};

void Logger::Log(const string& message) {
	if (log_line && log_file) {
		os << file_name << ":" << line_number << " ";
	} else if (log_line) {
		os << "Line " << line_number << " ";
	} else if (log_file) {
		os << file_name << " ";
	}
	os << message << endl;
}

#define LOG(logger, message) \
	logger.SetFile(__FILE__);\
	logger.SetLine(__LINE__);\
	logger.Log(message)

void TestLog() {
/* 
 * (http://en.cppreference.com/w/cpp/preprocessor/line)
 */
#line 1 "logger.cpp"

  ostringstream logs;
  Logger l(logs);
  LOG(l, "hello");

  l.SetLogFile(true);
  LOG(l, "hello");

  l.SetLogLine(true);
  LOG(l, "hello");

  l.SetLogFile(false);
  LOG(l, "hello");

  string expected = "hello\n";
  expected += "logger.cpp hello\n";
  expected += "logger.cpp:10 hello\n";
  expected += "Line 13 hello\n";
  ASSERT_EQUAL(logs.str(), expected);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestLog);
}
