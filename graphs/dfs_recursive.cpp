#include "utils.hpp"

void preprocess(int) {}
void postprocess(int) {}

void dfs_impl(const std::vector<std::vector<int>> &graph, int root,
              std::vector<bool> &visited, std::vector<int> &order) {
  preprocess(root);
  if (visited[root])
    return;
  visited[root] = true;
  order.push_back(root);
  for (const auto &next : graph[root]) {
    if (!visited[next])
      dfs_impl(graph, next, visited, order);
  }
  postprocess(root);
}

std::vector<std::vector<int>>
dfs_recursive(const std::vector<std::vector<int>> &graph) {
  int n = graph.size();
  std::vector<bool> visited(n, false);
  std::vector<std::vector<int>> component_order;
  for (int i = 0; i < n; i++) {
    if (!visited[i]) {
      std::vector<int> order;
      dfs_impl(graph, i, visited, order);
      component_order.push_back(std::move(order));
    }
  }
  return component_order;
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
    return;

  std::vector<std::vector<int>> graph(n, std::vector<int>{});
  for (int i = 0; i < m; i++) {
    std::cin >> a >> b;
    graph[a].push_back(b);
    if (d == 0)
      graph[b].push_back(a);
  }

  auto result = dfs_recursive(graph);
  std::cout << "\n Number of components in the graph : \n" << result.size();
  for (int i = 0; i < result.size(); i++) {
    for (const auto &v : result[i]) {
      std::cout << v << " ";
    }
    std::cout << "\n";
  }
  return 0;
}