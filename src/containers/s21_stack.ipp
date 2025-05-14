#pragma once

using namespace s21;

template <typename T>
stack<T>::stack(std::initializer_list<value_type> const& items) {
  head = NULL;
  s_size = items.size();
  arr = new value_type[s_size];
  for (auto it = items.begin(), i = 0; it != items.end(); it++, i++) {
    arr[i] = *it;
    head = &arr[i];
  }
}

template <typename T>
stack<T>::stack(const stack& s) : head(nullptr), arr(nullptr), s_size(0) {
  for (int i = 0; i < s.s_size; i++) {
    this->push(s.arr[i]);
  }
}

template <typename T>
stack<T>::stack(stack&& s) : head(s.head), arr(s.arr), s_size(s.s_size) {
  s.head = NULL;
  s.arr = NULL;
  s.s_size = 0;
}

template <typename T>
stack<T>::~stack() {
  if (arr) delete[] arr;
}

template <typename T>
stack<T> stack<T>::operator=(stack&& s) {
  return std::move(s);
}

template <typename T>
const T& stack<T>::top() {
  return *head;
}

template <typename T>
bool stack<T>::empty() {
  return s_size == 0;
}

template <typename T>
size_t stack<T>::size() {
  return s_size;
}

template <typename T>
void stack<T>::push(const_reference value) {
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

template <typename T>
void stack<T>::pop() {
  value_type* t_arr = arr;
  arr = new value_type[s_size--];
  for (int i = 0; i < s_size; i++) {
    arr[i] = t_arr[i];
  }
  head = &arr[s_size - 1];
  delete[] t_arr;
}

template <typename T>
void stack<T>::swap(stack& other) {
  std::swap(head, other.head);
  std::swap(arr, other.arr);
  std::swap(s_size, other.s_size);
}

template <typename T>
template <typename... Args>
void stack<T>::insert_many_front(Args&&... args) {
  for (auto i : {args...}) {
    if (!std::is_same<decltype(i), value_type>::value)
      throw std::out_of_range(TYPE_S);
    this->push(i);
  }
}
