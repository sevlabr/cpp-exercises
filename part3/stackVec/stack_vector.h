#pragma once

#include <stdexcept>
//#include <iterator>
#include <array>
using namespace std;

template <typename T, size_t N>
class StackVector {
public:
  explicit StackVector(size_t a_size = 0) {
  	if (a_size > N) {
  		throw invalid_argument("Size is bigger than capacity");
  	} else {
  		size = a_size;
  	}
  }

  T& operator[](size_t index);
  const T& operator[](size_t index) const;

  T* begin(); // typename array<T, N>::iterator
  T* end(); // typename array<T, N>::iterator
  const T* begin() const; // typename array<T, N>::const_iterator
  const T* end() const; // typename array<T, N>::const_iterator

  size_t Size() const;
  size_t Capacity() const;

  void PushBack(const T& value);
  T PopBack();

private:
  array<T, N> data;
  size_t size;
};


template <typename T, size_t N>
size_t StackVector<T, N>::Size() const {
	return size;
}

template <typename T, size_t N>
size_t StackVector<T, N>::Capacity() const {
	return N;
}

template <typename T, size_t N>
void StackVector<T, N>::PushBack(const T& value) {
	if (size == N) {
		throw overflow_error("Size is equal to capacity");
	} else {
		data[size] = value;
		++size;
	}
}

template <typename T, size_t N>
T& StackVector<T, N>::operator[](size_t index) {
	return data[index];
}

template <typename T, size_t N>
const T& StackVector<T, N>::operator[](size_t index) const {
	return data[index];
}

template <typename T, size_t N>
T StackVector<T, N>::PopBack() {
	if (size == 0) {
		throw underflow_error("Size is equal to 0");
	} else {
		--size;
		return data[size];
	}
}

template <typename T, size_t N>
T* StackVector<T, N>::begin() {
	//return &data[0]; // - this works
	//return begin(data); // - compile problems in coursera grader
	return data.begin(); // - this works
}

template <typename T, size_t N>
const T* StackVector<T, N>::begin() const {
	//return &data[0]; // - this works
	//return begin(data); // - compile problems in coursera grader
	return data.begin(); // - this works
}

template <typename T, size_t N>
T* StackVector<T, N>::end() {
	//return &data[size]; // - this works
	//return next(begin(data), size); // - compile problems in coursera grader
	//return next(data.begin(), size); // - this works
	return data.begin() + size; // - this works
}

template <typename T, size_t N>
const T* StackVector<T, N>::end() const {
	//return &data[size]; // - this works
	//return next(begin(data), size); // - compile problems in coursera grader
	//return next(data.begin(), size); // - this works
	return data.begin() + size; // - this works
}
