#include <iostream>
#include <queue>
#include <vector>

constexpr int INF = 1'000'000'000;

using AdjMatrix = std::vector<std::vector<int>>;

int FlowDFS(AdjMatrix& G, std::vector<bool>& used, int snk, int u, int flow = INF) {
    used[u] = true;
    if (u == snk) {
        return flow;
    }
    int n = G.size() - 1, new_flow = 0;
    for (int v = 1; v <= n; ++v) {
        if (!used[v] && G[u][v] && (new_flow = FlowDFS(G, used, snk, v, std::min(flow, G[u][v])))) {
            G[u][v] -= new_flow;
            G[v][u] += new_flow;
            return new_flow;
        }
    }
    return 0;
}

int FordFulkerson(AdjMatrix& G, int src, int snk) {
    int flow = 0, delta = 0;
    std::vector<bool> used;
    do {
        used.assign(G.size(), false);
        delta = FlowDFS(G, used, snk, src);
        flow += delta;
    } while (delta);
    return flow;
}

struct Edge {
    int c, w;
    Edge(int c, int w) : c(c), w(w) {}
};

using CostMatrix = std::vector<std::vector<std::vector<Edge>>>;

auto SPFA(const CostMatrix& G, int src) {
    int n = G.size() - 1;
    std::vector<int> d(n + 1, INF);
    d[src] = 0;
    std::queue<int> q;
    q.push(src);
    std::vector<bool> used(n + 1);
    used[src] = true;
    std::vector<std::pair<int, int>> p(n + 1);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        used[u] = false;
        for (int v = 1; v <= n; ++v) {
            for (int idx = 0; idx < G[u][v].size(); ++idx) {
                auto [c, w] = G[u][v][idx];
                if (w && d[u] + c < d[v]) {
                    d[v] = d[u] + c;
                    p[v] = {u, idx};
                    if (!used[v]) {
                        q.push(v);
                        used[v] = true;
                    }
                }
            }
        }
    }
    return p;
}

auto MinCostFlow(CostMatrix& G, int src, int snk, int k = INF) {
    int cost = 0, flow = 0;
    do {
        auto p = SPFA(G, src);
        if (!p[snk].first) {
            break;
        }
        int v = snk, df = k - flow;
        while (v != src) {
            auto [u, idx] = p[v];
            df = std::min(df, G[u][v][idx].w);
            v = u;
        }
        v = snk;
        while (v != src) {
            auto [u, idx] = p[v];
            cost += df * G[u][v][idx].c;
            G[u][v][idx].w -= df;
            G[v][u][idx].w += df;
            v = u;
        }
        flow += df;
    } while (flow < k);
    return std::make_pair(cost, flow);
}

int main() {
    return 0;
}
