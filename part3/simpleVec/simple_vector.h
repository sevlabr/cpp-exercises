#pragma once

#include <cstdlib>

template <typename T>
class SimpleVector {
public:
  SimpleVector() {
  	data = nullptr;
  	end_ = data;
  	capacity_ = 0;
  }

  explicit SimpleVector(size_t size) {
  	if (size == 0) {
  		SimpleVector();
  	} else {
  		data = new T[size];
  		end_ = data + size;
  		capacity_ = size;
  	}
  }

  ~SimpleVector() {
  	delete[] data;
  }

  T& operator[](size_t index) {
  	return data[index];
  }

  T* begin() { return data; }
  T* end() { return end_; }

  const T* begin() const { return data; }
  const T* end() const { return end_; }

  size_t Size() const {
  	return end_ - data;
  }

  size_t Capacity() const {
  	return capacity_;
  }

  void PushBack(const T& value) {
  	if (Capacity() == 0) {
  		data = new T[1];
  		*data = value;
  		end_ = data + 1;
  		capacity_ = 1;
  	} else if (Size() == Capacity()) {
  		T* new_data = new T[2 * Capacity()];
  		capacity_ = 2 * Size();
  		for (size_t i = 0; i < Size(); ++i) {
  			new_data[i] = data[i];
  		}
  		new_data[Size()] = value;
  		size_t old_size = Size();
  		end_ = new_data + old_size + 1;
  		delete[] data;
  		data = new_data;
  	} else if (Size() < Capacity()) {
  		*end_ = value;
  		++end_;
  		/*data[Size()] = value;
  		size_t old_size = Size();
  		end_ = data + old_size + 1;*/
  	}
  }

private:
  T* data;
  T* end_;
  size_t capacity_;
};
