#include "s21_graph_algorithms.h"

vector<int> GraphAlgorithms::DepthFirstSearch(Graph &graph, int start_vertex) {
  s21::stack<int> stack;
  vector<bool> visited(graph.size, false);
  vector<int> res;
  stack.push(start_vertex);
  while (!stack.empty()) {
    int n = stack.top();
    stack.pop();
    if (!visited[n]) {
      res.push_back(n);
      visited[n] = true;
      for (int i = graph.size - 1; i >= 0; i--) {
        if (graph.matrix[n][i] && !visited[i]) stack.push(i);
      }
    }
  }
  return res;
}

vector<int> GraphAlgorithms::BreadthFirstSearch(Graph &graph,
                                                int start_vertex) {
  s21::queue<int> queue;
  vector<bool> visited(graph.size, false);
  vector<int> res;
  queue.push(start_vertex);
  while (!queue.empty()) {
    int n = queue.front();
    queue.pop();
    if (!visited[n]) {
      res.push_back(n);
      visited[n] = true;
      for (int i = 0; i < graph.size; i++) {
        if (graph.matrix[n][i] && !visited[i]) queue.push(i);
      }
    }
  }
  return res;
}

/*<----Dijkstra's algorithm---->*/

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

/*<----FLoyd-Warshall algorithm---->*/

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

/*<----Prim's alogrithm---->*/

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
  bool undir = graph.IsUndirected();
  for (int i = 1; i < graph.size; i++) {
    res[parentNodes[i]][i] = graph.matrix[parentNodes[i]][i];
    if (undir) res[i][parentNodes[i]] = graph.matrix[i][parentNodes[i]];
  }
  return res;
}

/*<----Ant colony method---->*/

GraphAlgorithms::TsmResult GraphAlgorithms::SolveTravelingSalesmanProblem(
    Graph &graph) {
  Q *= graph.size;
  vector<vector<double>> pheromones(graph.size,
                                    vector<double>(graph.size, initPheromone));
  vector<vector<double>> deltaPheromones(graph.size,
                                         vector<double>(graph.size, 0));
  vector<int> bestPath(graph.size, 0);
  int minLen = INT_MAX;

  for (int i = 0; i < cycles; i++) {
    for (int ant = 0; ant < graph.size; ant++) {
      vector<bool> visited(graph.size, false);
      int curr = ant;
      visited[curr] = true;
      vector<int> path;
      path.push_back(curr);

      while ((int)path.size() < graph.size) {
        vector<double> probabilities =
            GetNeigbourProbabilities(graph, pheromones, curr, visited);
        int next = GetNextVertex(probabilities);
        visited[next] = true;
        path.push_back(next);
        curr = next;
      }
      path.push_back(path[0]);
      int len = GetPathLength(graph, path);
      if (len < minLen) {
        minLen = len;
        bestPath = path;
      }
      deltaPheromones = UpdateDeltaPheromones(deltaPheromones, path, len);
    }
    pheromones = AddNewTrails(EvaporatePheromones(pheromones), deltaPheromones);
  }

  TsmResult res;
  res.distance = (minLen != INT_MAX && minLen ? minLen : -1);
  if (res.distance != -1) res.vertices = ShiftPath(bestPath);
  return res;
}

vector<double> GraphAlgorithms::GetNeigbourProbabilities(
    Graph &graph, vector<vector<double>> pheromones, int curr,
    vector<bool> visited) {
  vector<double> probabilities(graph.size, 0);
  double sum = 0;
  for (int i = 0; i < graph.size; i++) {
    if (!visited[i]) {
      probabilities[i] = pow(pheromones[curr][i], alpha) *
                         pow(1.0 / graph.matrix[curr][i], beta);
      sum += probabilities[i];
    }
  }
  if (sum)
    for (int i = 0; i < graph.size; i++) probabilities[i] /= sum;
  return probabilities;
}

vector<vector<double>> GraphAlgorithms::AddNewTrails(
    vector<vector<double>> pheromones, vector<vector<double>> deltaPheromones) {
  int n = pheromones.size();
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      pheromones[i][j] += deltaPheromones[i][j] * evaporation;
  return pheromones;
}

vector<vector<double>> GraphAlgorithms::EvaporatePheromones(
    vector<vector<double>> pheromones) {
  int n = pheromones.size();
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++) pheromones[i][j] *= (1 - evaporation);
  return pheromones;
}

vector<vector<double>> GraphAlgorithms::UpdateDeltaPheromones(
    vector<vector<double>> deltaPheromones, vector<int> path, int len) {
  int n = path.size();
  for (int i = 0; i < n - 1; i++) {
    int from = path[i], to = path[i + 1];
    deltaPheromones[from][to] += Q / len;
  }
  return deltaPheromones;
}

int GraphAlgorithms::GetNextVertex(vector<double> probabilites) {
  double sum = 0;
  int n = probabilites.size();
  double begin[n], end[n];
  for (int i = 0; i < n; i++) sum += evaporation;

  double curr = 0;
  for (int i = 0; i < n; i++) {
    begin[i] = curr;
    end[i] = curr + probabilites[i] / sum;
    curr = end[i];
  }

  uniform_real_distribution<double> unif(0.0, 1.0);
  default_random_engine re;
  double choice = unif(re);

  for (int i = 0; i < n; i++)
    if (begin[i] <= choice && end[i] >= choice) return i;
  return n - 1;
}

