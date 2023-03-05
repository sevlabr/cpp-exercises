#pragma once

#include <algorithm>

using namespace std;

template <typename It>
class IteratorRange {
public:
  IteratorRange(It first, It last) : first(first), last(last) {
  }

  It begin() const {
    return first;
  }

  It end() const {
    return last;
  }

  size_t size() const {
    return last - first;
  }

private:
  It first, last;
};

template <typename It>
IteratorRange<It> MakeIteratorRange(It first, It second) {
	return {first, second};
}

template <typename Container>
auto Head(Container& c, int top) {
  return MakeIteratorRange(begin(c), begin(c) + min<size_t>(max(top, 0), c.size()));
}
