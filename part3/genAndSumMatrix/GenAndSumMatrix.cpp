#include "profile.h"
#include "paginator.h"
#include "test_runner.h"

#include <iostream>
#include <vector>
#include <cstdint>
#include <future>

using namespace std;

template <typename ContainerOfVectors>
void GenerateSingleThread(
		ContainerOfVectors& result,
		size_t first_row,
		size_t column_size
) {
	for (auto& row : result) {
		row.reserve(column_size);
		for (size_t column = 0; column < column_size; ++column) {
			row.push_back(first_row ^ column);
		}
		++first_row;
	}
}

vector<vector<int>> GenerateSingleThread(size_t size) {
	vector<vector<int>> result(size);
	GenerateSingleThread(result, 0, size);
	return result;
}

template <typename ContainerOfVectors>
int64_t SumSingleThread(const ContainerOfVectors& matrix) {
	int64_t sum = 0;
	for (const auto& row : matrix) {
		for (const auto& item : row) {
			sum += item;
		}
	}
	return sum;
}

vector<vector<int>> GenerateMultiThread(
		size_t size, size_t page_size
) {
	vector<vector<int>> result(size);
	vector<future<void>> futures;
	size_t first_row = 0;
	for (auto page : Paginate(result, page_size)) {
		futures.push_back(
				async([page, first_row, size] {
						GenerateSingleThread(page, first_row, size);
				})
		);
		first_row += page_size;
	}

	for (auto& f : futures) {
		f.get();
	}

	return result;
}

int64_t CalculateMatrixSum(const vector<vector<int>>& matrix) {
	int64_t sum = 0;
	const size_t page_size = 875;
	vector<future<int64_t>> futures;
	for (const auto& page : Paginate(matrix, page_size)) {
		futures.push_back(
				async([page] {
						return SumSingleThread(page);
				})
		);
	}

	for (auto& f : futures) {
		sum += f.get();
	}

	return sum;
}

void TestCalculateMatrixSum() {
  const vector<vector<int>> matrix = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12},
    {13, 14, 15, 16}
  };
  ASSERT_EQUAL(CalculateMatrixSum(matrix), 136);
}

int main() {
	// 195928050144
	// 195928050144
	LOG_DURATION("Total");
	const size_t matrix_size = 7000;
	const size_t page_size = 875;
	vector<vector<int>> matrix;

  TestRunner tr;
  RUN_TEST(tr, TestCalculateMatrixSum);

	{
		LOG_DURATION("Single thread generation");
		matrix = GenerateSingleThread(matrix_size);
	}
	{
		LOG_DURATION("Multi-thread generation");
		matrix = GenerateMultiThread(matrix_size, page_size);
	}
	{
		LOG_DURATION("Single thread sum");
		cout << SumSingleThread(matrix) << endl;
	}
	{
		LOG_DURATION("Multi-thread sum");
		cout << CalculateMatrixSum(matrix) << endl;
	}

	return 0;
}
