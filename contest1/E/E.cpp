#include <iostream>
#include <stack>

const int kMaxN = 1e6 + 1;

long long GetMaxArea(int n, long long* heights) {
  std::stack<std::pair<long long, long long>> increasing_sequence;
  increasing_sequence.push({-1, -1});
  long i = 0;
  long long max_area = 0;
  while (i < n) {
    if (heights[i] > increasing_sequence.top().first) {
      increasing_sequence.push({heights[i], i});
      ++i;
    } else if (!increasing_sequence.empty()) {
      long long middle_height = increasing_sequence.top().first;
      increasing_sequence.pop();
      max_area = std::max(
          max_area, middle_height * (i - increasing_sequence.top().second - 1));
    }
  }
  return max_area;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  int n;
  std::cin >> n;
  long long heights[kMaxN];
  for (int i = 0; i < n; ++i) {
    std::cin >> heights[i];
  }
  heights[n] = 0;
  std::cout << GetMaxArea(n + 1, heights);
}