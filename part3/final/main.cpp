#include "search_server.h"
#include "parse.h"
#include "test_runner.h"
#include "profile.h"

#include <algorithm>
#include <iterator>
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <random>
#include <thread>
#include <utility>

using namespace std;

void TestFunctionality(
  const vector<string>& docs,
  const vector<string>& queries,
  const vector<string>& expected
) {
  istringstream docs_input(Join('\n', docs));
  istringstream queries_input(Join('\n', queries));

  SearchServer srv;
  srv.UpdateDocumentBase(docs_input);
  ostringstream queries_output;
  srv.AddQueriesStream(queries_input, queries_output);

  const string result = queries_output.str();
  const auto lines = SplitBy(Strip(result), '\n');
  ASSERT_EQUAL(lines.size(), expected.size());
  for (size_t i = 0; i < lines.size(); ++i) {
    ASSERT_EQUAL(lines[i], expected[i]);
  }
}

void TestSerpFormat() {
  const vector<string> docs = {
    "london is the capital of great britain",
    "i am travelling down the river"
  };
  const vector<string> queries = {"london", "the"};
  const vector<string> expected = {
    "london: {docid: 0, hitcount: 1}",
    Join(' ', vector<string>{
      "the:",
      "{docid: 0, hitcount: 1}",
      "{docid: 1, hitcount: 1}"
    })
  };

  TestFunctionality(docs, queries, expected);
}

void TestTop5() {
  const vector<string> docs = {
    "milk a",
    "milk b",
    "milk c",
    "milk d",
    "milk e",
    "milk f",
    "milk g",
    "water a",
    "water b",
    "fire and earth"
  };

  const vector<string> queries = {"milk", "water", "rock"};
  const vector<string> expected = {
    Join(' ', vector<string>{
      "milk:",
      "{docid: 0, hitcount: 1}",
      "{docid: 1, hitcount: 1}",
      "{docid: 2, hitcount: 1}",
      "{docid: 3, hitcount: 1}",
      "{docid: 4, hitcount: 1}"
    }),
    Join(' ', vector<string>{
      "water:",
      "{docid: 7, hitcount: 1}",
      "{docid: 8, hitcount: 1}",
    }),
    "rock:",
  };
  TestFunctionality(docs, queries, expected);
}

void TestHitcount() {
  const vector<string> docs = {
    "the river goes through the entire city there is a house near it",
    "the wall",
    "walle",
    "is is is is",
  };
  const vector<string> queries = {"the", "wall", "all", "is", "the is"};
  const vector<string> expected = {
    Join(' ', vector<string>{
      "the:",
      "{docid: 0, hitcount: 2}",
      "{docid: 1, hitcount: 1}",
    }),
    "wall: {docid: 1, hitcount: 1}",
    "all:",
    Join(' ', vector<string>{
      "is:",
      "{docid: 3, hitcount: 4}",
      "{docid: 0, hitcount: 1}",
    }),
    Join(' ', vector<string>{
      "the is:",
      "{docid: 3, hitcount: 4}",
      "{docid: 0, hitcount: 3}",
      "{docid: 1, hitcount: 1}",
    }),
  };
  TestFunctionality(docs, queries, expected);
}

void TestRanking() {
  const vector<string> docs = {
    "london is the capital of great britain",
    "paris is the capital of france",
    "berlin is the capital of germany",
    "rome is the capital of italy",
    "madrid is the capital of spain",
    "lisboa is the capital of portugal",
    "bern is the capital of switzerland",
    "moscow is the capital of russia",
    "kiev is the capital of ukraine",
    "minsk is the capital of belarus",
    "astana is the capital of kazakhstan",
    "beijing is the capital of china",
    "tokyo is the capital of japan",
    "bangkok is the capital of thailand",
    "welcome to moscow the capital of russia the third rome",
    "amsterdam is the capital of netherlands",
    "helsinki is the capital of finland",
    "oslo is the capital of norway",
    "stockgolm is the capital of sweden",
    "riga is the capital of latvia",
    "tallin is the capital of estonia",
    "warsaw is the capital of poland",
  };

  const vector<string> queries = {"moscow is the capital of russia"};
  const vector<string> expected = {
    Join(' ', vector<string>{
      "moscow is the capital of russia:",
      "{docid: 7, hitcount: 6}",
      "{docid: 14, hitcount: 6}",
      "{docid: 0, hitcount: 4}",
      "{docid: 1, hitcount: 4}",
      "{docid: 2, hitcount: 4}",
    })
  };
  TestFunctionality(docs, queries, expected);
}

