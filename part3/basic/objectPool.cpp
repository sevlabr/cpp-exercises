#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>

using namespace std;

template <class T>
class ObjectPool {
public:
  T* Allocate() {
  	if (!free.empty()) {
  		return Move();
  	}
  	T* to_alloc = new T;
  	allocated.insert(to_alloc);
  	return to_alloc;
  }

  T* TryAllocate() {
  	if (!free.empty()) {
  		return Move();
  	}
  	return nullptr;
  }

  void Deallocate(T* object) {
  	if (allocated.count(object) == 1) {
  		free.push(object);
  		allocated.erase(object);
  	} else {
  		throw invalid_argument("");
  	}
  }

  ~ObjectPool() {
  	for (auto alloc_ptr : allocated) {
  		delete alloc_ptr;
  	}
  	allocated.clear();
  	while (!free.empty()) {
  		delete free.front();
  		free.pop();
  	}
  }

private:
  set<T*> allocated;
  queue<T*> free;

  T* Move() {
  	//T*& to_alloc = free.front(); - this works
  	T* to_alloc = free.front(); // - this works
  	//auto to_alloc = free.front(); - this works
  	free.pop();
  	allocated.insert(to_alloc);
  	return to_alloc;
  }
};

void TestObjectPool() {
  ObjectPool<string> pool;

  auto p1 = pool.Allocate();
  auto p2 = pool.Allocate();
  auto p3 = pool.Allocate();

  *p1 = "first";
  *p2 = "second";
  *p3 = "third";

  pool.Deallocate(p2);
  ASSERT_EQUAL(*pool.Allocate(), "second");

  pool.Deallocate(p3);
  pool.Deallocate(p1);
  ASSERT_EQUAL(*pool.Allocate(), "third");
  ASSERT_EQUAL(*pool.Allocate(), "first");

  pool.Deallocate(p1);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestObjectPool);
  return 0;
}
