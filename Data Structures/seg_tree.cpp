#include <functional>
#include <iostream>
#include <vector>

template<typename T>
class SegTree {
private:
    std::vector<T> tree;
    std::function<T(const T&, const T&)> op;
    T nil;
    int sz = 1;
public:
    SegTree(const std::vector<T>& v, const std::function<T(const T&, const T&)>& op, const T& nil) : op(op), nil(nil) {
        int n = v.size();
        while (sz < n) {
            sz <<= 1;
        }
        tree.assign(2 * sz - 1, nil);
        for (int i = 0; i < n; ++i) {
            tree[sz - 1 + i] = v[i];
        }
        for (int i = sz - 2; i >= 0; --i) {
            tree[i] = op(tree[2 * i + 1], tree[2 * i + 2]);
        }
    }
    T get_op(int left, int right, int l = 0, int r = -1, int x = 0) const {
        if (r == -1) {
            r = sz;
        }
        if (l == left && r == right) {
            return tree[x];
        }
        int mid = (l + r) / 2;
        T ans = nil;
        if (left < mid) {
            ans = op(ans, get_op(left, std::min(mid, right), l, mid, 2 * x + 1));
        }
        if (right > mid) {
            ans = op(ans, get_op(std::max(mid, left), right, mid, r, 2 * x + 2));
        }
        return ans;
    }
    void set_value(const T& val, int idx, int l = 0, int r = -1, int x = 0) {
        if (r == -1) {
            r = sz;
        }
        if (l + 1 == r) {
            tree[x] = val;
            return;
        }
        int mid = (l + r) / 2;
        if (idx < mid) {
            set_value(val, idx, l, mid, 2 * x + 1);
        } else {
            set_value(val, idx, mid, r, 2 * x + 2);
        }
        tree[x] = op(tree[2 * x + 1], tree[2 * x + 2]);
    }
};

int main() {
    return 0;
}
