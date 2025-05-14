#pragma once

using namespace s21;

template <typename T>
list<T>::list(size_type n) : head(nullptr), tail(nullptr) {
  for (int i = 0; i < (int)n; i++) {
    this->push_back(0U);
  }
}

template <typename T>
list<T>::list(std::initializer_list<value_type> const& items) {
  head = NULL;
  tail = NULL;
  for (auto i = items.begin(); i != items.end(); i++) {
    this->push_back(*i);
  }
}

template <typename T>
list<T>::list(const list& l) : head(nullptr), tail(nullptr) {
  list<T> tmp;
  tmp.head = l.head;
  tmp.tail = l.tail;
  for (auto i = tmp.begin(); i != tmp.end(); i++) {
    this->push_back(*i);
  }
  tmp.head = NULL;
  tmp.tail = NULL;
}

template <typename T>
list<T>::list(list&& l) : head(l.head), tail(l.tail) {
  l.head = NULL;
  l.tail = NULL;
}

template <typename T>
list<T>::~list() {
  this->clear();
}

template <typename T>
list<T> list<T>::operator=(list&& l) noexcept {
  return std::move(l);
}

template <typename T>
const T& list<T>::front() noexcept {
  return head->data;
}

template <typename T>
const T& list<T>::back() noexcept {
  return tail->data;
}

template <typename T>
bool list<T>::empty() noexcept {
  return head == NULL;
}

template <typename T>
size_t list<T>::size() noexcept {
  int size = 0;
  for (auto it = this->begin(); it != this->end(); ++it) {
    size++;
  }
  return size;
}

template <typename T>
size_t list<T>::max_size() noexcept {
  std::allocator<node_base> tmp;
  return std::allocator_traits<decltype(tmp)>::max_size(tmp);
}

template <typename T>
void list<T>::clear() noexcept {
  while (tail) {
    this->pop_back();
  }
}

template <typename T>
typename list<T>::ListIterator list<T>::insert(iterator pos,
                                               const_reference value) {
  ListIterator iter = pos;
  if (pos == this->begin()) {
    this->push_front(value);
  } else if (pos == this->end()) {
    this->push_back(value);
    iter.m_ptr = tail;
  } else {
    bool found = false;
    for (auto i = this->begin(); i != this->end(); i++) {
      if (pos.m_ptr == i.m_ptr) found = true;
    }
    if (!found) throw std::out_of_range(RANGE);
    node_base* tmp = new node_base;
    tmp->prev = pos.m_ptr->prev;
    tmp->next = pos.m_ptr->prev->next;
    pos.m_ptr->prev->next = tmp;
    tmp->next->prev = tmp;
    tmp->data = value;
    --iter;
  }
  return iter;
}

template <typename T>
void list<T>::erase(iterator pos) noexcept {
  if (pos == this->begin())
    this->pop_front();
  else if (pos.m_ptr == tail)
    this->pop_back();
  else {
    pos.m_ptr->prev->next = pos.m_ptr->next;
    pos.m_ptr->next->prev = pos.m_ptr->prev;
    delete pos.m_ptr;
  }
}

template <typename T>
void list<T>::push_back(const_reference value) noexcept {
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
}

template <typename T>
void list<T>::pop_back() noexcept {
  if (tail->prev) {
    node_base* tmp = tail->prev;
    delete tail;
    tail = tmp;
    tail->next = NULL;
  } else if (tail) {
    delete tail;
    tail = NULL;
    head = NULL;
  }
}

template <typename T>
void list<T>::push_front(const_reference value) noexcept {
  node_base* tmp = new node_base;
  tmp->data = value;
  tmp->prev = NULL;
  tmp->next = NULL;
  if (!head) {
    head = tmp;
    tail = tmp;
  } else {
    head->prev = tmp;
    tmp->next = head;
    head = tmp;
  }
}

template <typename T>
void list<T>::pop_front() noexcept {
  if (head->next) {
    node_base* tmp = head->next;
    delete head;
    head = tmp;
    head->prev = NULL;
  } else if (head) {
    delete head;
    head = NULL;
    tail = NULL;
  }
}

template <typename T>
void list<T>::swap(list& other) noexcept {
  std::swap(head, other.head);
  std::swap(tail, other.tail);
}

template <typename T>
void list<T>::merge(list& other) noexcept {
  if (&other == this) return;
  list<value_type> merged;
  merged.head = this->merge_nodes(head, other.head);
  head = merged.head;
  while (merged.head) {
    tail = merged.head;
    merged.head = merged.head->next;
  }
  merged.head = NULL;
  merged.tail = NULL;
  other.head = NULL;
  other.tail = NULL;
}

