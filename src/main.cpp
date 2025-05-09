#include <chrono>

#include "s21_graph_algorithms.h"

using namespace std;
using namespace chrono;

enum Action {
  IMPORT = 1,
  EXPORT,
  DFS,
  BFS,
  PATH_BETWEEN,
  PATH,
  MST,
  TSP,
  EXIT
};

void beginLoop(Graph &graph);
void exportGraph(Graph &graph);
void importGraph(Graph &graph);
void dfs(Graph &graph);
void bfs(Graph &graph);
void pathBetweenPoints(Graph &graph);
void shortestPath(Graph &graph);
void mst(Graph &graph);
void tsp(Graph &graph);
void cont();

int main() {
  cout << "\033[2J\033[1;1H";
  cout << "Welcome!" << endl;
  string in;
  Graph graph;
  importGraph(graph);
  beginLoop(graph);
  cout << "\033[2J\033[1;1H";
  return 0;
}

void beginLoop(Graph &graph) {
  int res = -1;
  while (1) {
    cout << "\033[2J\033[1;1H";
    cout << "Choose action:" << endl << endl;
    cout << "1. Import new graph" << endl;
    cout << "2. Export graph" << endl;
    cout << "3. Depth First Search" << endl;
    cout << "4. Breadth First Search" << endl;
    cout << "5. Shortest path between two vertices" << endl;
    cout << "6. Shortest path between all vertices" << endl;
    cout << "7. Get least spanning tree" << endl;
    cout << "8. Solve traveling salesman problem (ant colony method)" << endl;
    cout << "9. Exit" << endl;
    cin >> res;
    if (res == IMPORT)
      importGraph(graph);
    else if (res == EXPORT)
      exportGraph(graph);
    else if (res == DFS)
      dfs(graph);
    else if (res == BFS)
      bfs(graph);
    else if (res == PATH_BETWEEN)
      pathBetweenPoints(graph);
    else if (res == PATH)
      shortestPath(graph);
    else if (res == MST)
      mst(graph);
    else if (res == TSP)
      tsp(graph);
    else if (res == EXIT)
      break;
  }
}

void importGraph(Graph &graph) {
  int res = -1;
  string in;
  do {
    cout << "Please enter graph file:" << endl;
    cin >> in;
    res = graph.LoadGraphFromFile(in);
    if (res == NO_FILE)
      cout << "Error: couldn't open file." << endl;
    else if (res == BAD_SIZE)
      cout << "Error: graph must have at least 2 nodes." << endl;
    else if (res == BAD_FORMAT)
      cout << "Error: bad format. File empty or has non-integers." << endl;
    else if (res == BAD_DATA)
      cout << "Error: data out of range. Edges must be >= 0." << endl;
    else if (res == DISCONNECTED)
      cout << "Error: graph is null or disconnected." << endl;
  } while (res != 0);
  graph.Print();
  cout << "Graph successfully uploaded." << endl;
  cont();
}

void exportGraph(Graph &graph) {
  int res = -1;
  string in;
  do {
    cout << "Please enter name of .dot file to export:" << endl;
    cin >> in;
    res = graph.ExportGraphToDot(in);
    if (res == NO_FILE) cout << "Couldn't open file." << endl;
  } while (res != 0);
  cont();
}

void dfs(Graph &graph) {
  GraphAlgorithms alg;
  int min = 1, max = graph.size, res = -1;
  do {
    cout << "Please enter node " << min << "-" << max << ":" << endl;
    cin >> res;
  } while (res < min || res > max);
  vector<int> path = alg.DepthFirstSearch(graph, res - 1);
  for (int i = 0; i < (int)path.size(); i++) cout << path[i] + 1 << " ";
  cout << endl;
  cont();
}

void bfs(Graph &graph) {
  GraphAlgorithms alg;
  int min = 1, max = graph.size, res = -1;
  do {
    cout << "Please enter node " << min << "-" << max << ":" << endl;
    cin >> res;
  } while (res < min || res > max);
  vector<int> path = alg.BreadthFirstSearch(graph, res - 1);
  for (int i = 0; i < (int)path.size(); i++) cout << path[i] + 1 << " ";
  cout << endl;
  cont();
}

void pathBetweenPoints(Graph &graph) {
  GraphAlgorithms alg;
  int a, b;
  int min = 1, max = graph.size;
  do {
    cout << "Please enter two nodes " << min << "-" << max << ":" << endl;
    cin >> a >> b;
  } while (a < min || a > max || b < min || b > max);
  cout << alg.GetShortestPathBetweenVertices(graph, a - 1, b - 1) << endl;
  cont();
}

void shortestPath(Graph &graph) {
  GraphAlgorithms alg;
  vector<vector<int>> res = alg.GetShortestPathBetweenAllVertices(graph);
  for (int i = 0; i < graph.size; i++) {
    for (int j = 0; j < graph.size; j++) {
      cout << res[i][j] << " ";
    }
    cout << endl;
  }
  cout << endl;
  cont();
}

void mst(Graph &graph) {
  GraphAlgorithms alg;
  vector<vector<int>> res = alg.GetLeastSpanninhTree(graph);
  for (int i = 0; i < graph.size; i++) {
    for (int j = 0; j < graph.size; j++) {
      cout << res[i][j] << " ";
    }
    cout << endl;
  }
  cout << endl;
  cont();
}

void tsp(Graph &graph) {
  GraphAlgorithms alg;
  auto res = alg.SolveTravelingSalesmanProblem(graph);
  if (res.distance == -1)
    cout << "No solution found." << endl;
  else {
    cout << "Traversing sequence: ";
    for (auto i : res.vertices) {
      cout << i + 1 << " ";
    }
    cout << endl << "Route length: " << res.distance << endl;
  }
  cont();
}

void cont() {
  char res = 0;
  do {
    cout << "Press 1 to return: ";
    cin >> res;
  } while (res != '1');
}