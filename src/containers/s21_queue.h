#ifndef S21_QUEUE_H
#define S21_QUEUE_H

#include "s21_list.h"

template <typename T, typename Container = List<T>>
class Queue {
 public:
  using value_type = typename Container::value_type;
  using reference = typename Container::reference;
  using const_reference = typename Container::const_reference;
  using size_type = typename Container::size_type;

 protected:
  Container t1;

 public:
  Queue() : t1() {}
  ~Queue() {}
  const_reference Front() { return t1.front(); }
  const_reference Back() { return t1.back(); }
  bool Empty() { return t1.empty(); }
  void Push(const_reference value) { this->t1.push_back(value); }
  value_type Pop() { return this->t1.pop_front(); }
};

#endif  // S21_QUEUE_H