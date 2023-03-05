#include "test_runner.h"

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>

using namespace std;

template <typename T>
class Deque {
public:
	Deque() {
		vector<T> init_f, init_b;
		front = init_f; back = init_b;
	}

	bool Empty() const {
		if (front.empty() && back.empty()) {
			return true;
		}
		return false;
	}

	size_t Size() const {
		return front.size() + back.size();
	}

	T& operator[](size_t index) {
		++index;
		if (index <= front.size()) {
			return front[front.size() - index];
		}
		--index;
		return back[index - front.size()];
	}

	const T& operator[](size_t index) const {
		++index;
		if (index <= front.size()) {
			return front[front.size() - index];
		}
		--index;
		return back[index - front.size()];
	}

	void CheckIndex(const size_t& index) const {
		if (Empty() || index >= Size()) {
			throw out_of_range("");
		}
	}

	T& At(size_t index) {
		CheckIndex(index);
		++index;
		if (index <= front.size()) {
			return front[front.size() - index];
		}
		--index;
		return back[index - front.size()];
	}

	const T& At(size_t index) const {
		CheckIndex(index);
		++index;
		if (index <= front.size()) {
			return front[front.size() - index];
		}
		--index;
		return back[index - front.size()];
	}

	T& Front() {
		if (!front.empty()) {
			return front.back();
		}
		return back.front();
	}

	const T& Front() const {
		if (!front.empty()) {
			return front.back();
		}
		return back.front();
	}

	T& Back() {
		if (!back.empty()) {
			return back.back();
		}
		return front.front();
	}

	const T& Back() const {
		if (!back.empty()) {
			return back.back();
		}
		return front.front();
	}

	void PushBack(const T& val) {
		back.push_back(val);
	}

	void PushFront(const T& val) {
		front.push_back(val);
	}

private:
	vector<T> front;
	vector<T> back;
};

void TestConstructor() {
	Deque<string> s;
	Deque<int> i;
	Deque<double> d;

	ASSERT(s.Empty());
	ASSERT(i.Empty());
	ASSERT(d.Empty());

	ASSERT_EQUAL(s.Size(), 0u);
	ASSERT_EQUAL(i.Size(), 0u);
	ASSERT_EQUAL(d.Size(), 0u);
}

void TestPush() {
	{
		Deque<int> d;

		for (int i = 0; i < 3; ++i) {
			d.PushFront(i);
		}

		ASSERT_EQUAL(d.Empty(), false);
		ASSERT_EQUAL(d.Size(), 3u);

		ostringstream oss;
		for (size_t i = 0; i < 3; ++i) {
			oss << d[i];
		}
		ASSERT_EQUAL(oss.str(), "210");
	}
	{
		Deque<int> d;

		for (int i = 0; i < 3; ++i) {
			d.PushBack(i);
		}

		ASSERT_EQUAL(d.Empty(), false);
		ASSERT_EQUAL(d.Size(), 3u);

		ostringstream oss;
		for (size_t i = 0; i < 3; ++i) {
			oss << d[i];
		}
		ASSERT_EQUAL(oss.str(), "012");
	}
	{
		Deque<int> d;

		d.PushBack(23);
		d.PushFront(-11);
		d.PushFront(0);
		d.PushBack(16);
		ostringstream oss;
		for (size_t i = 0; i < d.Size(); ++i) {
			oss << d[i];
		}
		ASSERT_EQUAL(oss.str(), "0-112316");
	}
}

void TestOperator() {
	{
		Deque<int> d;
		d.PushBack(1);
		d[0] = 3;
		ASSERT_EQUAL(d[0], 3);
		d.PushBack(-1);
		ASSERT_EQUAL(d[1], -1);
		d[1] = 0;
		ASSERT_EQUAL(d[1], 0);
	}
	{
		Deque<int> d;
		d.PushFront(1);
		d[0] = 2;
		ASSERT_EQUAL(d[0], 2);
		d.PushFront(4);
		d[0] = 17;
		ASSERT_EQUAL(d[1], 2);
		ASSERT_EQUAL(d[0], 17);
	}
	{
		Deque<int> d;
		d.PushBack(23);
		d.PushFront(-11);
		d.PushFront(0);
		d.PushBack(16);
		ostringstream oss;
		for (size_t i = 0; i < d.Size(); ++i) {
			++d[i];
			oss << d[i];
		}
		ASSERT_EQUAL(oss.str(), "1-102417");
	}
}

void TestFrontBack() {
	{
		Deque<int> d;
		d.PushBack(1);
		ASSERT_EQUAL(d.Back(), 1);
		ASSERT_EQUAL(d.Front(), 1);

		++d.Back();
		++d.Front();
		ASSERT_EQUAL(d.Back(), 3);
		ASSERT_EQUAL(d.Front(), 3);
	}
	{
		Deque<int> d;
		d.PushFront(1);
		ASSERT_EQUAL(d.Back(), 1);
		ASSERT_EQUAL(d.Front(), 1);

		++d.Back();
		++d.Front();
		ASSERT_EQUAL(d.Back(), 3);
		ASSERT_EQUAL(d.Front(), 3);
	}
	{
		Deque<int> d;
		d.PushBack(1);
		d.PushFront(0);
		ASSERT_EQUAL(d.Back(), 1);
		ASSERT_EQUAL(d.Front(), 0);

		++d.Back();
		++d.Front();
		ASSERT_EQUAL(d.Back(), 2);
		ASSERT_EQUAL(d.Front(), 1);
	}
}

void TestAt() {
	{
		Deque<int> d;
		try {
			++d.At(1);
		} catch(out_of_range&) {}
		try {
			--d.At(0);
		} catch(out_of_range&) {}
		d.PushBack(0);
		ASSERT_EQUAL(d.At(0), 0);
		try {
			cout << d.At(1) << endl;
		} catch(out_of_range&) {}
		++d.At(0);
		ASSERT_EQUAL(d.At(0), 1);
		ostringstream oss;
		oss << d.At(0) << " ok";
		ASSERT_EQUAL(oss.str(), "1 ok");
	}
	{
		Deque<int> d;
		d.PushFront(0);
		ASSERT_EQUAL(d.At(0), 0);
		try {
			--d.At(1);
		} catch(out_of_range&) {}
		try {
			cout << d.At(1) << endl;
		} catch(out_of_range&) {}
		--d.At(0);
		ASSERT_EQUAL(d.At(0), -1);
		ostringstream oss;
		oss << d.At(0) << " ok";
		ASSERT_EQUAL(oss.str(), "-1 ok");
	}
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestConstructor);
	RUN_TEST(tr, TestPush);
	RUN_TEST(tr, TestOperator);
	RUN_TEST(tr, TestFrontBack);
	RUN_TEST(tr, TestAt);
	return 0;
}
