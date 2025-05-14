#include <gtest/gtest.h>

#include "../containers/s21_stack.h"

using namespace s21;

TEST(test_Constr_Stack, constr_1) {
  stack<int> test = {1, 2, 3};
  ASSERT_TRUE(test.size() == 3);
}

TEST(test_Constr_Stack, constr_2) {
  stack<int> test = {1, 2, 3};
  stack<int> test2(test);
  ASSERT_TRUE(!test2.empty());
}

TEST(test_Constr_Stack, constr_3) {
  stack<int> test = {1, 2, 3};
  stack<int> test2 = std::move(test);
  ASSERT_TRUE(test2.top() == 3);
}

TEST(test_Constr_Stack, constr_4) {
  stack<int> test = {1, 2, 3};
  stack<int> test2 = test;
  ASSERT_TRUE(test2.top() == 3);
}

TEST(test_Push_Stack, push_1) {
  stack<int> test = {1, 2, 3};
  test.push(4);
  ASSERT_TRUE(test.size() == 4);
}

TEST(test_Push_Stack, push_2) {
  stack<int> test = {1, 2, 3};
  test.push(4);
  ASSERT_TRUE(test.top() == 4);
}

TEST(test_Pop_Stack, pop_1) {
  stack<int> test = {1, 2, 3};
  test.pop();
  ASSERT_TRUE(test.size() == 2);
}

TEST(test_Pop_Stack, pop_2) {
  stack<int> test = {1, 2, 3};
  test.pop();
  ASSERT_TRUE(test.top() == 2);
}

TEST(test_Swap_Stack, swap_1) {
  stack<int> test = {1, 2, 3};
  stack<int> test2 = {4};
  test.swap(test2);
  ASSERT_TRUE(test.top() == 4);
}

TEST(test_Swap_Stack, swap_2) {
  stack<int> test = {1, 2, 3};
  stack<int> test2 = {4};
  test.swap(test2);
  ASSERT_TRUE(test2.top() == 3);
}

TEST(test_Insert_Stack, insert_1) {
  stack<int> test = {1, 2, 3};
  test.insert_many_front(4, 5, 6);
  ASSERT_TRUE(test.top() == 6);
}

TEST(test_Insert_Stack, insert_2) {
  stack<int> test = {1, 2, 3};
  test.insert_many_front(4, 5, 6);
  ASSERT_TRUE(test.size() == 6);
}