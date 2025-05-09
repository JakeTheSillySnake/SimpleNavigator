#ifndef GRAPH_H
#define GRAPH_H

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

enum Errors { NO_FILE = 1, BAD_SIZE, BAD_FORMAT, BAD_DATA, DISCONNECTED };

class Graph {
 public:
  int **matrix = nullptr;
  int size = 0;

  Graph() { Graph(0); }
  Graph(int n) { Init(n); }
  ~Graph() { Clear(); }
  int LoadGraphFromFile(string filename);
  int ExportGraphToDot(string filename);
  bool EdgeExists(int a, int b);
  bool IsUndirected();
  void Init(int n);
  void Clear();
  void Print();
};

#endif