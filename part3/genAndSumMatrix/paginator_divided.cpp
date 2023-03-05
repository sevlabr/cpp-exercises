#include "paginator_divided.h"

using namespace std;

template <typename Iterator>
Iterator IteratorRange<Iterator>::begin() const {
	return first;
}

template <typename Iterator>
Iterator IteratorRange<Iterator>::end() const {
	return last;
}

template <typename Iterator>
size_t IteratorRange<Iterator>::size() const {
	return size_;
}

template <typename Iterator>
Paginator<Iterator>::Paginator(Iterator begin, Iterator end, size_t page_size) {
  for (size_t left = distance(begin, end); left > 0; ) {
    size_t current_page_size = min(page_size, left);
    Iterator current_page_end = next(begin, current_page_size);
    pages.push_back({begin, current_page_end});

    left -= current_page_size;
    begin = current_page_end;
  }
}

template <typename Iterator>
auto Paginator<Iterator>::begin() const {
	return pages.begin();
}

template <typename Iterator>
auto Paginator<Iterator>::end() const {
  return pages.end();
}

template <typename Iterator>
size_t Paginator<Iterator>::size() const {
  return pages.size();
}

template <typename Iterator>
Paginator<Iterator> MakePaginator(Iterator begin, Iterator end, const size_t& page_size) {
	return {begin, end, page_size};
}

template <typename C>
auto Paginate(C& c, size_t page_size) {
	return MakePaginator(c.begin(), c.end(), page_size);
}
