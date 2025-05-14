#include <gtest/gtest.h>

#include <queue>

#include "../containers/s21_queue.h"

template <typename value_type>
bool CompareQueues(s21::queue<value_type> myQueue,
                   std::queue<value_type> stdQueue) {
  bool result = true;
  if (myQueue.size() == stdQueue.size()) {
    while (!myQueue.empty() && !stdQueue.empty()) {
      if (myQueue.front() != stdQueue.front()) {
        result = false;
        break;
      }
      myQueue.pop();
      stdQueue.pop();
    }
  } else {
    result = false;
  }
  return result;
}

TEST(QueueTest, CompareQueues) {
  s21::queue<int> myQueue{3, -5, 7, -9};
  std::queue<int> stdQueue;
  stdQueue.push(3);
  stdQueue.push(-5);
  stdQueue.push(7);
  stdQueue.push(-9);
  EXPECT_TRUE(CompareQueues(myQueue, stdQueue));
  stdQueue.push(20);
  EXPECT_FALSE(CompareQueues(myQueue, stdQueue));
}

TEST(QueueTest, CompareQueues2) {
  s21::queue<int> myQueue{3, -5, 17, -9};
  std::queue<int> stdQueue;
  stdQueue.push(3);
  stdQueue.push(-5);
  stdQueue.push(100);
  stdQueue.push(-9);
  EXPECT_FALSE(CompareQueues(myQueue, stdQueue));
}
TEST(QueueTest, Front) {
  s21::queue<int> myQueue{99, 1, 2};
  std::initializer_list<int> std = {99, 2, 3};
  std::queue<int> stdQueue{std};
  EXPECT_EQ(myQueue.front(), stdQueue.front());
}

TEST(QueueTest, Back) {
  s21::queue<int> myQueue{-100, 58, 99};
  std::initializer_list<int> std = {1, 3, 5, 4, 7, 99};
  std::queue<int> stdQueue{std};
  EXPECT_EQ(myQueue.back(), stdQueue.back());
}

TEST(QueueTest, Empty) {
  s21::queue<int> myQueue;
  std::queue<int> stdQueue;
  EXPECT_EQ(myQueue.empty(), stdQueue.empty());
  myQueue.push(555);
  stdQueue.push(2354);
  EXPECT_EQ(myQueue.empty(), stdQueue.empty());
}

TEST(QueueTest, Size) {
  s21::queue<int> myQueue{1, 2, 3, 4, 5, 6, 7, 8};
  std::initializer_list<int> il = {1, 2, 3, 4, 5, 6, 7, 8};
  std::queue<int> stdQueue{il};
  EXPECT_EQ(myQueue.size(), stdQueue.size());
}

TEST(QueueTest, Push) {
  s21::queue<int> myQueue;
  std::queue<int> stdQueue;
  myQueue.push(555);
  stdQueue.push(555);
  myQueue.push(-100);
  stdQueue.push(-100);
  EXPECT_TRUE(CompareQueues(myQueue, stdQueue));
}

TEST(QueueTest, Pop) {
  s21::queue<int> myQueue{1, 2, 3, 4, 5, 6, 7, 8};
  std::initializer_list<int> std = {1, 2, 3, 4, 5, 6, 7, 8};
  std::queue<int> stdQueue{std};
  myQueue.pop();
  myQueue.pop();
  stdQueue.pop();
  stdQueue.pop();
  EXPECT_TRUE(CompareQueues(myQueue, stdQueue));
  EXPECT_EQ(myQueue.front(), 3);
}

TEST(QueueTest, Swap) {
  s21::queue<int> myQueue1{1, 2, 3, 4, 5};
  s21::queue<int> myQueue2{6, 7, 8, 9, 10, 11};
  myQueue1.swap(myQueue2);

  std::initializer_list<int> std1 = {1, 2, 3, 4, 5};
  std::initializer_list<int> std2 = {6, 7, 8, 9, 10, 11};
  std::queue<int> stdQueue1{std1};
  std::queue<int> stdQueue2{std2};
  stdQueue1.swap(stdQueue2);

  EXPECT_TRUE(CompareQueues(myQueue1, stdQueue1));
  EXPECT_TRUE(CompareQueues(myQueue2, stdQueue2));
}
