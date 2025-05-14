#include <gtest/gtest.h>

#include "../containers/s21_list.h"

using namespace s21;

TEST(test_Constr_List, constr_1) {
  list<int> li1(3);
  ASSERT_TRUE(li1.size() == 3);
}

TEST(test_Constr_List, constr_2) {
  list<int> li1 = {1, 2, 3};
  ASSERT_TRUE(li1.size() == 3);
}

TEST(test_Constr_List, constr_3) {
  list<int> li1 = {1, 2, 3};
  list<int> li2(li1);
  int res = li2.size();
  ASSERT_TRUE(res == 3);
}

TEST(test_Constr_List, constr_4) {
  list<int> li1 = {1, 2, 3};
  list<int> li2 = std::move(li1);
  ASSERT_TRUE(li2.size() == 3);
}

TEST(test_Constr_List, constr_5) {
  list<int> li1 = {1, 2, 3};
  list<int> li2 = li1;
  ASSERT_TRUE(li2.size() == 3);
}

TEST(test_Size_List, size_1) {
  list<int> li1 = {1, 2, 3};
  ASSERT_TRUE(li1.max_size() != 0);
}

TEST(test_Iter_List, iter_1) {
  list<int> li1 = {1};
  list<int>::ListIterator iter = li1.begin();
  ASSERT_TRUE(*iter == 1);
}

TEST(test_Access_List, access_1) {
  list<int> li1 = {1, 2, 3, 4};
  int res = li1.front() + li1.back();
  ASSERT_TRUE(res == 5);
}

TEST(test_Empty_List, empty_1) {
  list<int> li1;
  ASSERT_TRUE(li1.empty());
}

TEST(test_Empty_List, empty_2) {
  list<int> li1 = {1, 2, 3};
  li1.clear();
  ASSERT_TRUE(li1.empty());
}

TEST(test_Insert_List, insert_1) {
  list<int> li1 = {2};
  li1.insert(li1.begin(), 9);
  ASSERT_TRUE(li1.front() == 9);
}

TEST(test_Insert_List, insert_2) {
  list<int> li1 = {2};
  li1.insert(li1.end(), 9);
  ASSERT_TRUE(li1.back() == 9);
}

TEST(test_Insert_List, insert_3) {
  list<int> li1 = {2, 3};
  list<int>::ListIterator iter = li1.insert(++li1.begin(), 9);
  ASSERT_TRUE(*iter == 9);
}

TEST(test_Insert_List, insert_4) {
  list<int> li1;
  li1.insert(li1.begin(), 9);
  ASSERT_TRUE(li1.back() == 9);
}

TEST(test_Insert_List, insert_5) {
  list<int> li1;
  li1.insert(li1.begin(), 9);
  ASSERT_TRUE(li1.front() == 9);
}

TEST(test_Erase_List, erase_1) {
  list<int> li1 = {1, 2, 3};
  li1.erase(li1.begin());
  ASSERT_TRUE(li1.front() == 2);
}

TEST(test_Erase_List, erase_2) {
  list<int> li1 = {1, 2, 3};
  list<int>::ListIterator iter = li1.begin();
  li1.erase(std::next(iter, 2));
  ASSERT_TRUE(li1.back() == 2);
}

TEST(test_Erase_List, erase_3) {
  list<int> li1 = {1, 2, 3};
  li1.erase(++li1.begin());
  list<int>::ListIterator iter = ++li1.begin();
  ASSERT_TRUE(*iter == 3);
}

TEST(test_Erase_List, erase_4) {
  list<int> li1 = {1};
  li1.erase(li1.begin());
  ASSERT_TRUE(li1.empty());
}

TEST(test_Swap_List, swap_1) {
  list<int> li1 = {1, 2, 3};
  list<int> li2 = {4};
  li1.swap(li2);
  ASSERT_TRUE(li2.front() == 1);
}

TEST(test_Swap_List, swap_2) {
  list<int> li1 = {1, 2, 3};
  list<int>::ListIterator iter = std::next(li1.begin(), 2);
  li1.swap_elems(iter, li1.begin());
  ASSERT_TRUE(li1.front() == 3);
}

TEST(test_Merge_List, merge_1) {
  list<int> li1 = {1, 2, 3};
  list<int> li2 = {1, 2, 3};
  li1.merge(li2);
  ASSERT_TRUE(li1.size() == 6);
}

TEST(test_Merge_List, merge_2) {
  list<int> li1 = {1, 2, 3};
  list<int> li2 = {4};
  li1.merge(li2);
  ASSERT_TRUE(li1.back() == 4);
}

TEST(test_Merge_List, merge_3) {
  list<int> li1 = {1, 2, 3};
  list<int> li2 = {0};
  li1.merge(li2);
  ASSERT_TRUE(li1.front() == 0);
}

TEST(test_Merge_List, merge_4) {
  list<int> li1 = {1, 2, 3};
  list<int> li2 = {0};
  list<int>::ListIterator iter = li2.begin();
  li1.merge(li2);
  ASSERT_TRUE(iter.m_ptr == li1.head);
}

TEST(test_Merge_List, merge_5) {
  list<int> li1 = {1, 2, 3};
  list<int> li2 = {0};
  li1.merge(li2);
  ASSERT_TRUE(li2.empty());
}

TEST(test_Splice_List, splice_1) {
  list<int> li1 = {1, 2, 3};
  list<int> li2 = {4, 5, 6};
  li1.splice(li1.begin(), li2);
  ASSERT_TRUE(li1.front() == 4);
}

TEST(test_Splice_List, splice_2) {
  list<int> li1 = {1, 2, 3};
  list<int> li2 = {4, 5, 6};
  li1.splice(li1.begin(), li2);
  ASSERT_TRUE(li1.size() == 6);
}

