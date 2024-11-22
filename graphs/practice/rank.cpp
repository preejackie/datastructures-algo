#include<vector>
#include<iostream>
#include<algorithm>
using namespace std;

/*
  Do a dfs(v) for each node in graph, while there is a path from v to v
  in dfs, then v is in the cyclic.
*/

bool dfs(const vector<vector<int>> &graph, vector<bool> &visited, int root, int curr) {
  visited[curr] = true;
  bool ok = false;
  for (auto &next : graph[curr]) {
    if (next == root) { //root belongs a cycle
      return true;
    }
    if (!visited[next])
      ok |= dfs(graph, visited, root, next);
  }
  return ok;
}

int solve(const vector<vector<int>> &graph) {
  size_t n = graph.size();
  vector<bool> visited(n, false);
  size_t count = 0;
  for (size_t i=0; i<n; i++) {
    std::fill(visited.begin(), visited.end(), false);
    count += dfs(graph, visited, i, i) ? 1 : 0;
  }
  return count;
}


int main() {
  int n,k,a,b,s_a, s_b, ans;
  cin >> n >> k;
  vector<vector<int>> graph(n, vector<int>{});

  for (int i=0; i<k; i++) {
    cin >> a >> b >> s_a >> s_b;
    --a;
    --b;
    if (s_a > s_b)
      graph[a].push_back(b);
    else
      graph[b].push_back(a);
  }
  ans = solve(graph);
  cout << ans << endl;
  return 0;
}