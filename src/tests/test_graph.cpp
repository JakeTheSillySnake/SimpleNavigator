#include <gtest/gtest.h>

#include "../graph/s21_graph.h"

TEST(test_Graph, upload_1) {
  Graph graph;
  int res = graph.LoadGraphFromFile("bad_path.txt");
  ASSERT_TRUE(res == NO_FILE);
}

TEST(test_Graph, upload_2) {
  Graph graph;
  int res = graph.LoadGraphFromFile("assets/bad1.txt");
  ASSERT_TRUE(res == BAD_SIZE);
}

TEST(test_Graph, upload_3) {
  Graph graph;
  int res = graph.LoadGraphFromFile("assets/bad4.txt");
  ASSERT_TRUE(res == BAD_FORMAT);
}

TEST(test_Graph, upload_4) {
  Graph graph;
  int res = graph.LoadGraphFromFile("assets/empty.txt");
  ASSERT_TRUE(res == BAD_FORMAT);
}

TEST(test_Graph, upload_5) {
  Graph graph;
  int res = graph.LoadGraphFromFile("assets/bad2.txt");
  ASSERT_TRUE(res == BAD_FORMAT);
}

TEST(test_Graph, upload_6) {
  Graph graph;
  int res = graph.LoadGraphFromFile("assets/bad3.txt");
  ASSERT_TRUE(res == BAD_DATA);
}

TEST(test_Graph, upload_7) {
  Graph graph;
  int res = graph.LoadGraphFromFile("assets/disconnected.txt");
  ASSERT_TRUE(res == DISCONNECTED);
}

TEST(test_Graph, upload_8) {
  Graph graph;
  int res = graph.LoadGraphFromFile("assets/graph_uu.txt");
  graph.Print();
  ASSERT_TRUE(res == 0);
  ASSERT_TRUE(graph.IsUndirected());
}

TEST(test_Graph, export) {
  Graph graph;
  int res = graph.LoadGraphFromFile("assets/graph_uw.txt");
  res = graph.LoadGraphFromFile("assets/graph_big.txt");
  ASSERT_TRUE(res == 0);
  graph.ExportGraphToDot("test.dot");
  FILE *fptr = fopen("test.dot", "r");
  ASSERT_TRUE(fptr != NULL);
  fclose(fptr);
}