#include <algorithm>
#include <iostream>
int Check(int number, int lighted, int light, const int* recievers,
          int wizards) {
  int right = recievers[number - 1] - recievers[0], mid = right / 2;
  int left = 0;
  while (right - left > 1) {
    for (int i = 0; i < number; i++) {
      if (recievers[i] > lighted) {
        light = light + 1, lighted = recievers[i] + mid;
      }
    }
    if (light <= wizards) {
      right = mid;
    } else {
      left = mid;
    }
    mid = (left + right) / 2, light = 0, lighted = recievers[0] - 1;
  }
  return right;
}
int main() {
  int number, wizards, light = 0;
  int* recievers;
  std::cin >> number >> wizards;
  recievers = new int[number];
  for (int i = 0; i < number; i++) {
    std::cin >> recievers[i];
  }
  int *beg = recievers, *ent = recievers + number;
  std::sort(beg, ent);
  int lighted = recievers[0] - 1;
  int unique = 1;
  for (int i = 1; i < number; i++) {
    if (recievers[i] != recievers[i - 1]) {
      unique++;
    }
  }
  if (unique <= wizards) {
    std::cout << 0;
  } else {
    std::cout << Check(number, lighted, light, recievers, wizards);
  }
  delete[] recievers;
}