#pragma once

#include <vector>

using namespace std;

template <typename Iterator>
class IteratorRange {
public:
  IteratorRange(Iterator begin, Iterator end)
    : first(begin)
    , last(end)
    , size_(distance(first, last))
  {
  }

  Iterator begin() const;
  Iterator end() const;
  size_t size() const;

private:
  Iterator first, last;
  size_t size_;
};

template <typename Iterator>
class Paginator {
private:
  vector<IteratorRange<Iterator>> pages;

public:
  Paginator(Iterator begin, Iterator end, size_t page_size);

  auto begin() const;
  auto end() const;
  size_t size() const;
};

template <typename Iterator>
Paginator<Iterator> MakePaginator(Iterator begin, Iterator end, const size_t& page_size);

template <typename C>
auto Paginate(C& c, size_t page_size);
