#include <gtest/gtest.h>

#include "../s21_graph_algorithms.h"

TEST(test_GraphAlgorithms, dfs) {
  Graph graph;
  GraphAlgorithms algo;
  graph.LoadGraphFromFile("assets/graph_uw.txt");
  vector<int> res = algo.DepthFirstSearch(graph, 0);
  ASSERT_TRUE((int)res.size() == graph.size);
}

TEST(test_GraphAlgorithms, bfs) {
  Graph graph;
  GraphAlgorithms algo;
  graph.LoadGraphFromFile("assets/graph_uw.txt");
  vector<int> res = algo.BreadthFirstSearch(graph, 0);
  ASSERT_TRUE((int)res.size() == graph.size);
}

TEST(test_GraphAlgorithms, path_between_two) {
  Graph graph;
  GraphAlgorithms algo;
  graph.LoadGraphFromFile("assets/graph_uw.txt");
  int res = algo.GetShortestPathBetweenVertices(graph, 0, 8);
  ASSERT_TRUE(res == 4);
}

TEST(test_GraphAlgorithms, path_between_all) {
  Graph graph;
  GraphAlgorithms algo;
  graph.LoadGraphFromFile("assets/graph_dw.txt");
  auto res = algo.GetShortestPathBetweenAllVertices(graph);
  vector<vector<int>> compare = {{0, 4, 5, 5, 7},
                                 {3, 0, 1, 4, 6},
                                 {2, 6, 0, 3, 5},
                                 {3, 7, 1, 0, 2},
                                 {1, 5, 5, 4, 0}};
  ASSERT_TRUE(res == compare);
}

TEST(test_GraphAlgorithms, mst) {
  Graph graph;
  GraphAlgorithms algo;
  graph.LoadGraphFromFile("assets/graph_dw.txt");
  auto res = algo.GetLeastSpanninhTree(graph);
  vector<vector<int>> compare = {{0, 4, 0, 0, 0},
                                 {0, 0, 1, 0, 0},
                                 {0, 0, 0, 3, 0},
                                 {0, 0, 0, 0, 2},
                                 {0, 0, 0, 0, 0}};
  ASSERT_TRUE(res == compare);
}

TEST(test_GraphAlgorithms, tsp) {
  Graph graph;
  GraphAlgorithms algo;
  graph.LoadGraphFromFile("assets/graph_uw.txt");
  auto res = algo.SolveTravelingSalesmanProblem(graph);
  vector<int> compare = {0, 7, 4, 3, 9, 5, 2, 6, 1, 10, 8, 0};
  ASSERT_TRUE(res.vertices == compare);
  ASSERT_TRUE(res.distance == 253);
}