void TestBasicSearch() {
  const vector<string> docs = {
    "we are ready to go",
    "come on everybody shake you hands",
    "i love this game",
    "just like exception safety is not about writing try catch everywhere in your code move semantics are not about typing double ampersand everywhere in your code",
    "daddy daddy daddy dad dad dad",
    "tell me the meaning of being lonely",
    "just keep track of it",
    "how hard could it be",
    "it is going to be legen wait for it dary legendary",
    "we dont need no education"
  };

  const vector<string> queries = {
    "we need some help",
    "it",
    "i love this game",
    "tell me why",
    "dislike",
    "about"
  };

  const vector<string> expected = {
    Join(' ', vector<string>{
      "we need some help:",
      "{docid: 9, hitcount: 2}",
      "{docid: 0, hitcount: 1}"
    }),
    Join(' ', vector<string>{
      "it:",
      "{docid: 8, hitcount: 2}",
      "{docid: 6, hitcount: 1}",
      "{docid: 7, hitcount: 1}",
    }),
    "i love this game: {docid: 2, hitcount: 4}",
    "tell me why: {docid: 5, hitcount: 2}",
    "dislike:",
    "about: {docid: 3, hitcount: 2}",
  };
  TestFunctionality(docs, queries, expected);
}

void PrepareDataForBenchmark() {
	LOG_DURATION("PrepareData");

	const int LANGUAGE_SIZE = 15'000;
	const int WORD_SIZE = 100;

	const int DOCUMENT_SIZE = 100;
	const int DOCUMENT_INPUT_SIZE = 10'000;
	const int DOCUMENTS_COUNT = 2;

	const int QUERY_SIZE = 10;
	const int QUERY_INPUT_SIZE = 20'000;

//	const int LANGUAGE_SIZE = 500;
//	const int WORD_SIZE = 50;

//	const int DOCUMENT_SIZE = 100;
//	const int DOCUMENT_INPUT_SIZE = 1'000;
//	const int DOCUMENTS_COUNT = 2;
//
//	const int QUERY_SIZE = 5;
//	const int QUERY_INPUT_SIZE = 5'000;
//
//	const int LONG_QUERY_SIZE = 500'000;

  std::default_random_engine rd(34);
  std::uniform_int_distribution<char> char_gen('a', 'z');

  auto random_word = [&](size_t len) {
    string result(len, ' ');
    std::generate(begin(result), end(result), [&] { return char_gen(rd); });
    return result;
  };

  std::uniform_int_distribution<size_t> word_len_gen(1, WORD_SIZE);

  vector<string> language_words(LANGUAGE_SIZE);
  for (auto& w : language_words) {
    w = random_word(word_len_gen(rd));
  }

  ofstream lang("language.txt");
  for (const auto& w : language_words) {
    lang << w << ' ';
  }

  std::uniform_int_distribution<size_t> doc_len_gen(1, DOCUMENT_SIZE);
  std::uniform_int_distribution<int> word_choice(1, 100);

  for (int doc = 0; doc < DOCUMENTS_COUNT; ++doc) {
    ofstream documents("documents" + to_string(doc) + ".txt");
    for (int line = 0; line < DOCUMENT_INPUT_SIZE; ++line) {
      ostringstream line_out;
      auto line_len = doc_len_gen(rd);
      for (size_t i = 0; i < line_len; ++i) {
        if (word_choice(rd) < 20) {
          std::uniform_int_distribution<size_t> word_index(0, language_words.size() - 1);
          line_out << language_words[word_index(rd)];
        } else {
          line_out << random_word(word_len_gen(rd));
        }
        line_out << ' ';
      }
      documents << line_out.str() << '\n';
    }
  }

  std::uniform_int_distribution<size_t> query_len_gen(1, QUERY_SIZE);

  ofstream queries("queries.txt");
  for (int line = 0; line < QUERY_INPUT_SIZE; ++line) {
    ostringstream line_out;
    auto line_len = query_len_gen(rd);
    for (size_t i = 0; i < line_len; ++i) {
      if (word_choice(rd) < 20) {
        std::uniform_int_distribution<size_t> word_index(0, language_words.size() - 1);
        line_out << language_words[word_index(rd)];
      } else {
        line_out << random_word(word_len_gen(rd));
      }
      line_out << ' ';
    }
    queries << line_out.str() << '\n';
  }

//  ofstream big_q("big_q.txt");
//  for(size_t i = 0; i < LONG_QUERY_SIZE; ++i) {
//  	if (word_choice(rd) < 20) {
//  		std::uniform_int_distribution<size_t> word_index(0, language_words.size() - 1);
//  		big_q << language_words[word_index(rd)];
//  	} else {
//  		big_q << random_word(word_len_gen(rd));
//  	}
//  	big_q << ' ';
//  }

}

