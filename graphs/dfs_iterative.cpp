#include "utils.hpp"

void preprocess(int node) { std::cout << "\n Preprocess: " << node; }
void postprocess(int node) { std::cout << "\n Postprocess: " << node; }

std::vector<int> dfs_impl(const std::vector<std::vector<int>> &graph, int root,
                          std::vector<bool> &in, std::vector<bool> &out) {
  std::stack<std::pair<int, bool>> st;
  st.push({root, 1});
  st.push({root, 0});
  std::vector<int> order;

  while (!st.empty()) {
    auto node = st.top();
    st.pop();

    // skip if it is already visited according to dfs visitation order.
    if (out[node.first])
      continue;

    if (node.second == 1) {
      postprocess(node.first);
      out[node.first] = true;
    }

    if (in[node.first])
      continue;

    preprocess(node.first);
    in[node.first] = true;
    order.push_back(node.first);

    // go through its neighbours and put them in a stack, note this will
    // keep some duplicate nodes in the stack such as nodes those are
    // inserted by parent node, but they can also visited following some
    // other child node of parent.
    /*
        s
       / |
      t  |
       \ |
        v
    in this case order should be s->t->v or s->v->t not s->t->s->v
    */
    for (auto &next : graph[node.first]) {
      if (!in[next]) {
        st.push({next, 1});
        st.push({next, 0});
      }
    }
  }
  return order;
}

std::vector<std::vector<int>>
dfs_iterative(const std::vector<std::vector<int>> &graph) {
  int n = graph.size();
  std::vector<bool> in(n, false), out(n, false);
  std::vector<std::vector<int>> component_order;
  for (int i = 0; i < n; i++) {
    if (!out[i])
      component_order.push_back(dfs_impl(graph, i, in, out));
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
    return 0;

  std::vector<std::vector<int>> graph(n, std::vector<int>{});
  for (int i = 0; i < m; i++) {
    std::cin >> a >> b;
    graph[a].push_back(b);
    if (d == 0)
      graph[b].push_back(a);
  }

  auto result = dfs_iterative(graph);
  std::cout << "\n Number of components in the graph : \n" << result.size();
  for (int i = 0; i < result.size(); i++) {
    for (const auto &v : result[i]) {
      std::cout << v << " ";
    }
    std::cout << "\n";
  }
  return 0;
}