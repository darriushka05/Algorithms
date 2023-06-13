#include <iostream>
#include <algorithm>
#include <deque>
#include "vector"
#include "set"
#include "queue"

using namespace std;

int n, m;

vector<int> parent;
vector<int> vrank;

void make_set(int v) {
    parent[v] = v;
    vrank[v] = v;
}

int find_set(int v) {
    if (v == parent[v]) {
        return v;
    }
    return parent[v] = find_set(parent[v]);
}

void union_sets(int v, int u) {
    int a = find_set(v);
    int b = find_set(u);
    if (a != b) {
        if (vrank[a] < vrank[b]) {
            swap(a, b);
        }
        parent[b] = a;
        if (vrank[a] == vrank[b]) {
            ++vrank[a];
        }
    }
}

int main() {
    cin >> n >> m;

    parent.resize(n + 1, 0);
    vrank.resize(n + 1, 0);

    vector<pair<int, pair<int, int>>> edges;

    for (int i = 1; i < m + 1; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        edges.push_back({c, {a, b}});
    }

    vector<pair<int, int>> res;
    std::sort(edges.begin(), edges.end());

    for (int i = 1; i < n + 1; ++i) {
        make_set(i);
    }
    int cost = 0;

    for (int i = 0; i < m; ++i) {
        int a = edges[i].second.first;
        int b = edges[i].second.second;
        int l = edges[i].first;

        if (find_set(a) != find_set(b)) {
            cost += l;
            res.push_back(edges[i].second);
            union_sets(a, b);
        }
    }

    cout << cost;
}