void MakeHead(istream& document, const string& name) {
	const int BATCH_SIZE = 100;

	ofstream part(name + ".txt");
	int line_count = 0;
	for (string line; getline(document, line) && line_count < BATCH_SIZE; ++line_count) {
		part << line << '\n';
	}
}

void TestBench() {
//	PrepareDataForBenchmark();
//
//	{
//		LOG_DURATION("Check");
//		ifstream doc0("documents0.txt");
//		MakeHead(doc0, "head0");
//		ifstream doc1("documents1.txt");
//		MakeHead(doc1, "head1");
//	}

	{
		LOG_DURATION("Benchmark");

		SearchServer srv;

		ifstream input("documents0.txt");
		ifstream new_input("documents1.txt");
		ifstream queries("queries.txt");
		ifstream next_queries("queries.txt");
		ofstream q_results("current_results0.txt");
		ofstream next_q_results("current_results1.txt");

		{
			LOG_DURATION("1st Update");
			srv.UpdateDocumentBase(input);
		}
		{
			LOG_DURATION("1st Search");
			srv.AddQueriesStream(queries, q_results);
		}

		{
			LOG_DURATION("2nd Update");
			srv.UpdateDocumentBase(new_input);
		}
		{
			LOG_DURATION("2nd Search");
			srv.AddQueriesStream(next_queries, next_q_results);
		}
	}
}

bool CheckResults(const int num) {
	LOG_DURATION("Checking: " + to_string(num));
	ifstream canonical("results" + to_string(num) + ".txt");
	ifstream current("current_results" + to_string(num) + ".txt");

	for(string line; getline(canonical, line); ) {
		string res;
		getline(current, res);
		if (move(line) != move(res)) {
			return false;
		}
	}

	return true;
}

void TestResults() {
	ASSERT(CheckResults(0));
	ASSERT(CheckResults(1));
}

void TestAddQueries() {
	PrepareDataForBenchmark();

	ifstream query("big_q.txt");
	ifstream doc("document0.txt");
	ofstream output("out_for_big_q.txt");

	SearchServer srv(doc);

	srv.AddQueriesStream(query, output);
}

int main() {
  TestRunner tr;
//  RUN_TEST(tr, TestSerpFormat);
//  RUN_TEST(tr, TestTop5);
//  RUN_TEST(tr, TestHitcount);
//  RUN_TEST(tr, TestRanking);
//  RUN_TEST(tr, TestBasicSearch);
  RUN_TEST(tr, TestBench);
  RUN_TEST(tr, TestResults);
//  RUN_TEST(tr, TestAddQueries);
}
