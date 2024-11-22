#include "utils.hpp"
using namespace std;

int maxCycleLen;

bool checkCycle(const vector<vector<int>>  &graph, vector<bool> &visited, vector<bool> &dfsPath, int root,
            vector<int> &visitNum, int num) {
  visited[root] = true;
  dfsPath[root] = true;
  visitNum[root] = num;
  bool ok = false;
  for (const auto &next : graph[root]) {
    if (dfsPath[next]) { //backedge (root->next) visit number of next < visit number of root.
      maxCycleLen = max(maxCycleLen, visitNum[root] - visitNum[next] + 1);
      return true;
    }
    if (visited[next])
      continue;
    ok |= checkCycle(graph, visited, dfsPath, next, visitNum, num+1);
  }
  dfsPath[root] = false;
  return ok;
}

bool detectCycle(const vector<vector<int>> &graph) {
  int n = graph.size(), num = 0;
  bool ok = false;
  vector<bool> visited(n, false), dfsPath(n, false);
  vector<int>  visitNum(n, 0);

  for (int i=0; i<n; i++) {
    if (visited[i])
      continue;
    ok |= checkCycle(graph, visited, dfsPath, i, visitNum, num);
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
  maxCycleLen = 0;
  bool isCycle = detectCycle(graph);
  std::cout << "\n max cycle length : " << maxCycleLen;
  if (isCycle)
    std::cout << "Cycle Found";
  else
    std::cout << "Not found";
  return 0;
}