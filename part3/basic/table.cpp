#include "test_runner.h"

#include <vector>
#include <utility>
#include <algorithm>
#include <sstream>

using namespace std;

template <typename Iterator>
struct IteratorRange {
	Iterator first;
	Iterator last;

	Iterator begin() { return first; }
	Iterator end() { return last; }
};

template <typename T>
IteratorRange<typename vector<T>::iterator>
Head(vector<T>& v, const size_t& top) {
	return {v.begin(), v.begin() + min(v.size(), top)};
}

template <typename T>
class Table {
public:
	Table(const size_t& rows, const size_t& cols) {
		rows_ = rows;
		cols_ = cols;
		if (rows == 0 || cols == 0) {
			rows_ = 0;
			cols_ = 0;
		}
		vector<vector<T>> data(rows_);
		for (auto& row : data) {
			vector<T> col(cols_);
			row = col;
		}
		data_ = data;
	}

	vector<T>& operator[](const size_t& index) {
		return data_[index];
	}

	const vector<T>& operator[](const size_t& index) const {
		return data_[index];
	}

	pair<size_t, size_t> Size() const {
		return make_pair(rows_, cols_);
	}

	void Resize(const size_t& rows, const size_t& cols) {
		rows_ = rows;
		cols_ = cols;
		if (rows == 0 || cols == 0) {
			rows_ = 0;
			cols_ = 0;
		}
		data_.resize(rows_);
		for (auto& row : Head(data_, rows_)) {
			row.resize(cols_);
		}
	}

private:
	size_t rows_;
	size_t cols_;
	vector<vector<T>> data_;
};


void TestTable() {
  Table<int> t(1, 1);
  ASSERT_EQUAL(t.Size().first, 1u);
  ASSERT_EQUAL(t.Size().second, 1u);
  t[0][0] = 42;
  ASSERT_EQUAL(t[0][0], 42);
  t.Resize(3, 4);
  ASSERT_EQUAL(t.Size().first, 3u);
  ASSERT_EQUAL(t.Size().second, 4u);
}

void TestConstructor() {
	{
		Table<int> t(2, 2);
		ASSERT_EQUAL(t.Size().first, 2u);
		ASSERT_EQUAL(t.Size().second, 2u);
	}
	{
		Table<int> t(5, 2);
		ASSERT_EQUAL(t.Size().first, 5u);
		ASSERT_EQUAL(t.Size().second, 2u);
	}
	{
		Table<int> t(4, 1);
		ASSERT_EQUAL(t.Size().first, 4u);
		ASSERT_EQUAL(t.Size().second, 1u);
	}
	{
		Table<int> t(0, 5);
		ASSERT_EQUAL(t.Size().first, 0u);
		ASSERT_EQUAL(t.Size().second, 0u);
	}
	{
		Table<int> t(1, 0);
		ASSERT_EQUAL(t.Size().first, 0u);
		ASSERT_EQUAL(t.Size().second, 0u);
	}
	{
		Table<int> t(0, 0);
		ASSERT_EQUAL(t.Size().first, 0u);
		ASSERT_EQUAL(t.Size().second, 0u);
	}
}

void TestOperators() {
	{
		Table<int> t(2, 2);
		ostringstream oss;
		t[0][0] = 42;
		t[0][1] = -11;
		t[1][0] = -15;
		t[1][1] = 0;
		oss << t[0][0] << " " << t[0][1] << " " << t[1][0] << " " << t[1][1];
		ASSERT_EQUAL(oss.str(), "42 -11 -15 0");
	}
}

