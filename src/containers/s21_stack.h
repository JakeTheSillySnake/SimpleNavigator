#ifndef STACK_H
#define STACK_H

#include <initializer_list>
#include <iostream>
#include <type_traits>  // find args... type
#include <utility>

#define TYPE_S "Argument is not a suitable value."

using namespace std;

namespace s21 {
template <class T>
class stack {
 public:
  // stack member types
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;

  value_type* head = nullptr;

 private:
  value_type* arr = nullptr;
  int s_size = 0;

 public:
  // constructors
  stack() : head(NULL), arr(NULL), s_size(0U) {}
  stack(std::initializer_list<value_type> const& items);
  stack(const stack& s);       // copy
  stack(stack&& s);            // move
  ~stack();                    // destructor
  stack operator=(stack&& s);  // op overload to move an object

  // element access
  const_reference top();

  // capacity
  bool empty();
  size_type size();

  // modifiers;
  void push(const_reference value);
  void pop();
  void swap(stack& other);

  // param packs
  template <typename... Args>
  void insert_many_front(Args&&... args);

  void print() {
    for (int i = 0; i < s_size; i++) cout << arr[i] << " ";
    cout << endl;
  }
};
}  // namespace s21
#include "s21_stack.ipp"
#endif