#include "profile.h"

#include <iostream>
#include <vector>
#include <numeric>
#include <future>

using namespace std;

int SumTwoVectorsNormally(const vector<int>& one, const vector<int>& two) {
	return accumulate(begin(one), end(one), 0)
			+ accumulate(begin(two), end(two), 0);
}

int SumTwoVectorsAsync(const vector<int>& one, const vector<int>& two) {
	future<int> f = async([&one]{
		return accumulate(begin(one), end(one), 0);
	});
	int result = accumulate(begin(two), end(two), 0);
	return result + f.get();
}

const int SIZE = 1'000'000'000;

int main() {
	LOG_DURATION("Total");
	vector<int> one(SIZE, 1);
	vector<int> two(SIZE, 1);
	{
		LOG_DURATION("Normal");
		cout << SumTwoVectorsNormally(one, two) << '\n';
	}
	{
		LOG_DURATION("Async");
		cout << SumTwoVectorsAsync(one, two) << '\n';
	}
	return 0;
}