void TestResize() {
	{
		Table<int> t(3, 3);
		ostringstream oss;
		t[0][0] = 42;
		t[0][1] = -11;
		t[0][2] = -1;
		t[1][0] = -15;
		t[1][1] = 0;
		t[1][2] = 1;
		t[2][0] = 1;
		t[2][1] = 1;
		t[2][2] = 1;

		t.Resize(3, 2);
		ASSERT_EQUAL(t.Size().first, 3u);
		ASSERT_EQUAL(t.Size().second, 2u);
		oss << t[0][0] << t[0][1] << t[0][2] << t[1][0] << t[1][1] << t[1][2];
		ASSERT_EQUAL(oss.str(), "42-11-1-1501");
	}
	{
		Table<int> t(3, 3);
		ostringstream oss;
		t[0][0] = 42;
		t[0][1] = -11;
		t[0][2] = -1;
		t[1][0] = -15;
		t[1][1] = 0;
		t[1][2] = 1;
		t[2][0] = 1;
		t[2][1] = 1;
		t[2][2] = 1;

		t.Resize(2, 3);
		ASSERT_EQUAL(t.Size().first, 2u);
		ASSERT_EQUAL(t.Size().second, 3u);
		oss << t[0][0] << t[0][1] << t[1][0] << t[1][1] << t[2][0] << t[2][1];
		ASSERT_EQUAL(oss.str(), "42-11-15011");
	}
	{
		Table<int> t(3, 3);
		ostringstream oss;
		t[0][0] = 42;
		t[0][1] = -11;
		t[0][2] = -1;
		t[1][0] = -15;
		t[1][1] = 0;
		t[1][2] = 1;
		t[2][0] = 1;
		t[2][1] = 1;
		t[2][2] = 1;

		t.Resize(4, 4);
		ASSERT_EQUAL(t.Size().first, 4u);
		ASSERT_EQUAL(t.Size().second, 4u);
		oss << t[0][0] << t[0][1] << t[1][0] << t[1][1] << t[2][0] << t[2][1];
		ASSERT_EQUAL(oss.str(), "42-11-15011");
		ostringstream oss1;
		oss1 << t[0][0] << t[0][1] << t[0][2] << t[1][0] << t[1][1] << t[1][2];
		ASSERT_EQUAL(oss1.str(), "42-11-1-1501");
		ostringstream oss2;
		oss2 << t[0][0] << t[0][1] << t[0][2] << t[1][0] << t[1][1] << t[1][2] << t[2][0] << t[2][1]
																								 << t[2][2];
		ASSERT_EQUAL(oss2.str(), "42-11-1-1501111");

		t.Resize(3, 3);
		ASSERT_EQUAL(t.Size().first, 3u);
		ASSERT_EQUAL(t.Size().second, 3u);
		ostringstream oss3;
		oss3 << t[0][0] << t[0][1] << t[0][2] << t[1][0] << t[1][1] << t[1][2] << t[2][0] << t[2][1]
																								 << t[2][2];
		ASSERT_EQUAL(oss3.str(), "42-11-1-1501111");

		t.Resize(3, 4);
		ASSERT_EQUAL(t.Size().first, 3u);
		ASSERT_EQUAL(t.Size().second, 4u);
		ostringstream oss4;
		oss4 << t[0][0] << t[0][1] << t[0][2] << t[1][0] << t[1][1] << t[1][2] << t[2][0] << t[2][1]
																								 << t[2][2];
		ASSERT_EQUAL(oss4.str(), "42-11-1-1501111");

		t.Resize(4, 3);
		ASSERT_EQUAL(t.Size().first, 4u);
		ASSERT_EQUAL(t.Size().second, 3u);
		ostringstream oss5;
		oss5 << t[0][0] << t[0][1] << t[0][2] << t[1][0] << t[1][1] << t[1][2] << t[2][0] << t[2][1]
																								 << t[2][2];
		ASSERT_EQUAL(oss5.str(), "42-11-1-1501111");

		t[3][2] = 100;
		ostringstream oss6;
		oss6 << t[3][2];
		ASSERT_EQUAL(oss6.str(), "100")
	}
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestTable);
  RUN_TEST(tr, TestConstructor);
  RUN_TEST(tr, TestOperators);
  RUN_TEST(tr, TestResize);
  return 0;
}
