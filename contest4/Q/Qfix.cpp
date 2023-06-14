#include <iostream>
#include <algorithm>
#include <deque>
#include <vector>
#include <set>
#include <queue>
class DisjointSetUnion {
 private:
  std::vector<int> parent_;
  std::vector<int> vrank_;
 public:
  DisjointSetUnion(int num_of) :parent_(num_of + 1), vrank_(num_of + 1) {}
  void make_set(int v) {
    parent_[v] = v;
    vrank_[v] = v;
  }

  int find_set(int v) {
    if (v == parent_[v]) {
      return v;
    }
    return parent_[v] = find_set(parent_[v]);
  }

  void union_sets(int v, int u) {
    int a = find_set(v);
    int b = find_set(u);
    if (a != b) {
      if (vrank_[a] < vrank_[b]) {
        std::swap(a, b);
      }
      parent_[b] = a;
      if (vrank_[a] == vrank_[b]) {
        ++vrank_[a];
      }
    }
  }
};

int main() {
  int n, m;
  std::cin >> n >> m;
  DisjointSetUnion dsu (n);
  std::vector<std::pair<int, std::pair<int, int>>> edges;

  for (int i = 1; i < m + 1; ++i) {
    int from, to, weight;
    std::cin >> from >> to >> weight;
    edges.push_back({weight, {from, to}});
  }

  std::vector<std::pair<int, int>> res;
  std::sort(edges.begin(), edges.end());

  for (int i = 1; i < n + 1; ++i) {
    dsu.make_set(i);
  }
  int cost = 0;

  for (int i = 0; i < m; ++i) {
    int from = edges[i].second.first;
    int to = edges[i].second.second;
    int weight = edges[i].first;

    if (dsu.find_set(from) != dsu.find_set(to)) {
      cost += weight;
      res.push_back(edges[i].second);
      dsu.union_sets(from, to);
    }
  }

  std::cout << cost;
  return 0;
}