int GraphAlgorithms::GetPathLength(Graph &graph, vector<int> path) {
  int len = 0;
  int n = path.size();
  for (int i = 0; i < n - 1; i++) {
    int from = path[i], to = path[i + 1];
    len += graph.matrix[from][to];
  }
  len += graph.matrix[path[n - 1]][path[0]];
  return len;
}

vector<int> GraphAlgorithms::ShiftPath(vector<int> path) {
  int curr = path[0], idx = 0, n = path.size();
  vector<int> res;
  while (curr != 0) curr = path[++idx];
  for (int i = idx; i > 0; i--) res.push_back(path[i]);
  for (int i = n - 1; i >= idx; i--) res.push_back(path[i]);
  return res;
}

/*<----Brute force method---->*/

GraphAlgorithms::TsmResult GraphAlgorithms::BruteForceAlgorithm(Graph &graph) {
  vector<bool> visited(graph.size, false);
  vector<int> path;
  visited[0] = true;
  path.push_back(0);
  TsmResult result;
  result.distance = INT_MAX;
  BruteForce(graph, 0, 0, path, visited, result);
  result.vertices.push_back(result.vertices[0]);
  result.distance =
      (result.distance != INT_MAX && result.distance ? result.distance : -1);
  return result;
}

void GraphAlgorithms::BruteForce(Graph &graph, int current, double cost,
                                 vector<int> &path, vector<bool> &visited,
                                 TsmResult &result) {
  if ((int)path.size() == graph.size) {
    cost += graph.matrix[current][0];
    if (cost < result.distance) {
      result.distance = cost;
      result.vertices = path;
    }
    return;
  }
  for (int i = 0; i < graph.size; ++i) {
    if (!visited[i] && graph.matrix[current][i] > 0) {
      visited[i] = true;
      path.push_back(i);
      BruteForce(graph, i, cost + graph.matrix[current][i], path, visited,
                 result);
      visited[i] = false;
      path.pop_back();
    }
  }
}

/*<----Branch and bound method---->*/

GraphAlgorithms::TsmResult GraphAlgorithms::BranchAndBoundAlgorithm(
    Graph &graph) {
  vector<bool> visited(graph.size, false);
  TsmResult result;
  result.distance = INT_MAX;
  result.vertices.resize(graph.size + 1);
  std::vector<int> curr_path;
  curr_path.assign(graph.size, -1);
  int curr_bound = 0;
  for (int i = 0; i < graph.size; ++i)
    curr_bound += (FirstMin(graph, i, visited) + SecondMin(graph, i, visited));
  curr_bound = (curr_bound & 1) ? curr_bound / 2 + 1 : curr_bound / 2;
  visited[0] = true;
  curr_path[0] = 0;
  Rec(graph, curr_bound, 0, 1, curr_path, visited, result);
  result.distance =
      (result.distance != INT_MAX && result.distance ? result.distance : -1);
  return result;
}

void GraphAlgorithms::CopyToFinalPath(Graph &graph, vector<int> &curr_path,
                                      TsmResult &result) {
  for (int i = 0; i < graph.size; ++i) result.vertices[i] = curr_path[i];
  result.vertices[graph.size] = curr_path[0];
}

int GraphAlgorithms::FirstMin(Graph &graph, int i, vector<bool> &visited) {
  int min = INT_MAX;
  for (int k = 0; k < graph.size; ++k) {
    if (visited[k] || i == k) continue;
    if (graph.matrix[i][k] < min) min = graph.matrix[i][k];
  }
  return min;
}

int GraphAlgorithms::SecondMin(Graph &graph, int i, vector<bool> &visited) {
  int first = INT_MAX;
  int second = INT_MAX;
  for (int k = 0; k < graph.size; ++k) {
    if (visited[k] || i == k) continue;
    if (graph.matrix[i][k] <= first) {
      second = first;
      first = graph.matrix[i][k];
    } else if (graph.matrix[i][k] <= second && graph.matrix[i][k] != first) {
      second = graph.matrix[i][k];
    }
  }
  return second;
}

void GraphAlgorithms::Rec(Graph &graph, int curr_bound, int curr_weight,
                          int level, vector<int> &curr_path,
                          vector<bool> &visited, TsmResult &result) {
  if (level == graph.size) {
    if (graph.matrix[curr_path[level - 1]][curr_path[0]] != 0) {
      int curr_res =
          curr_weight + graph.matrix[curr_path[level - 1]][curr_path[0]];
      if (curr_res < result.distance) {
        CopyToFinalPath(graph, curr_path, result);
        result.distance = curr_res;
      }
    }
    return;
  }
  for (int i = 0; i < graph.size; ++i) {
    if (graph.matrix[curr_path[level - 1]][i] != 0 && visited[i] == false) {
      int temp = curr_bound;
      curr_weight += graph.matrix[curr_path[level - 1]][i];
      if (level == 1)
        curr_bound -= ((FirstMin(graph, curr_path[level - 1], visited) +
                        FirstMin(graph, i, visited)) /
                       2);
      else
        curr_bound -= ((SecondMin(graph, curr_path[level - 1], visited) +
                        FirstMin(graph, i, visited)) /
                       2);
      if (curr_bound + curr_weight < result.distance) {
        curr_path[level] = i;
        visited[i] = true;
        Rec(graph, curr_bound, curr_weight, level + 1, curr_path, visited,
            result);
      }
      curr_weight -= graph.matrix[curr_path[level - 1]][i];
      curr_bound = temp;
      visited.assign(visited.size(), false);
      for (int j = 0; j <= level - 1; ++j) visited[curr_path[j]] = true;
    }
  }
}