TEST(test_Splice_List, splice_3) {
  list<int> li1 = {1, 2, 3};
  list<int> li2 = {4, 5, 6};
  li1.splice(li1.end(), li2);
  ASSERT_TRUE(li1.back() == 6);
}

TEST(test_Splice_List, splice_4) {
  list<int> li1 = {1, 2, 3};
  list<int> li2 = {4, 5, 6};
  li1.splice(++li1.begin(), li2);
  ASSERT_TRUE(*(++li1.begin()) == 4);
}

TEST(test_Splice_List, splice_5) {
  list<int> li1 = {1, 2, 3};
  list<int> li2 = {4, 5, 6};
  li1.splice(++li1.begin(), li2);
  ASSERT_TRUE(li2.empty());
}

TEST(test_Splice_List, splice_6) {
  list<int> li1 = {1, 2, 3};
  list<int> li2 = {4, 5, 6};
  list<int>::ListIterator iter = li2.begin();
  li1.splice(++li1.begin(), li2);
  ASSERT_TRUE(*iter);
}

TEST(test_Reverse_List, reverse_1) {
  list<int> li1 = {1, 2, 3};
  li1.reverse();
  ASSERT_TRUE(li1.front() == 3);
}

TEST(test_Reverse_List, reverse_2) {
  list<int> li1 = {1, 2, 3};
  li1.reverse();
  ASSERT_TRUE(li1.back() == 1);
}

TEST(test_Reverse_List, reverse_3) {
  list<int> li1 = {1, 2, 3};
  list<int>::ListIterator iter = li1.begin();
  li1.reverse();
  ASSERT_TRUE(iter.m_ptr == std::next(li1.begin(), 2).m_ptr);
}

TEST(test_Unique_List, unique_1) {
  list<int> li1 = {1, 1, 1, 2, 3};
  li1.unique();
  ASSERT_TRUE(li1.size() == 3);
}

TEST(test_Unique_List, unique_2) {
  list<int> li1 = {1, 2, 2, 2, 3};
  li1.unique();
  ASSERT_TRUE(li1.size() == 3);
}

TEST(test_Unique_List, unique_3) {
  list<int> li1 = {1, 2, 3, 3, 3};
  li1.unique();
  ASSERT_TRUE(li1.size() == 3);
}

TEST(test_Unique_List, unique_4) {
  list<int> li1 = {1, 2, 1, 2, 3};
  li1.unique();
  ASSERT_TRUE(li1.size() == 5);
}

TEST(test_Sort_List, sort_1) {
  list<int> li1 = {1, 2, 1, 2, 3};
  li1.sort();
  ASSERT_TRUE(*(++li1.begin()) == 1);
}

TEST(test_Insert_ListMany, insert_many_1) {
  list<int> li1 = {1, 2, 3};
  list<int>::node_base *node = new list<int>::node_base;
  list<int>::node_base *node2 = new list<int>::node_base;
  list<int>::node_base *node3 = new list<int>::node_base;
  node->data = 4;
  node2->data = 5;
  node3->data = 6;
  li1.insert_many(li1.begin(), node, node2, node3);
  ASSERT_TRUE(li1.head->data == 4);
}

TEST(test_Insert_ListMany, insert_many_2) {
  list<int> li1 = {1, 2, 3};
  list<int>::node_base *node = new list<int>::node_base;
  list<int>::node_base *node2 = new list<int>::node_base;
  list<int>::node_base *node3 = new list<int>::node_base;
  node->data = 4;
  node2->data = 5;
  node3->data = 6;
  li1.insert_many(li1.end(), node, node2, node3);
  ASSERT_TRUE(li1.tail->data == 6);
}

TEST(test_Insert_ListMany, insert_many_3) {
  list<int> li1 = {1, 2, 3};
  list<int>::node_base *node = new list<int>::node_base;
  list<int>::node_base *node2 = new list<int>::node_base;
  list<int>::node_base *node3 = new list<int>::node_base;
  node->data = 4;
  node2->data = 5;
  node3->data = 6;
  li1.insert_many(++li1.begin(), node, node2, node3);
  ASSERT_TRUE(li1.head->data = 1);
}

TEST(test_Insert_ListMany, insert_many_4) {
  list<int> li1 = {1, 2, 3};
  list<int>::node_base *node = new list<int>::node_base;
  list<int>::node_base *node2 = new list<int>::node_base;
  list<int>::node_base *node3 = new list<int>::node_base;
  node->data = 4;
  node2->data = 5;
  node3->data = 6;
  list<int>::ListIterator iter =
      li1.insert_many(++li1.begin(), node, node2, node3);
  ASSERT_TRUE(*iter == 4);
}

TEST(test_Insert_ListMany, insert_many_5) {
  list<int> li1 = {1, 2, 3};
  list<int>::node_base *node = new list<int>::node_base;
  list<int>::node_base *node2 = new list<int>::node_base;
  list<int>::node_base *node3 = new list<int>::node_base;
  node->data = 4;
  node2->data = 5;
  node3->data = 6;
  li1.insert_many_front(node, node2, node3);
  ASSERT_TRUE(li1.head->data == 4);
}

TEST(test_Insert_ListMany, insert_many_6) {
  list<int> li1 = {1, 2, 3};
  list<int>::node_base *node = new list<int>::node_base;
  list<int>::node_base *node2 = new list<int>::node_base;
  list<int>::node_base *node3 = new list<int>::node_base;
  node->data = 4;
  node2->data = 5;
  node3->data = 6;
  li1.insert_many_back(node, node2, node3);
  ASSERT_TRUE(li1.tail->data == 6);
}