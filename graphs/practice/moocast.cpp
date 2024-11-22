// https://usaco.org/index.php?page=viewproblem2&cpid=668
#include <cassert>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

int dfs(const vector<vector<int>> &graph, int root, vector<int> &visitation,
        int visit) {
  int count = 1;
  visitation[root] = visit;

  for (auto &next : graph[root]) {
    if (visitation[next] != visit) {
      count += dfs(graph, next, visitation, visit);
    }
  }
  return count;
}

int solve(const vector<vector<int>> &graph) {
  size_t n = graph.size();
  vector<int> visitation(n, -1);
  int res = 0, visit = 0;
  for (size_t i = 0; i < n; i++) {
    if (visitation[i] == -1) {
      int val = dfs(graph, i, visitation, visit++);
      cout << val;
      res = max(res, val);
    }
  }
  return res;
}

int main() {
  freopen("moocast.in", "r", stdin);
  int cow_num;
  cin >> cow_num;
  vector<int> x(cow_num), y(cow_num);
  vector<int> power(cow_num);
  for (int c = 0; c < cow_num; c++) {
    cin >> x[c] >> y[c] >> power[c];
  }

  vector<vector<int>> graph(cow_num, vector<int>{});
  for (int i = 0; i < cow_num; i++) {
    for (int j = 0; j < cow_num; j++) {
      int dist_squared =
          ((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]));
      if (dist_squared <= power[i] * power[i]) {
        graph[i].push_back(j);
      }
    }
  }

  int max_cows = solve(graph);
  freopen("moocast.out", "w", stdout);
  cout << max_cows << endl;
}