#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

struct Dest {
  size_t weight;
  size_t to;
};

struct Vertex {
  size_t id;
  size_t dist;
};

struct CompareVertex {
  bool operator()(const Vertex &from, const Vertex &to) const {
    if (from.dist < to.dist) {
      return true;
    }
    return (from.dist == to.dist && from.id < to.id);
  }
};

class Graph {
 public:
  explicit Graph(size_t);
  void InsertEdge(size_t, size_t, size_t);
  std::vector<size_t> FindAllDist(size_t);

 private:
  const size_t k_max_dist_ = INT64_MAX;
  std::vector<std::vector<Dest>> adj_list_;
  std::vector<size_t> Dijkstra(size_t begin) {
    std::vector<size_t> dist(adj_list_.size(), k_max_dist_);
    dist[begin] = 0;
    std::set<Vertex, CompareVertex> smallest_edge_to;
    for (size_t i = 0; i < adj_list_.size(); i++) {
      smallest_edge_to.insert({i, dist[i]});
    }
    while (!smallest_edge_to.empty()) {
      auto min_ver = *smallest_edge_to.begin();
      smallest_edge_to.erase(smallest_edge_to.begin());
      for (auto &dest : adj_list_[min_ver.id]) {
        if (smallest_edge_to.find({dest.to, dist[dest.to]}) != smallest_edge_to.end() &&
            dist[dest.to] > (dist[min_ver.id] + dest.weight)) {
          smallest_edge_to.erase({dest.to, dist[dest.to]});
          dist[dest.to] = dist[min_ver.id] + dest.weight;
          smallest_edge_to.insert({dest.to, dist[dest.to]});
        }
      }
    }
    return dist;
  }
};

Graph::Graph(size_t size) : adj_list_(size) {
}

void Graph::InsertEdge(size_t f_ver, size_t s_ver, size_t weight) {
  adj_list_[f_ver].push_back({weight, s_ver});
  adj_list_[s_ver].push_back({weight, f_ver});
}

std::vector<size_t> Graph::FindAllDist(size_t vertex) {
  return Dijkstra(vertex);
}

int main() {
  int64_t num_of_ver, num_of_edges, num_of_points;
  std::cin >> num_of_ver >> num_of_edges >> num_of_points;
  Graph graph(num_of_ver);
  std::vector<int64_t> points(num_of_points);
  for (int64_t i = 0; i < num_of_points; ++i) {
    std::cin >> points[i];
    points[i]--;
  }
  for (int64_t i = 0; i < num_of_edges; i++) {
    int64_t from, to, weight;
    std::cin >> from >> to >> weight;
    graph.InsertEdge(--from, --to, weight);
  }
  int64_t begin, end;
  std::cin >> begin >> end;
  auto dist = graph.FindAllDist(--end);
  begin--;
  for (auto &i : points) {
    if (dist[i] <= dist[begin]) {
      std::cout << -1;
      return 0;
    }
  }
  std::cout << dist[begin];
  return 0;
}