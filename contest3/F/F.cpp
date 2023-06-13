#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

const int kMod = 1e9;

struct Node {
  Node* left;
  Node* right;
  Node* parent;
  long long key;
  int prior;
  long long size;
  Node(long long key)
      : left(nullptr),
        right(nullptr),
        parent(nullptr),
        key(key),
        prior(std::rand() % kMod),
        size(key) {}
};

void Update(Node* root) {
  if (root == nullptr) {
    return;
  }
  root->size = root->key;
  if (root->left != nullptr) {
    root->left->parent = root;
    root->size += root->left->size;
  }
  if (root->right != nullptr) {
    root->right->parent = root;
    root->size += root->right->size;
  }
}

Node* Merge(Node* root1, Node* root2) {
  if (root1 == nullptr) {
    return root2;
  }
  if (root2 == nullptr) {
    return root1;
  }
  if (root1->prior < root2->prior) {
    root1->right = Merge(root1->right, root2);
    Update(root1);
    return root1;
  }
  root2->left = Merge(root1, root2->left);
  Update(root2);
  return root2;
}

void Add(Node* to_add, Node* current, Node*& root) {
  if (to_add->prior > current->prior) {
    if (current->right != nullptr) {
      to_add->left = current->right;
      to_add->left->parent = to_add;
    }
    to_add->parent = current;
    current->right = to_add;
    return;
  }
  if (current == root) {
    to_add->left = root;
    to_add->left->parent = to_add;
    root = to_add;
    return;
  }
  Add(to_add, current->parent, root);
}

std::pair<Node*, Node*> Split(Node* root, int key_split) {
  if (root == nullptr) {
    return {nullptr, nullptr};
  }
  if (root->key < key_split) {
    std::pair<Node*, Node*> temp = Split(root->right, key_split);
    root->right = temp.first;
    Update(root);
    Update(temp.second);
    return {root, temp.second};
  }
  std::pair<Node*, Node*> temp = Split(root->left, key_split);
  root->left = temp.second;
  Update(root);
  Update(temp.first);
  return {temp.first, root};
}

bool Find(Node* root, long long key) {
  if (root == nullptr) {
    return false;
  }
  if (root->key == key) {
    return true;
  }
  return (root->key < key) ? Find(root->right, key) : Find(root->left, key);
}

void Print(Node* root) {
  if (root == nullptr) {
    return;
  }
  std::cout << root->key << '\n';
  Print(root->left);
  Print(root->right);
}

Node* Insert(Node* root, long long x) {
  if (Find(root, x)) {
    return root;
  }
  Node* new_node = new Node(x);
  std::pair<Node*, Node*> temp = Split(root, x);
  temp.first = Merge(temp.first, new_node);
  Update(temp.first);
  root = Merge(temp.first, temp.second);
  Update(root);
  return root;
}

void Delete(Node*& root, long long key) {
  if (!Find(root, key)) {
    return;
  }
  std::pair<Node*, Node*> temp = Split(root, key);
  std::pair<Node*, Node*> right_temp = Split(temp.second, key + 1);
  delete right_temp.first;
  root = Merge(temp.first, right_temp.second);
  Update(root);
}

Node* GoRight(Node* root) {
  if (root == nullptr) {
    return nullptr;
  }
  if (root->right == nullptr) {
    return root;
  }
  return GoRight(root->right);
}

Node* GoLeft(Node* root) {
  if (root == nullptr) {
    return nullptr;
  }
  if (root->left == nullptr) {
    return root;
  }
  return GoLeft(root->left);
}

Node* GetNext(Node* root, int x) {
  std::pair<Node*, Node*> temp = Split(root, x + 1);
  Node* next = GoLeft(temp.second);
  root = Merge(temp.first, temp.second);
  Update(root);
  return next;
}

Node* GetPrev(Node* root, int x) {
  std::pair<Node*, Node*> temp = Split(root, x);
  Node* next = GoRight(temp.first);
  root = Merge(temp.first, temp.second);
  Update(root);
  return next;
}

int Size(Node* root) {
  if (root == nullptr) {
    return 0;
  }
  return root->size;
}

std::pair<Node*, Node*> SizeSplit(Node* root, int size) {  // |left| = size.
  if (root == nullptr) {
    return {nullptr, nullptr};
  }
  if (Size(root->left) >= size) {
    std::pair<Node*, Node*> temp = SizeSplit(root->left, size);
    root->left = temp.second;
    Update(root);
    return {temp.first, root};
    return {temp.first, Merge(temp.second, root->right)};
  }
  std::pair<Node*, Node*> temp =
      SizeSplit(root->right, size - Size(root->left) - 1);
  root->right = temp.first;
  Update(root);
  return {root, temp.second};
}

Node* GetKth(Node* root, int size) {
  if (Size(root) < size) {
    return nullptr;
  }
  std::pair<Node*, Node*> temp = SizeSplit(root, size);
  Node* key = (temp.first != nullptr ? GoRight(temp.first) : nullptr);
  root = Merge(temp.first, temp.second);
  Update(root);
  return key;
}

void Clear(Node* root) {
  if (root == nullptr) {
    return;
  }
  Clear(root->left);
  Clear(root->right);
  delete root;
}

void ProcessRequest(int n) {
  Node* root = nullptr;
  char request;
  bool id = false;
  std::vector<long long> sum;
  for (int i = 0; i < n; ++i) {
    std::cin >> request;
    if (request == '?') {
      int l, r;
      std::cin >> l >> r;
      std::pair<Node*, Node*> left = Split(root, l);
      std::pair<Node*, Node*> right = Split(left.second, r + 1);
      sum.push_back(right.first != nullptr ? right.first->size : 0);
      root = Merge(left.first, Merge(right.first, right.second));
      id = true;
      continue;
    }
    int key;
    std::cin >> key;
    if (id) {
      root = Insert(root, (key + sum.back()) % kMod);
    } else {
      root = Insert(root, key);
    }
    id = false;
  }
  Clear(root);
  for (long long s : sum) {
    std::cout << s << '\n';
  }
}

int main() {
  srand((unsigned)time(0));
  int n;
  std::cin >> n;
  ProcessRequest(n);
}