#ifndef GRAPH_ALGO_H
#define GRAPH_ALGO_H

#include <limits.h>

#include <cmath>
#include <random>
#include <vector>

#include "containers/s21_queue.h"
#include "containers/s21_stack.h"
#include "s21_graph.h"

using namespace std;

class GraphAlgorithms {
 private:
  const double alpha = 1.0;  // regulates whether distance affects ant's choice
  const double beta = 2.0;   // regulates whether pheromons affect ant's choice
  const double initPheromone = 0.1;  // initial pheromone amount
  const double evaporation = 0.2;    // regulates pheromone evaporation
  double Q = 5.0;                    // regulates pheromone addition
  int cycles = 100;                  // learning cycles = 100

 public:
  struct TsmResult {
    vector<int> vertices;
    double distance;
  };

  GraphAlgorithms() {}
  ~GraphAlgorithms() {}

  vector<int> DepthFirstSearch(Graph &graph, int start_vertex);
  vector<int> BreadthFirstSearch(Graph &graph, int start_vertex);

  int GetShortestPathBetweenVertices(Graph &graph, int vertex1, int vertex2);
  vector<vector<int>> GetShortestPathBetweenAllVertices(Graph &graph);

  vector<vector<int>> GetLeastSpanninhTree(Graph &graph);
  TsmResult SolveTravelingSalesmanProblem(Graph &graph);

 private:
  // shortes path helper
  int GetMinDistance(vector<int> dist, vector<bool> visited);

  // tsp ant colony helpers
  vector<double> GetNeigbourProbabilities(Graph &graph,
                                          vector<vector<double>> pheromones,
                                          int curr, vector<bool> visited);
  vector<vector<double>> AddNewTrails(vector<vector<double>> pheromones,
                                      vector<vector<double>> deltaPheromones);
  vector<vector<double>> EvaporatePheromones(vector<vector<double>> pheromones);
  vector<vector<double>> UpdateDeltaPheromones(
      vector<vector<double>> deltaPheromones, vector<int> path, int len);
  int GetNextVertex(vector<double> probabilites);
  int GetPathLength(Graph &graph, vector<int> path);
  vector<int> ShiftPath(vector<int> path);
};

#endif