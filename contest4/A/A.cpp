#include <iostream>
#include <iterator>
#include <list>
#include <vector>

class HashTable {
 public:
  HashTable(int n)
      : size_(n), data_(std::vector<std::list<int64_t>>(n)) {}
  void Add(int64_t number) { data_[Hash(number)].push_front(number); }
  void Erase(int64_t number);
  bool IsThere(int64_t number) const {
    return Find(number) != data_[Hash(number)].end();
  };

 private:
  size_t size_;
  std::vector<std::list<int64_t>> data_;
  const int64_t kHash1 = 2473, kHash2 = 1117;
  int64_t Hash(int64_t number) const {
    return (kHash1 * number + kHash2) % size_;
  }
  std::list<int64_t>::const_iterator Find(int64_t number) const;
};

std::list<int64_t>::const_iterator HashTable::Find(int64_t number) const {
  std::list<int64_t>::const_iterator it = data_[Hash(number)].begin();
  while (it != data_[Hash(number)].end() && *it != number) {
    ++it;
  }
  return it;
}

void HashTable::Erase(int64_t number) {
  std::list<int64_t>::const_iterator it = Find(number);
  while (it != data_[Hash(number)].end()) {
    data_[Hash(number)].erase(it);
    it = Find(number);
  }
}

int main() {
  int n;
  std::cin >> n;
  HashTable set(n);
  for (int i = 0; i < n; ++i) {
    int num;
    char request;
    std::cin >> request >> num;
    if (request == '+') {
      set.Add(num);
    }
    if (request == '-') {
      set.Erase(num);
    }
    if (request == '?') {
      if (set.IsThere(num)) {
        std::cout << "YES";
      } else {
        std::cout << "NO";
      }
      std::cout << '\n';
    }
  }
}

