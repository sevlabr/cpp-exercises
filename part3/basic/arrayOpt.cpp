#include "profile.h"
#include <algorithm>
#include <array>
#include <tuple>
#include <vector>
#include <iostream>

using namespace std;

vector<int> BuildVector(int i) {
  return {i, i + 1, i + 2, i + 3, i + 4};
}

tuple<int, int, int, int, int> BuildTuple(int i) {
  return make_tuple(i, i + 1, i + 2, i + 3, i + 4);
}

array<int, 5> BuildArray(int i) {
  //return {i + 4, i + 3, i + 2, i + 1, i};
	return {i, i + 1, i + 2, i + 3, i + 4};
}

const int COUNT = 1000000;

int main() {
  size_t tmp = 0;

  {
    LOG_DURATION("vector");

    for (int i = 0; i < COUNT; ++i) { // C * N
      auto numbers = BuildVector(i);
      tmp += numbers.size();
    }
  }

  cout << "vector: " << tmp << "\n";

  {
    LOG_DURATION("tuple");

    for (int i = 0; i < COUNT; ++i) { // C * N
      auto numbers = BuildTuple(i);
      tmp += std::get<0>(numbers);
    }
  }

  cout << "tuple: " << tmp << "\n";

  {
    LOG_DURATION("array");

    for (int i = 0; i < COUNT; ++i) { // C * N * logN
      auto numbers = BuildArray(i);
      sort(begin(numbers), end(numbers));
      tmp += numbers.size();
    }
  }

  cout << "array: " << tmp << "\n";

  return 0;
}
