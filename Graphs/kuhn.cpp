#include <iostream>
#include <vector>

using AdjList = std::vector<std::vector<int>>;

bool KuhnDFS(const AdjList& G, std::vector<bool>& used, std::vector<int>& match, int u) {
    used[u] = true;
    for (auto v : G[u]) {
        if (!match[v] || (!used[match[v]] && KuhnDFS(G, used, match, match[v]))) { //separate cycle heuristic
            match[v] = u;
            return true;
        }
    }
    return false;
}

auto Kuhn(const AdjList& G, int n, int m) { //greedy and clear used when necessary heuristics
    std::vector<int> match(m + 1);
    std::vector<bool> used;
    for (int u = 1; u <= n; ++u) {
        used.assign(n + 1, false);
        KuhnDFS(G, used, match, u);
    }
    std::vector<std::pair<int, int>> matching;
    for (int v = 1; v <= m; ++v) {
        if (match[v]) {
            matching.emplace_back(match[v], v);
        }
    }
    return matching;
}

auto modified_Kuhn(const AdjList& G, int n, int m) {
    std::vector<int> match(m + 1);
    std::vector<bool> used;
    bool repeat;
    do {
        repeat = false;
        used.assign(n + 1, false);
        for (int u = 1; u <= n; ++u) {
            if (!used[u] && KuhnDFS(G, used, match, u)) {
                repeat = true;
            }
        }
    } while (repeat);
    std::vector<std::pair<int, int>> matching;
    for (int v = 1; v <= m; ++v) {
        if (match[v]) {
            matching.emplace_back(match[v], v);
        }
    }
    return matching;
}

int main() {
    return 0;
}
