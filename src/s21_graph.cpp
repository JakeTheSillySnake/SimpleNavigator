#include "s21_graph.h"

using namespace std;

void Graph::Clear() {
  for (int i = 0; i < size; i++) delete[] matrix[i];
  if (matrix != nullptr) delete[] matrix;
  size = 0;
}

void Graph::Init(int n) {
  matrix = new int*[n];
  for (int i = 0; i < n; i++) matrix[i] = new int[n];
  size = n;
}

int Graph::LoadGraphFromFile(string filename) {
  Clear();
  int error = 0;
  ifstream input(filename);
  if (!input.is_open()) return NO_FILE;
  int size;
  input >> size;
  if (input.fail())
    return BAD_FORMAT;
  else if (size < 2)
    return BAD_DATA;
  Init(size);
  for (int i = 0; i < size && !error; i++) {
    bool connected = false;
    for (int j = 0; j < size && !error; j++) {
      input >> matrix[i][j];
      if (input.fail())
        error = BAD_FORMAT;
      else if (matrix[i][j] < 0)
        error = BAD_DATA;
      if (!error && matrix[i][j]) connected = true;
    }
    if (!connected && !error) error = BAD_DATA;
  }
  input.close();
  return error;
}

int Graph::ExportGraphToDot(string filename) {
  ofstream output(filename);
  if (!output.is_open()) return NO_FILE;
  output << "graph newgraph {" << endl;
  string path = "--";
  bool undirected = IsUndirected();
  if (!undirected) path = "->";
  char outerNode = 'a';
  int outerRound = 1;
  for (int i = 0; i < size; i++) {
    char innerNode = 'a';
    int innerRound = 1;
    for (int j = 0; j < size; j++) {
      if (i != j && (!undirected || j > i) && matrix[i][j]) {
        char buff[100];
        snprintf(buff, sizeof(buff), "    %c%d %s %c%d;\n", outerNode,
                 outerRound, path.c_str(), innerNode, innerRound);
        output << buff;
      }
      innerNode++;
      if (innerNode > 'z') {
        innerNode = 'a';
        innerRound++;
      }
    }
    outerNode++;
    if (outerNode > 'z') {
      outerNode = 'a';
      outerRound++;
    }
  }
  output << "}";
  output.close();
  return 0;
}

bool Graph::IsUndirected() {
  for (int i = 0; i < size; i++) {
    if (matrix[i][i] != 0) return false;
    for (int j = 0; j < size; j++) {
      if (matrix[i][j] != matrix[j][i]) return false;
    }
  }
  return true;
}

void Graph::Print() {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      cout << matrix[i][j] << " ";
    }
    cout << endl;
  }
  cout << endl;
}