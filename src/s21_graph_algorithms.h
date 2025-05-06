#ifndef GRAPH_ALGO_H
#define GRAPH_ALGO_H

#include <limits.h>

#include <vector>

#include "containers/s21_queue.h"
#include "containers/s21_stack.h"
#include "s21_graph.h"

using namespace std;

class GraphAlgorithms {
 public:
  struct TsmResult {
    int *vertices;
    double distance;
    TsmResult() { TsmResult(0, 0); }
    TsmResult(int size, int dist) : distance(dist) { vertices = new int[size]; }
    ~TsmResult() { delete[] vertices; }
  };

  GraphAlgorithms() {}
  ~GraphAlgorithms() {}

  vector<int> DepthFirstSearch(Graph &graph, int start_vertex);
  vector<int> BreadthFirstSearch(Graph &graph, int start_vertex);

  int GetShortestPathBetweenVertices(Graph &graph, int vertex1, int vertex2);
  vector<vector<int>> GetShortestPathBetweenAllVertices(Graph &graph);
  int GetMinDistance(vector<int> dist, vector<bool> visited);

  vector<vector<int>> GetLeastSpanninhTree(Graph &graph);
  TsmResult SolveTravelingSalesmanProblem(Graph &graph);
};

#endif