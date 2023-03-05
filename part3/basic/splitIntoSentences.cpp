#include "test_runner.h"

#include <vector>

using namespace std;

template <typename Token>
using Sentence = vector<Token>;

template <typename Token>
bool IsEndSentence(const size_t& i, const vector<Token>& tokens) {
	return tokens[i].IsEndSentencePunctuation();
}

template <typename Token>
bool IsNextSentenceBeginning(const size_t& i, const vector<Token>& tokens) {
	return i != tokens.size() - 1 && !IsEndSentence(i + 1, tokens);
}

template <typename Token>
vector<Sentence<Token>> SplitIntoSentences(vector<Token> tokens) {
	vector<Sentence<Token>> result;
	bool make_new_sentence = true;
	for (size_t i = 0; i < tokens.size(); ++i) {
		if (make_new_sentence) {
			result.push_back({});
			result.back().push_back(move(tokens[i]));
			make_new_sentence = false;
			if (
					result.back().back().IsEndSentencePunctuation() &&
					IsNextSentenceBeginning(i, tokens)
					)
			{
				make_new_sentence = true;
			}
		} else if (!IsEndSentence(i, tokens)) {
			result.back().push_back(move(tokens[i]));
		} else if (IsEndSentence(i, tokens)) {
			result.back().push_back(move(tokens[i]));
			if (IsNextSentenceBeginning(i, tokens)) {
				make_new_sentence = true;
			}
		}
	}
	return result;
}


struct TestToken {
  string data;
  bool is_end_sentence_punctuation = false;

  bool IsEndSentencePunctuation() const {
    return is_end_sentence_punctuation;
  }
  bool operator==(const TestToken& other) const {
    return data == other.data && is_end_sentence_punctuation == other.is_end_sentence_punctuation;
  }
};

ostream& operator<<(ostream& stream, const TestToken& token) {
  return stream << token.data;
}

void TestSplitting() {
  ASSERT_EQUAL(
    SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!"}})),
    vector<Sentence<TestToken>>({
        {{"Split"}, {"into"}, {"sentences"}, {"!"}}
    })
  );

  ASSERT_EQUAL(
    SplitIntoSentences(vector<TestToken>({{"!", true}, {"!", true}, {"!", true}, {"!", true}})),
    vector<Sentence<TestToken>>({
        {{"!", true}, {"!", true}, {"!", true}, {"!", true}}
    })
  );

  ASSERT_EQUAL(
    SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!", true}})),
    vector<Sentence<TestToken>>({
        {{"Split"}, {"into"}, {"sentences"}, {"!", true}}
    })
  );

  ASSERT_EQUAL(
    SplitIntoSentences(vector<TestToken>({
  			{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true},
				{"Without"}, {"copies"}, {".", true}}
    )),
    vector<Sentence<TestToken>>({
        {{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}},
        {{"Without"}, {"copies"}, {".", true}},
    })
  );

  ASSERT_EQUAL(
    SplitIntoSentences(vector<TestToken>({
  			{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true},
				{"Without"}, {"copies"}, {"."}}
    )),
    vector<Sentence<TestToken>>({
        {{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}},
        {{"Without"}, {"copies"}, {"."}},
    })
  );

  ASSERT_EQUAL(
    SplitIntoSentences(vector<TestToken>({
  			{"!", true}, {"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true},
				{"Without"}, {"copies"}, {"."}}
    )),
    vector<Sentence<TestToken>>({
  			{{"!", true}},
        {{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}},
        {{"Without"}, {"copies"}, {"."}},
    })
  );
}

void TestCopying() {
	vector<TestToken> source = {{"Test"}, {"copying"}, {".", true}};
	vector<Sentence<TestToken>> target = SplitIntoSentences(source);
	ASSERT_EQUAL(source.size(), 3u);
	ASSERT_EQUAL(target.size(), 1u);
	ASSERT_EQUAL(target[0].size(), 3u);

	ASSERT_EQUAL(
			target,
			vector<Sentence<TestToken>>({{{"Test"}, {"copying"}, {".", true}}})
	);

	vector<TestToken> new_source = {{"Test"}, {"no copying"}, {"!", true}};
	target = SplitIntoSentences(move(new_source));
	ASSERT_EQUAL(new_source.size(), 0u);
	ASSERT_EQUAL(target.size(), 1u);
	ASSERT_EQUAL(target[0].size(), 3u);

	ASSERT_EQUAL(
			target,
			vector<Sentence<TestToken>>({{{"Test"}, {"no copying"}, {"!", true}}})
	);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSplitting);
  RUN_TEST(tr, TestCopying);
  return 0;
}