template <typename T>
typename list<T>::node_base* list<T>::merge_nodes(node_base* a,
                                                  node_base* b) noexcept {
  if (!a) return b;
  if (!b) return a;
  if (a->data < b->data) {
    a->next = this->merge_nodes(a->next, b);
    a->next->prev = a;
    a->prev = NULL;
    return a;
  } else {
    b->next = this->merge_nodes(a, b->next);
    b->next->prev = b;
    b->prev = NULL;
    return b;
  }
}

template <typename T>
void list<T>::splice(const_iterator pos, list& other) {
  auto curr = pos._const_cast();
  if (curr != this->begin() && curr != this->end()) {
    bool found = false;
    for (auto i = this->begin(); i != this->end(); i++) {
      if (pos.m_ptr == i.m_ptr) found = true;
    }
    if (!found) throw std::out_of_range(RANGE);
    curr.m_ptr->prev->next = other.head;
    other.head->prev = curr.m_ptr->prev;
    curr.m_ptr->prev = other.tail;
  } else if (curr == this->begin()) {
    head->prev = other.tail;
    head = other.head;
  } else {
    other.head->prev = tail;
    tail->next = other.head;
    tail = other.tail;
  }
  other.tail->next = curr.m_ptr;
  other.head = NULL;
  other.tail = NULL;
}

template <typename T>
void list<T>::reverse() noexcept {
  iterator iter;
  iter.m_ptr = tail;
  for (auto i = this->begin(), j = iter, size = 0; size * 2 < (int)this->size();
       i++, j--, size++) {
    this->swap_elems(i, j);
    std::swap(i.m_ptr, j.m_ptr);
  }
}

template <typename T>
void list<T>::unique() noexcept {
  for (auto i = this->begin(); i.m_ptr; i++) {
    value_type tmp = *i;
    while (i.m_ptr && i.m_ptr->next) {
      if (tmp == i.m_ptr->next->data && i.m_ptr != tail) {
        ListIterator temp = i;
        this->erase(++i);
        i = temp;
      } else
        break;
    }
  }
}

template <typename T>
void list<T>::sort() noexcept {
  for (auto i = this->begin(); i != this->end(); i++) {
    for (auto j = this->begin(); j != this->end(); j++) {
      if (!j.m_ptr || !j.m_ptr->next) continue;
      if (*j > j.m_ptr->next->data) {
        iterator tmp = j;
        this->swap_elems(j, ++tmp);
      }
    }
  }
}

template <typename T>
void list<T>::swap_elems(iterator a, iterator b) noexcept {
  if (a.m_ptr == NULL || b.m_ptr == NULL || a.m_ptr == b.m_ptr) return;
  if (a.m_ptr == head)
    head = b.m_ptr;
  else if (b.m_ptr == head)
    head = a.m_ptr;
  if (a.m_ptr == tail)
    tail = b.m_ptr;
  else if (b.m_ptr == tail)
    tail = a.m_ptr;

  std::swap(a.m_ptr->next, b.m_ptr->next);
  if (a.m_ptr->next) a.m_ptr->next->prev = a.m_ptr;
  if (b.m_ptr->next) b.m_ptr->next->prev = b.m_ptr;

  std::swap(a.m_ptr->prev, b.m_ptr->prev);
  if (a.m_ptr->prev) a.m_ptr->prev->next = a.m_ptr;
  if (b.m_ptr->prev) b.m_ptr->prev->next = b.m_ptr;
}

template <typename T>
template <typename... Args>
typename list<T>::ListIterator list<T>::insert_many(const_iterator pos,
                                                    Args&&... args) {
  if (pos == this->end()) {
    insert_many_back(args...);
    pos.m_ptr = tail;
  } else {
    list<T> tmp;
    tmp.push_front(0U);
    for (auto i : {args...}) {
      if (!std::is_same<decltype(i), node_base*>::value)
        throw std::out_of_range(TYPE_L);
      tmp.head->prev = i;
      i->next = tmp.head;
      i->prev = NULL;
      tmp.head = i;
    }
    tmp.pop_back();
    tmp.reverse();
    int count = (int)tmp.size();
    this->splice(pos, tmp);
    for (int i = 0; i < count; i++) --pos;
  }
  return pos._const_cast();
}

template <typename T>
template <typename... Args>
void list<T>::insert_many_back(Args&&... args) {
  for (auto i : {args...}) {
    if (!std::is_same<decltype(i), node_base*>::value)
      throw std::out_of_range(TYPE_L);
    tail->next = i;
    i->prev = tail;
    i->next = NULL;
    tail = i;
  }
}

template <typename T>
template <typename... Args>
void list<T>::insert_many_front(Args&&... args) {
  list<T> tmp;
  tmp.push_front(0U);
  for (auto i : {args...}) {
    if (!std::is_same<decltype(i), node_base*>::value)
      throw std::out_of_range(TYPE_L);
    tmp.head->prev = i;
    i->next = tmp.head;
    i->prev = NULL;
    tmp.head = i;
  }
  tmp.pop_back();
  tmp.reverse();
  this->splice(this->begin(), tmp);
}