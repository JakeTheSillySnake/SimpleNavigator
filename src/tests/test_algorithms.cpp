#include <gtest/gtest.h>

#include "../graph/s21_graph_algorithms.h"

TEST(test_GraphAlgorithms, dfs) {
  Graph graph;
  GraphAlgorithms algo;
  graph.LoadGraphFromFile("assets/graph_dw.txt");
  auto res = algo.DepthFirstSearch(graph, 0);
  vector<int> compare = {0, 1, 2, 3, 4};
  ASSERT_TRUE(res == compare);

  graph.LoadGraphFromFile("assets/graph_uw2.txt");
  res = algo.DepthFirstSearch(graph, 2);
  compare = {2, 1, 0, 3, 4};
  ASSERT_TRUE(res == compare);
}

TEST(test_GraphAlgorithms, bfs) {
  Graph graph;
  GraphAlgorithms algo;
  graph.LoadGraphFromFile("assets/graph_dw.txt");
  auto res = algo.BreadthFirstSearch(graph, 0);
  vector<int> compare = {0, 1, 3, 2, 4};
  ASSERT_TRUE(res == compare);

  graph.LoadGraphFromFile("assets/graph_uw2.txt");
  res = algo.BreadthFirstSearch(graph, 2);
  compare = {2, 1, 3, 0, 4};
  ASSERT_TRUE(res == compare);
}

TEST(test_GraphAlgorithms, path_between_two) {
  Graph graph;
  GraphAlgorithms algo;
  graph.LoadGraphFromFile("assets/graph_uw.txt");
  int res = algo.GetShortestPathBetweenVertices(graph, 0, 8);
  ASSERT_TRUE(res == 4);

  graph.LoadGraphFromFile("assets/graph_uw2.txt");
  res = algo.GetShortestPathBetweenVertices(graph, 0, 4);
  ASSERT_TRUE(res == 21);
  res = algo.GetShortestPathBetweenVertices(graph, 2, 4);
  ASSERT_TRUE(res == 9);
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

  graph.LoadGraphFromFile("assets/graph_uw2.txt");
  res = algo.GetShortestPathBetweenAllVertices(graph);
  compare = {{0, 5, 12, 15, 21},
             {5, 0, 7, 10, 16},
             {12, 7, 0, 3, 9},
             {15, 10, 3, 0, 6},
             {21, 16, 9, 6, 0}};
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

TEST(test_GraphAlgorithms, tsp_ant) {
  Graph graph;
  GraphAlgorithms algo;
  graph.LoadGraphFromFile("assets/graph_uw.txt");
  auto res = algo.SolveTravelingSalesmanProblem(graph);
  vector<int> compare = {0, 7, 4, 3, 9, 5, 2, 6, 1, 10, 8, 0};
  ASSERT_TRUE(res.vertices == compare);
  ASSERT_TRUE(res.distance == 253);

  graph.LoadGraphFromFile("assets/graph_uw2.txt");
  res = algo.SolveTravelingSalesmanProblem(graph);
  ASSERT_TRUE(res.distance == -1);

  graph.LoadGraphFromFile("assets/graph_dw.txt");
  res = algo.SolveTravelingSalesmanProblem(graph);
  ASSERT_TRUE(res.distance == -1);
}

TEST(test_GraphAlgorithms, tsp_brute) {
  Graph graph;
  GraphAlgorithms algo;
  graph.LoadGraphFromFile("assets/graph_uw.txt");
  auto res = algo.BruteForceAlgorithm(graph);
  vector<int> compare = {0, 7, 4, 3, 9, 5, 2, 6, 1, 10, 8, 0};
  ASSERT_TRUE(res.vertices == compare);
  ASSERT_TRUE(res.distance == 253);

  /*<----small graph for valgrind---->*/
  /*graph.LoadGraphFromFile("assets/graph_du.txt");
  algo.BruteForceAlgorithm(graph);*/
}

TEST(test_GraphAlgorithms, tsp_branch) {
  Graph graph;
  GraphAlgorithms algo;
  graph.LoadGraphFromFile("assets/graph_uw.txt");
  auto res = algo.BranchAndBoundAlgorithm(graph);
  vector<int> compare = {0, 7, 4, 3, 9, 5, 2, 6, 1, 10, 8, 0};
  ASSERT_TRUE(res.vertices == compare);
  ASSERT_TRUE(res.distance == 253);

  graph.LoadGraphFromFile("assets/graph_uw2.txt");
  res = algo.BranchAndBoundAlgorithm(graph);
  ASSERT_TRUE(res.distance == -1);

  /*<----small graph for valgrind---->*/
  /*graph.LoadGraphFromFile("assets/graph_du.txt");
  algo.BranchAndBoundAlgorithm(graph);*/
}