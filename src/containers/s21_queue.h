#ifndef S21_QUEUE_H
#define S21_QUEUE_H
#include "s21_list.h"

namespace s21 {

template <typename T, typename Container = list<T>>
class queue {
 public:
  using value_type = typename Container::value_type;
  using reference = typename Container::reference;
  using const_reference = typename Container::const_reference;
  using size_type = typename Container::size_type;

 protected:
  Container t1;

 public:
  queue() : t1() {}
  queue(std::initializer_list<value_type> const &items) : t1(items) {}
  queue(const queue &q) : t1(q.t1) {}
  queue(queue &&q) : t1(std::move(q.t1)) {}
  ~queue() {}
  queue &operator=(queue &&q) {
    this->t1 = std::move(q.t1);
    return *this;
  }

  const_reference front() { return t1.front(); }
  const_reference back() { return t1.back(); }

  bool empty() { return t1.empty(); }
  size_type size() { return t1.size(); }

  void push(const_reference value) { this->t1.push_back(value); }
  void pop() { this->t1.pop_front(); }
  void swap(queue &other) { this->t1.swap(other.t1); }
};

}  // namespace s21
#endif  // S21_QUEUE_H