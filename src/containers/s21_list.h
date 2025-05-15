#ifndef LIST_H
#define LIST_H

#include <initializer_list>
#include <iostream>
#include <limits>       // find max size
#include <type_traits>  // find args... type
#include <utility>

#define RANGE "Iterator does not refer to a node in the list."
#define TYPE_L "Argument is not a node pointer."

using namespace std;

namespace s21 {
template <typename T>
class list {
 public:
  // node base
  struct node_base {
    node_base* next;
    node_base* prev;
    T data;
  };
  node_base* head = nullptr;
  node_base* tail = nullptr;

  // inner iterator classes;
  class ListIterator;
  class ListConstIterator;

  // list member types
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = ListIterator;
  using const_iterator = ListConstIterator;
  using size_type = size_t;
  using difference_type = ptrdiff_t;

  // constructors
  list() : head(NULL), tail(NULL) {}
  explicit list(size_type n);
  list(std::initializer_list<value_type> const& items);
  list(const list& l);                // copy
  list(list&& l);                     // move
  ~list();                            // destructor
  list operator=(list&& l) noexcept;  // op overload to move an object

  // element access
  const_reference front() noexcept;
  const_reference back() noexcept;

  // main iterators
  iterator begin() noexcept { return iterator(head); }
  iterator end() noexcept { return iterator(tail->next); }

  // capacity
  bool empty() noexcept;
  size_type size() noexcept;
  size_type max_size() noexcept;

  // modifiers
  void clear() noexcept;
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos) noexcept;
  void push_back(const_reference value) noexcept;
  void pop_back() noexcept;
  void push_front(const_reference value) noexcept;
  void pop_front() noexcept;
  void swap(list& other) noexcept;
  void merge(list& other) noexcept;
  void splice(const_iterator pos, list& other);
  void reverse() noexcept;
  void unique() noexcept;
  void sort() noexcept;

  // param packs
  template <typename... Args>
  iterator insert_many(const_iterator pos, Args&&... args);
  template <typename... Args>
  void insert_many_back(Args&&... args);
  template <typename... Args>
  void insert_many_front(Args&&... args);

  // extra
  node_base* merge_nodes(node_base* a, node_base* b) noexcept;
  void swap_elems(iterator a, iterator b) noexcept;
  void print() noexcept {
    if (!head) return;
    for (auto i = this->begin(); i != this->end(); i++) {
      cout << i.m_ptr->data << " ";
    }
    cout << endl;
  };
};

template <typename T>
class list<T>::ListIterator {
 public:
  using _self = ListIterator;
  using _node = list<T>::node_base;  // actual node in list
  using difference_type = ptrdiff_t;
  using value_type = T;
  using reference = T&;
  using pointer = T*;
  using iterator_category = bidirectional_iterator_tag;

  // only member points to list element
  _node* m_ptr;

  // constructors
  ListIterator() noexcept : m_ptr() {}
  ListIterator(_node* ptr) noexcept : m_ptr(ptr) {}

  // cast to const
  _self _const_cast() const noexcept { return *this; };

  // op overloads
  reference operator*() const noexcept { return m_ptr->data; }
  pointer operator->() const noexcept { return &(m_ptr->data); }
  _self& operator++() noexcept {
    m_ptr = m_ptr->next;
    return *this;
  }
  _self operator++(int) noexcept {
    _self tmp = *this;
    m_ptr = m_ptr->next;
    return tmp;
  }
  _self& operator--() noexcept {
    m_ptr = m_ptr->prev;
    return *this;
  }
  _self operator--(int) noexcept {
    _self tmp = *this;
    m_ptr = m_ptr->prev;
    return tmp;
  }
  friend bool operator==(const _self& a, const _self& b) noexcept {
    return a.m_ptr == b.m_ptr;
  }
  friend bool operator!=(const _self& a, const _self& b) noexcept {
    return a.m_ptr != b.m_ptr;
  }
};

template <typename T>
class list<T>::ListConstIterator {
 public:
  using _self = ListConstIterator;
  using _node = const list<T>::node_base;  // actual node in list
  using iterator = ListIterator;
  using difference_type = ptrdiff_t;
  using value_type = T;
  using reference = const T&;
  using pointer = const T*;
  using iterator_category = bidirectional_iterator_tag;

  // only member points to list element
  _node* m_ptr;

  // constructors
  ListConstIterator() noexcept : m_ptr() {}
  ListConstIterator(_node* ptr) noexcept : m_ptr(ptr) {}
  ListConstIterator(const iterator& a) noexcept : m_ptr(a.m_ptr) {}

  // cast to non-const
  iterator _const_cast() const noexcept {
    return iterator(const_cast<list<T>::node_base*>(m_ptr));
  }

  // op overloads
  reference operator*() const noexcept { return m_ptr->data; }
  pointer operator->() const noexcept { return &(m_ptr->data); }
  _self& operator++() noexcept {
    m_ptr = m_ptr->next;
    return *this;
  }
  _self operator++(int) noexcept {
    _self tmp = *this;
    m_ptr = m_ptr->next;
    return tmp;
  }
  _self& operator--() noexcept {
    m_ptr = m_ptr->prev;
    return *this;
  }
  _self operator--(int) noexcept {
    _self tmp = *this;
    m_ptr = m_ptr->prev;
    return tmp;
  }
  friend bool operator==(const _self& a, const _self& b) noexcept {
    return a.m_ptr == b.m_ptr;
  }
  friend bool operator!=(const _self& a, const _self& b) noexcept {
    return a.m_ptr != b.m_ptr;
  }
};
}  // namespace s21
#include "s21_list.ipp"  // needed for correct compilation
#endif