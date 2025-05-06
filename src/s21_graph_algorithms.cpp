#include "s21_graph_algorithms.h"

vector<int> GraphAlgorithms::DepthFirstSearch(Graph &graph, int start_vertex) {
  Stack<int> stack;
  vector<bool> visited(graph.size, false);
  vector<int> res;
  stack.Push(start_vertex);
  while (!stack.Empty()) {
    int n = stack.Top();
    stack.Pop();
    if (!visited[n]) {
      res.push_back(n + 1);
      visited[n] = true;
      for (int i = 0; i < graph.size; i++) {
        if (graph.matrix[n][i] && !visited[i]) stack.Push(i);
      }
    }
  }
  return res;
}

vector<int> GraphAlgorithms::BreadthFirstSearch(Graph &graph,
                                                int start_vertex) {
  Queue<int> queue;
  vector<bool> visited(graph.size, false);
  vector<int> res;
  queue.Push(start_vertex);
  while (!queue.Empty()) {
    int n = queue.Front();
    queue.Pop();
    if (!visited[n]) {
      res.push_back(n + 1);
      visited[n] = true;
      for (int i = 0; i < graph.size; i++) {
        if (graph.matrix[n][i] && !visited[i]) queue.Push(i);
      }
    }
  }
  return res;
}

int GraphAlgorithms::GetShortestPathBetweenVertices(Graph &graph, int vertex1,
                                                    int vertex2) {
  vector<int> dist(graph.size, INT_MAX);
  vector<bool> visited(graph.size, false);
  dist[vertex1] = 0;
  for (int cnt = 0; cnt < graph.size - 1 && cnt != vertex2; cnt++) {
    int n = GetMinDistance(dist, visited);
    visited[n] = true;
    for (int i = 0; i < graph.size; i++)
      if (!visited[i] && graph.matrix[n][i] &&
          dist[n] + graph.matrix[n][i] < dist[i] && dist[n] != INT_MAX)
        dist[i] = dist[n] + graph.matrix[n][i];
  }
  return dist[vertex2];
}

vector<vector<int>> GraphAlgorithms::GetShortestPathBetweenAllVertices(
    Graph &graph) {
  vector<vector<int>> dist(graph.size, vector<int>(graph.size, 0));
  for (int i = 0; i < graph.size; i++) {
    for (int j = 0; j < graph.size; j++) {
      dist[i][j] = graph.matrix[i][j];
      if (!dist[i][j] && i != j) dist[i][j] = 1e8;
    }
  }
  for (int k = 0; k < graph.size; k++) {
    for (int i = 0; i < graph.size; i++) {
      for (int j = 0; j < graph.size; j++) {
        if (dist[i][k] != 1e8 && dist[k][j] != 1e8)
          dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
      }
    }
  }
  return dist;
}

int GraphAlgorithms::GetMinDistance(vector<int> dist, vector<bool> visited) {
  int min = INT_MAX, idx;
  for (int i = 0; i < (int)dist.size(); i++) {
    if (!visited[i] && dist[i] <= min) min = dist[i], idx = i;
  }
  return idx;
}

vector<vector<int>> GraphAlgorithms::GetLeastSpanninhTree(Graph &graph) {
  vector<bool> visited(graph.size, false);
  vector<int> dist(graph.size, INT_MAX);
  vector<int> parentNodes(graph.size);
  dist[0] = 0;
  parentNodes[0] = -1;
  for (int cnt = 0; cnt < graph.size - 1; cnt++) {
    int n = GetMinDistance(dist, visited);
    visited[n] = true;
    for (int i = 0; i < graph.size; i++) {
      if (graph.matrix[n][i] && !visited[i] && graph.matrix[n][i] < dist[i])
        parentNodes[i] = n, dist[i] = graph.matrix[n][i];
    }
  }
  vector<vector<int>> res(parentNodes.size(), vector<int>(parentNodes.size()));
  for (int i = 1; i < graph.size; i++) {
    res[parentNodes[i]][i] = graph.matrix[parentNodes[i]][i];
    res[i][parentNodes[i]] = graph.matrix[i][parentNodes[i]];
  }
  return res;
}

GraphAlgorithms::TsmResult GraphAlgorithms::SolveTravelingSalesmanProblem(
    Graph &graph) {
  TsmResult res;
  res.vertices = new int[graph.size];
  res.distance = 0;
  // tsm solution
  return res;
}