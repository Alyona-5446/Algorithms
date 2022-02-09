#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

constexpr int INF = 1'000'000'000;

template<typename T>
using MinHeap = std::priority_queue<T, std::vector<T>, std::greater<T>>;

using AdjList = std::vector<std::vector<std::pair<int, int>>>;

struct Edge {
    int u, v, w;
    Edge(int u, int v, int w) : u(u), v(v), w(w) {}
    friend bool operator<(const Edge& e1, const Edge& e2) {
        return e1.w < e2.w;
    }
};

class DSU {
    std::vector<int> p, ranks;
public:
    DSU(int n) : p(n + 1), ranks(n + 1, 1) {
        for (int u = 1; u <= n; ++u) {
            p[u] = u;
        }
    }
    int get_set(int u) {
        if (p[u] != u) {
            p[u] = get_set(p[u]);
        }
        return p[u];
    }
    bool unite_sets(int u, int v) {
        u = get_set(u), v = get_set(v);
        if (u != v) {
            if (ranks[u] > ranks[v]) {
                std::swap(u, v);
            }
            p[u] = v;
            ranks[v] += ranks[u];
            return true;
        }
        return false;
    }
};

auto Kruskal(std::vector<Edge>& edges, int n) {
    std::sort(edges.begin(), edges.end());
    DSU dsu(n);
    std::vector<Edge> mst;
    for (auto [u, v, w] : edges) {
        if (dsu.unite_sets(u, v)) {
            mst.emplace_back(u, v, w);
        }
    }
    return mst;
}

auto Prim(const AdjList& G, int src) {
    std::vector<int> dst(G.size(), INF), p(G.size());
    dst[src] = 0;
    std::vector<bool> used(G.size());
    used[src] = true;
    MinHeap<std::pair<int, int>> q;
    for (auto [v, w] : G[src]) {
        q.emplace(w, v);
    }
    std::vector<Edge> mst;
    while (!q.empty()) {
        auto [c, u] = q.top();
        q.pop();
        if (!used[u]) {
            mst.emplace_back(p[u], u, c);
            for (auto [v, w] : G[u]) {
                if (!used[v] && w < dst[v]) {
                    dst[v] = w;
                    p[v] = u;
                    q.emplace(w, v);
                }
            }
        }
    }
    return mst;
}

int main() {
    return 0;
}
