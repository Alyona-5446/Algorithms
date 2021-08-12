#include <iostream>
#include <tuple>
#include <vector>

class PersistDSU {
private:
    using Event = std::tuple<int, int, int, int>;
    std::vector<Event> history;
    std::vector<int> sets, ranks;
public:
    int set_cnt;
    PersistDSU(int n) : sets(n + 1), ranks(n + 1, 1), set_cnt(n) {
        for (int i = 1; i <= n; ++i) {
            sets[i] = i;
        }
    }
    int get_set(int k) {
        return sets[k] == k ? k : get_set(sets[k]);
    }
    bool unite_sets(int u, int v) {
        u = get_set(u);
        v = get_set(v);
        if (u != v) {
            if (ranks[u] > ranks[v]) {
                std::swap(u, v);
            }
            history.emplace_back(u, sets[u], v, ranks[v]);
            sets[u] = v;
            ranks[v] += ranks[u];
            --set_cnt;
            return true;
        }
        return false;
    }
    void roll_back() {
        auto [u, s, v, r] = history.back();
        sets[u] = s;
        ranks[v] = r;
        history.pop_back();
        ++set_cnt;
    }
};

struct Query {
    int u, v;
    bool bridge;
    Query(int u, int v) : u(u), v(v) {}
};

class QTree {
private:
    std::vector<std::vector<Query>> tree;
    PersistDSU dsu;
    int sz = 1;
public:
    QTree(int n, int m) : dsu(n) {
        while (sz < m) {
            sz <<= 1;
        }
        tree.assign(2 * sz - 1, {});
    }
    void add(Query& q, int left, int right, int l = 0, int r = -1, int x = 0) {
        if (r == -1) {
            r = sz;
        }
        if (l == left && r == right) {
            tree[x].push_back(q);
            return;
        }
        int mid = (l + r) / 2;
        if (left < mid) {
            add(q, left, std::min(mid, right), l, mid, 2 * x + 1);
        }
        if (right > mid) {
            add(q, std::max(mid, left), right, mid, r, 2 * x + 2);
        }
    }
    void DFS(std::vector<int>& ans, int l = 0, int r = -1, int x = 0) {
        if (r == -1) {
            r = sz;
        }
        for (auto& q : tree[x]) {
            q.bridge = dsu.unite_sets(q.u, q.v);
        }
        if (l + 1 == r) {
            ans[l] = dsu.set_cnt;
        } else {
            int mid = (l + r) / 2;
            DFS(ans, l, mid, 2 * x + 1);
            DFS(ans, mid, r, 2 * x + 2);
        }
        for (auto& q : tree[x]) {
            if (q.bridge) {
                dsu.roll_back();
            }
        }
    }
    void get_ans(int m) {
        std::vector<int> ans(sz);
        DFS(ans);
        for (int i = 0; i <= m; ++i) {
            std::cout << ans[i] << ' ';
        }
        std::cout << '\n';
    }
};

int main() {
    return 0;
}
