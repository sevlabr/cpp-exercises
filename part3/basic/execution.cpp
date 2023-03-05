#include "profile.h"

#include <iostream>
#include <vector>
#include <cstdint>
#include <future>
#include <algorithm>
//#include <execution>

using namespace std;

template <typename ContainerOfVectors>
void GenerateSingleThread(
		ContainerOfVectors& result,
		size_t first_row,
		size_t column_size
) {
	for_each(
		// execution::par
		begin(result),
		end(result),
		[&first_row, column_size](vector<int>& row) {
			row.reserve(column_size);
			for (size_t column = 0; column < column_size; ++column) {
				row.push_back(first_row ^ column);
			}
			++first_row;
		}
	);
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

int main() {
	// 195928050144
	// 195928050144
	LOG_DURATION("Total");
	const size_t matrix_size = 7000;
	vector<vector<int>> matrix;

	{
		LOG_DURATION("Single thread generation");
		matrix = GenerateSingleThread(matrix_size);
	}
	{
		LOG_DURATION("Single thread sum");
		cout << SumSingleThread(matrix) << endl;
	}

	return 0;
}
