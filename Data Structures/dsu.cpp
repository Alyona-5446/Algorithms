#include <iostream>
#include <vector>

class DSU {
    std::vector<int> p, ranks;
    int cmp_cnt;
public:
    DSU(int n) : p(n + 1), ranks(n + 1, 1), cmp_cnt(n) {
        for (int i = 1; i <= n; ++i) {
            p[i] = i;
        }
    }
    int find_set(int k) {
        if (p[k] != k) {
            p[k] = find_set(p[k]);
        }
        return p[k];
    }
    void unite_sets(int u, int v) {
        u = find_set(u);
        v = find_set(v);
        if (u != v) {
            if (ranks[u] > ranks[v]) {
                std::swap(u, v);
            }
            p[u] = v;
            ranks[v] += ranks[u];
            --cmp_cnt;
        }
    }
    int get_cnt() {
        return cmp_cnt;
    }
};

int main() {
    return 0;
}
