#pragma once

#include <cstdint>
#include <algorithm>
#include <utility>

using namespace std;

template <typename T>
class SimpleVector {
public:
  SimpleVector() = default;
  explicit SimpleVector(size_t size);
  SimpleVector(const SimpleVector<T>& other);
  SimpleVector(SimpleVector<T>&& other);

  void operator=(const SimpleVector<T>& rhs);
  void operator=(SimpleVector<T>&& rhs);

  ~SimpleVector();

  T& operator[](size_t index);

  T* begin();
  T* end();
  const T* begin() const;
  const T* end() const;

  size_t Size() const;
  size_t Capacity() const;

  //void PushBack(const T& value);
  //void PushBack(T&& value);

  void PushBack(T value);

private:
  T* data = nullptr;
  size_t size = 0;
  size_t capacity = 0;

  void ExpandIfNeeded();
};



template <typename T>
SimpleVector<T>::SimpleVector(size_t size)
  : data(new T[size])
  , size(size)
  , capacity(size)
{
}

template <typename T>
SimpleVector<T>::SimpleVector(const SimpleVector<T>& other)
  : data(new T[other.capacity])
  , size(other.size)
  , capacity(other.capacity)
{
	copy(other.begin(), other.end(), begin());
}

template <typename T>
SimpleVector<T>::SimpleVector(SimpleVector<T>&& other)
  : data(other.data)
  , size(other.size)
  , capacity(other.capacity)
{
	other.data = nullptr;
	other.size = other.capacity = 0;
}


template <typename T>
SimpleVector<T>::~SimpleVector() {
  delete[] data;
}


template <typename T>
void SimpleVector<T>::operator=(const SimpleVector<T>& rhs) {
	if (rhs.size <= capacity) {
		copy(rhs.begin(), rhs.end(), begin());
		size = rhs.size;
	} else {
		SimpleVector<T> tmp(rhs);
		swap(tmp.data, data);
		swap(tmp.size, size);
		swap(tmp.capacity, capacity);
	}
}

template <typename T>
void SimpleVector<T>::operator=(SimpleVector<T>&& rhs) {
	delete[] data;
	data = rhs.data;
	size = rhs.size;
	capacity = rhs.capacity;

	rhs.data = nullptr;
	rhs.size = rhs.capacity = 0;
}


template <typename T>
T& SimpleVector<T>::operator[](size_t index) {
  return data[index];
}


template <typename T>
size_t SimpleVector<T>::Size() const {
  return size;
}

template <typename T>
size_t SimpleVector<T>::Capacity() const {
  return capacity;
}

template <typename T>
void SimpleVector<T>::ExpandIfNeeded() {
  if (size >= capacity) {
    auto new_cap = capacity == 0 ? 1 : 2 * capacity;
    auto new_data = new T[new_cap];
    move(begin(), end(), new_data);
    delete[] data;
    data = new_data;
    capacity = new_cap;
  }
}

template <typename T>
void SimpleVector<T>::PushBack(T value) {
  ExpandIfNeeded();
  data[size++] = move(value);
}


template <typename T>
T* SimpleVector<T>::begin() {
  return data;
}

template <typename T>
T* SimpleVector<T>::end() {
  return data + size;
}

template <typename T>
const T* SimpleVector<T>::begin() const {
  return data;
}

template <typename T>
const T* SimpleVector<T>::end() const {
  return data + size;
}
