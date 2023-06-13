#include <iostream>
#include <string>
#include <vector>

std::vector<int> Includes(const std::string &string, const size_t size) {
  std::vector<int> position(string.size(), 0);
  std::vector<int> result;
  for (int i = 1; i < string.size(); ++i) {
    int tmp = position[i - 1];
    while (tmp > 0 && string[i] != string[tmp]) {
      tmp = position[tmp - 1];
    }
    if (string[i] == string[tmp]) {
      tmp++;
    }
    position[i] = tmp;
    if (tmp == size) {
      result.push_back(i - 2 * size);
    }
  }
  return result;
}

int main() {
  std::string word, text;
  std::cin >> text >> word;
  auto str = word + '#' + text;
  auto result(std::move(Includes(str, word.size())));
  for (auto &inc : result) {
    std::cout << inc << '\n';
  }
  return 0;
}