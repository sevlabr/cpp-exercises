#include <string>
#include <list>
#include <vector>
#include <iterator>

#include "test_runner.h"
#include "profile.h"

using namespace std;

class Editor {
 public:
  Editor()
 	 : data(),
		 cursor(begin(data)),
		 buffer_begin(0)
 	 {
  	buffer.reserve(MAX_SIZE);
 	 }

  void Left() {
  	if (cursor != begin(data)) {
  		--cursor;
  	}
  }

  void Right() {
  	if (!data.empty() && cursor != end(data)) {
  		++cursor;
  	}
  }

  void Insert(char token) {
  	data.insert(cursor, token);
  }

  void Cut(size_t tokens = 1) {
  	if (tokens == 0) {
  		buffer_begin += buffer.size();
  	} else {
  		Copy(tokens);
  		const size_t dist = static_cast<size_t>(distance(cursor, end(data)));
  		if (tokens > dist) {
  			tokens = dist;
  		}
  		if (tokens == data.size()) {
  			data.clear();
  			cursor = begin(data);
  		} else if (cursor == begin(data)) {
  			data.erase(cursor, next(cursor, tokens));
  			cursor = begin(data);
  		} else {
  			auto precursor = prev(cursor);
  			data.erase(cursor, next(cursor, tokens));
  			cursor = next(precursor);
  		}
  	}
  }

  void Copy(size_t tokens = 1) {
  	if (tokens == 0) {
  		buffer_begin += buffer.size();
  	} else {
  		buffer_begin += buffer.size();
  		auto tmp_cursor = cursor;
  		while(tmp_cursor != end(data) && tokens > 0) {
  			buffer.push_back(*tmp_cursor);
  			++tmp_cursor;
  			--tokens;
  		}
  	}
  }

  void Paste() {
  	if (!buffer.empty()) {
  		data.insert(cursor,
  				buffer_begin + begin(buffer),
					end(buffer));
  		// cursor = next(cursor, buffer.size() - buffer_begin);
  	}
  }

  string GetText() const {
  	return string(begin(data), end(data));
  }

  string GetBuffer() const {
  	return string(buffer_begin + begin(buffer),
  			buffer_begin + end(buffer));
  }

  size_t GetCursorDist() {
  	return static_cast<size_t>(distance(begin(data), cursor));
  }

 private:
  static const int MAX_SIZE = 1'000'000;

  list<char> data;
  typename list<char>::iterator cursor;

  vector<char> buffer;
  size_t buffer_begin;
};


void TypeText(Editor& editor, const string& text) {
  for(char c : text) {
    editor.Insert(c);
  }
}

/*int main() {
	Editor editor;
	TypeText(editor, "he");
	ASSERT_EQUAL(editor.GetText(), "he");
}*/

void TestEditing() {
  {
    Editor editor;

    const size_t text_len = 12;
    const size_t first_part_len = 7;
    TypeText(editor, "hello, world");
    ASSERT_EQUAL(editor.GetText(), "hello, world");
    for(size_t i = 0; i < text_len; ++i) {
      editor.Left();
    }
    editor.Cut(first_part_len);
    //ASSERT_EQUAL(editor.GetBuffer(), "hello, ");
    ASSERT_EQUAL(editor.GetText(), "world");
    //ASSERT_EQUAL(editor.GetCursorDist(), static_cast<size_t>(0));
    for(size_t i = 0; i < text_len - first_part_len; ++i) {
      editor.Right();
    }
    //ASSERT_EQUAL(editor.GetCursor(), 5);
    TypeText(editor, ", ");
    ASSERT_EQUAL(editor.GetText(), "world, ");
    editor.Paste();
    editor.Left();
    editor.Left();
    editor.Cut(3);

    ASSERT_EQUAL(editor.GetText(), "world, hello");
  }
  {
    Editor editor;

    TypeText(editor, "misprnit");
    editor.Left();
    editor.Left();
    editor.Left();
    editor.Cut(1);
    editor.Right();
    editor.Paste();

    ASSERT_EQUAL(editor.GetText(), "misprint");
  }
}

void TestReverse() {
  Editor editor;

  const string text = "esreveR";
  for(char c : text) {
    editor.Insert(c);
    editor.Left();
  }

  ASSERT_EQUAL(editor.GetText(), "Reverse");
}

void TestNoText() {
  Editor editor;
  ASSERT_EQUAL(editor.GetText(), "");

  editor.Left();
  editor.Left();
  editor.Right();
  editor.Right();
  editor.Copy(0);
  editor.Cut(0);
  editor.Paste();

  ASSERT_EQUAL(editor.GetText(), "");
}

void TestEmptyBuffer() {
  Editor editor;

  editor.Paste();
  TypeText(editor, "example");
  editor.Left();
  editor.Left();
  editor.Paste();
  editor.Right();
  editor.Paste();
  editor.Copy(0);
  editor.Paste();
  editor.Left();
  editor.Cut(0);
  editor.Paste();

  ASSERT_EQUAL(editor.GetText(), "example");
}

void TestBenchmark() {
	const size_t TEST_COUNT = 1'000'000;
	{
		LOG_DURATION("total");
		Editor e;
		TypeText(e, "a");
		for (size_t i = 0; i < TEST_COUNT; ++i) {
			e.Cut(1);
			e.Paste();
			e.Right();
		}
	}
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestEditing);
  RUN_TEST(tr, TestReverse);
  RUN_TEST(tr, TestNoText);
  RUN_TEST(tr, TestEmptyBuffer);
  RUN_TEST(tr, TestBenchmark);
  return 0;
}
