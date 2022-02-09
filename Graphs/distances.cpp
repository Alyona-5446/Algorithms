#include <iostream>
#include <queue>
#include <tuple>
#include <vector>

constexpr int INF = 1'000'000'000;

template<typename T>
using MinHeap = std::priority_queue<T, std::vector<T>, std::greater<T>>;

using Graph = std::vector<std::vector<std::pair<int, int>>>;
using Matrix = std::vector<std::vector<int>>;

auto Dijkstra(const Graph& G, int src) {
    std::vector<int> d(G.size(), INF);
    d[src] = 0;
    MinHeap<std::pair<int, int>> q;
    q.emplace(d[src], src);
    std::vector<bool> used(G.size());
    while (!q.empty()) {
        auto [dst, u] = q.top();
        q.pop();
        if (!used[u]) {
            used[u] = true;
            for (auto [c, v] : G[u]) {
                if (dst + c < d[v]) {
                    d[v] = dst + c;
                    q.emplace(d[v], v);
                }
            }
        }
    }
    return d;
}

auto FordBellman(const std::vector<std::tuple<int, int, int>>& edges, int n, int src) {
    std::vector<int> d(n + 1, INF);
    d[src] = 0;
    bool changed = true;
    while (changed) {
        changed = false;
        for (auto [u, v, c] : edges) {
            if (d[u] != INF && d[u] + c < d[v]) {
                d[v] = d[u] + c;
                changed = true;
            }
        }
    }
    return d;
}

auto SPFA(const Graph& G, int src) {
    std::vector<int> d(G.size(), INF);
    d[src] = 0;
    std::queue<int> q;
    q.push(src);
    std::vector<bool> used(G.size());
    used[src] = true;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        used[u] = false;
        for (auto [c, v] : G[u]) {
            if (d[u] + c < d[v]) {
                d[v] = d[u] + c;
                if (!used[v]) {
                    q.push(v);
                }
            }
        }
    }
    return d;
}

auto FloydWarshall(const Matrix& G) {
    int n = G.size() - 1;
    Matrix d(G);
    for (int k = 1; k <= n; ++k) {
        for (int u = 1; u <= n; ++u) {
            for (int v = 1; v <= n; ++v) {
                if (d[u][k] != INF && d[k][v] != INF) {
                    d[u][v] = std::min(d[u][v], d[u][k] + d[k][v]);
                }
            }
        }
    }
    return d;
}

int main() {
    return 0;
}
