#include "test_runner.h"
#include "profile.h"
#include "paginator.h"

#include <map>
#include <string>
#include <sstream>
#include <iostream>
#include <future>
#include <vector>
#include <functional>
#include <random>
#include <iterator>
#include <fstream>

using namespace std;

struct Stats {
  map<string, int> word_frequences;

  void operator += (const Stats& other) {
  	for (const auto& [word, frequence] : other.word_frequences) {
  		word_frequences[word] += frequence;
  	}
  }
};

Stats ExploreLine(const set<string>& key_words, const string& line) {
	Stats result;
	size_t beginning = 0;
	while(true) {
		size_t space = line.find(' ', beginning);
		auto it = key_words.find(
				line.substr(beginning, space - beginning)
		);
		if (it != end(key_words)) {
			++result.word_frequences[*it];
		}

		if (space == line.npos) {
			break;
		} else {
			beginning = space + 1;
		}
	}

	return result;
}

vector<string> ParseData(istream& input) {
	vector<string> result;
	for (string line; getline(input, line); ) {
		result.push_back(move(line));
	}
	return result;
}

Stats ExploreKeyWordsSingleThread(
  const set<string>& key_words, istream& input
) {
  Stats result;
  vector<string> data = ParseData(input);
  for (const string& line : data) {
    result += ExploreLine(key_words, line);
  }
  return result;
}

template <typename Iterator>
Stats ExploreKeyWordsFromIteratorSingleThread(
  const set<string>& key_words, Iterator begin, Iterator end
) {
  Stats result;
  for ( ; begin != end; ++begin) {
    result += ExploreLine(key_words, *begin);
  }
  return result;
}

Stats ExploreKeyWordsFromVectorSingleThread(
  const set<string>& key_words, const vector<string>& data
) {
  Stats result;
  for (const string& line : data) {
  	result += ExploreLine(key_words, line);
  }
  return result;
}

Stats ExploreKeyWords(const set<string>& key_words, istream& input) {
  vector<string> data = ParseData(input);
  const size_t page_size = 10'000;
  vector<future<Stats>> futures;
  for (const auto& page : Paginate(data, page_size)) {
  	futures.push_back(
  		async([&key_words, page] {
  				return ExploreKeyWordsFromIteratorSingleThread(key_words, page.begin(), page.end());
  		})
  	);
  }

  Stats result;
  for (auto& f : futures) {
  	result += f.get();
  }

  return result;
}

void TestBasic() {
  const set<string> key_words = {"yangle", "rocks", "sucks", "all"};

  stringstream ss;
  ss << "this new yangle service really rocks\n";
  ss << "It sucks when yangle isn't available\n";
  ss << "10 reasons why yangle is the best IT company\n";
  ss << "yangle rocks others suck\n";
  ss << "Goondex really sucks, but yangle rocks. Use yangle\n";

  /*vector<string> data = ParseData(ss);
  const auto stats = ExploreKeyWordsFromVectorSingleThread(key_words, data); */
  const auto stats = ExploreKeyWords(key_words, ss);
  const map<string, int> expected = {
    {"yangle", 6},
    {"rocks", 2},
    {"sucks", 1}
  };
  ASSERT_EQUAL(stats.word_frequences, expected);
}

set<string> ReadKeyWords(istream& is) {
  return {istream_iterator<string>(is), istream_iterator<string>()};
}

void TestMtAgainstSt() {
  ifstream key_words_input("key_words.txt");
  const auto key_words_data = ReadKeyWords(key_words_input);
  const set<string> key_words(key_words_data.begin(), key_words_data.end());

  Stats st_stats, mt_stats;
  {
    ifstream text_input("text.txt");
    LOG_DURATION("Single thread");
    st_stats = ExploreKeyWordsSingleThread(key_words, text_input);
  }
  {
    ifstream text_input("text.txt");
    LOG_DURATION("Multi thread");
    mt_stats = ExploreKeyWords(key_words, text_input);
  }

  ASSERT_EQUAL(st_stats.word_frequences, mt_stats.word_frequences);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestBasic);
  RUN_TEST(tr, TestMtAgainstSt);
}
