#ifndef STACK_H
#define STACK_H

#include <iostream>

using namespace std;

template <class T>
class Stack {
 public:
  // Stack member types
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;

  value_type* head;

 private:
  value_type* arr;
  int s_size;

 public:
  Stack() : head(NULL), arr(NULL), s_size(0U) {}
  ~Stack() {
    if (arr) delete[] arr;
  }

  const_reference Top() { return *head; }
  bool Empty() { return s_size == 0; }

  void Push(const_reference value) {
    value_type* t_arr = arr;
    arr = new value_type[s_size + 1];
    for (int i = 0; i < s_size; i++) {
      arr[i] = t_arr[i];
    }
    arr[s_size] = value;
    head = &arr[s_size];
    ++s_size;
    delete[] t_arr;
  }

  value_type Pop() {
    value_type* t_arr = arr;
    value_type tmp = arr[s_size - 1];
    arr = new value_type[s_size--];
    for (int i = 0; i < s_size; i++) {
      arr[i] = t_arr[i];
    }
    head = &arr[s_size - 1];
    delete[] t_arr;
    return tmp;
  }
};

#endif