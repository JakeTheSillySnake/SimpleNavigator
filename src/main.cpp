#include <iostream>

#include "s21_graph.h"
#include "s21_graph_algorithms.h"

using namespace std;

int main() {
  cout << "Welcome!" << endl;
  string in;
  Graph graph;
  int res = -1;
  do {
    cout << "Please enter graph file:" << endl;
    cin >> in;
    res = graph.LoadGraphFromFile(in);
    if (res == NO_FILE)
      cout << "Couldn't open file." << endl;
    else if (res == BAD_FORMAT)
      cout << "Couldn't read from file: bad format." << endl;
    else if (res == BAD_DATA)
      cout << "Couldn't read from file: data out of range." << endl;
  } while (res != 0);

  cout << "Graph successfully uploaded." << endl;
  res = -1;
  do {
    cout << "Please enter name of .dot file to export:" << endl;
    cin >> in;
    res = graph.ExportGraphToDot(in);
    if (res == NO_FILE) cout << "Couldn't open file." << endl;
  } while (res != 0);
  return 0;
}