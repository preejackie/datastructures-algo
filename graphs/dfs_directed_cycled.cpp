#include "utils.hpp"
using namespace std;

/*
   Detect an existence of a cycle in the graph, don't count.
   in DAG visited[i] and dfsPath[i] is not equal to true at the same-time.
   if a graph has cycle, then visited[i] & dfsPath[i] is equal to true at
   same point in time.
   dfsPath helps us to eliminate non-cycles found by backedge detection
   algorithm for undirected graph.
*/
bool checkCycle(const vector<vector<int>> &graph, vector<bool> &visited,
                vector<bool> &dfsPath, int root) {
  visited[root] = true;
  dfsPath[root] = true;
  bool ok = false;
  for (const auto &next : graph[root]) {
    if (dfsPath[next])
      return true;
    if (visited[next])
      continue;
    ok |= checkCycle(graph, visited, dfsPath, next);
  }
  dfsPath[root] = false;
  return ok;
}

bool detectCycle(const vector<vector<int>> &graph) {
  int n = graph.size();
  bool ok = false;
  vector<bool> visited(n, false), dfsPath(n, false);
  for (int i = 0; i < n; i++) {
    if (visited[i])
      continue;
    ok |= checkCycle(graph, visited, dfsPath, i);
    if (ok)
      return ok;
  }
  return ok;
}

int main() {
  int n, m, a, b, d;
  std::cout << "\n Number of Nodes : ";
  std::cin >> n;
  std::cout << "\n Number of Edges : ";
  std::cin >> m;
  std::cout << "\n Directed 1 or 0 otherwise : ";
  std::cin >> d;
  if (n == 0)
    return 0;

  std::vector<std::vector<int>> graph(n, std::vector<int>{});
  for (int i = 0; i < m; i++) {
    std::cin >> a >> b;
    graph[a].push_back(b);
    if (d == 0)
      graph[b].push_back(a);
  }

  bool isCycle = detectCycle(graph);
  if (isCycle)
    std::cout << "Cycle Found";
  else
    std::cout << "Not found";
  return 0;
}