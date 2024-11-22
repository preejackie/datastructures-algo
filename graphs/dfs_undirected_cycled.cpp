#include "utils.hpp"
using namespace std;

bool checkForBackEdge(const vector<vector<int>> &graph, vector<bool> &visited, int root, int parent) {
  visited[root] = true;
  bool ok = false;
  for (auto &next : graph[root]) {
    if (next == parent)
      continue;
    if (visited[next]) //in directed graph there could be no path from next to root's predecessor
      return true;
    ok |= checkForBackEdge(graph, visited, next, root);
  }
  return ok;
}

bool detectCycle(const vector<vector<int>> &graph) {
  int n = graph.size();
  vector<bool> visited(n, false);
  bool ok = 0;
  for (int i=0; i<n; i++) {
    if (!visited[i])
      ok = checkForBackEdge(graph, visited, i, -1);
    if (ok) return ok;
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