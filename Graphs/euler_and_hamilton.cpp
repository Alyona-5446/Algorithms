#include <algorithm>
#include <iostream>
#include <stack>
#include <unordered_set>
#include <vector>

constexpr int INF = 1'000'000'000;

using ErasableList = std::vector<std::unordered_set<int>>;
using AdjMatrix = std::vector<std::vector<int>>;

auto EulerCycle(ErasableList& G, int src) {
    std::stack<int> st;
    std::vector<int> cycle;
    st.push(src);
    while (!st.empty()) {
        int u = st.top();
        if (G[u].empty()) {
            cycle.push_back(u);
            st.pop();
        } else {
            int v = *G[u].begin();
            G[u].erase(v);
            G[v].erase(u);
            st.push(v);
        }
    }
    return cycle;
}

auto MinHamiltonPath(const AdjMatrix& G) {
    int n = G.size() - 1;
    std::vector<std::vector<int>> dp(1 << n, std::vector<int>(n + 1, INF));
    for (int u = 1; u <= n; ++u) {
        dp[1 << (u - 1)][u] = 0;
    }
    for (int mask = 3; mask < (1 << n); ++mask) {
        for (int u = 1; u <= n; ++u) {
            if ((mask >> (u - 1)) & 1) {
                int sub = mask ^ (1 << (u - 1));
                for (int v = 1; v <= n; ++v) {
                    if ((sub >> (v - 1)) & 1) {
                        dp[mask][u] = std::min(dp[mask][u], dp[sub][v] + G[v][u]);
                    }
                }
            }
        }
    }
    int u = std::min_element(dp.back().begin(), dp.back().end()) - dp.back().begin();
    int cost = dp.back()[u], mask = (1 << n) - 1;
    std::vector<int> path;
    while (mask) {
        path.push_back(u);
        int sub = mask ^ (1 << (u - 1));
        for (int v = 1; v <= n; ++v) {
            if (dp[mask][u] == dp[sub][v] + G[v][u]) {
                u = v;
                break;
            }
        }
        mask = sub;
    }
    return std::make_pair(cost, path);
}

int main() {
    return 0;
}
