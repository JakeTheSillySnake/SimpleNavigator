#ifndef LIST_H
#define LIST_H

#include <iostream>

using namespace std;

template <typename T>
class List {
 public:
  // node base
  struct node_base {
    node_base* next;
    node_base* prev;
    T data;
  };
  node_base* head;
  node_base* tail;
  int size = 0;

  // List member types
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;

  // constructors
  List() : head(NULL), tail(NULL) {}
  ~List() { clear(); }

  const_reference front() noexcept { return head->data; }
  const_reference back() noexcept { return tail->data; }
  bool empty() noexcept { return size == 0; }

  void clear() noexcept {
    while (tail) {
      pop_front();
    }
  }

  void push_back(const_reference value) noexcept {
    node_base* tmp = new node_base;
    tmp->data = value;
    tmp->next = NULL;
    tmp->prev = NULL;
    if (!tail) {
      tail = tmp;
      head = tmp;
    } else {
      tail->next = tmp;
      tmp->prev = tail;
      tail = tmp;
    }
    size++;
  }

  value_type pop_front() noexcept {
    value_type t_val = 0U;
    if (head->next) {
      node_base* tmp = head->next;
      t_val = head->data;
      delete head;
      head = tmp;
      head->prev = NULL;
    } else if (head) {
      t_val = head->data;
      delete head;
      head = NULL;
      tail = NULL;
    }
    size--;
    return t_val;
  }
};

#endif