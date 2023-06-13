#include <deque>
#include <iostream>
#include <stack>
#include <vector>

enum Color { WHITE, GREY, BLACK };

class Graph {
 private:
  std::vector<std::vector<int>> graph_;
  std::vector<int> answer_;
  int num_of_cycles_;

  bool DFS(size_t idx, std::vector<Color> &is_used) {
    is_used[idx] = GREY;
    for (auto i : graph_[idx]) {
      if (is_used[i] == WHITE) {
        DFS(i, is_used);
      }
      if (is_used[i] == GREY) {
        return false;
      }
    }
    is_used[idx] = BLACK;
    answer_.push_back(idx);
    return true;
  }

 public:
  explicit Graph(int num_of) : graph_(num_of), num_of_cycles_(0) {
  }

  void Insert(int i, int j) {
    graph_[i].push_back(j);
  }

  void TopSort() {
    std::vector<Color> is_used(graph_.size(), WHITE);
    for (size_t i = 0; i < graph_.size(); i++) {
      if (is_used[i] == WHITE) {
        if (!DFS(i, is_used)) {
          answer_.clear();
          answer_.push_back(-2);
          return;
        }
      }
    }
  }

  void Answer() {
    for (auto i = int(answer_.size() - 1); i >= 0; i--) {
      std::cout << answer_[i] + 1 << " ";
    }
  }
};

int main() {
  int members, num_of;
  std::cin >> members >> num_of;
  Graph graph(members);
  for (int i = 0; i < num_of; i++) {
    size_t from, to;
    std::cin >> from >> to;
    graph.Insert(--from, --to);
  }
  graph.TopSort();
  graph.Answer();
  std::cout << '\n';
  return 0;
}