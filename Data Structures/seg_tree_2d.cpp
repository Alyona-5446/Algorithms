#include <functional>
#include <iostream>
#include <vector>

template<typename T>
class SegTree2D {
private:
    std::vector<std::vector<T>> tree;
    std::function<T(T, T)> op;
    T nil;
    int x_sz = 1, y_sz = 1;
    void set_y(T val, int y, int kx, int ly = 0, int ry = -1, int ky = 0) {
        if (ry == -1) {
            ry = y_sz;
        }
        if (ly + 1 == ry) {
            tree[kx][ky] = val;
            return;
        }
        int mid = (ly + ry) / 2;
        if (y < mid) {
            set_y(val, y, kx, ly, mid, 2 * ky + 1);
        } else {
            set_y(val, y, kx, mid, ry, 2 * ky + 2);
        }
        tree[kx][ky] = op(tree[kx][2 * ky + 1], tree[kx][2 * ky + 2]);
    }
    T get_y(int y1, int y2, int kx, int ly = 0, int ry = -1, int ky = 0) {
        if (ry == -1) {
            ry = y_sz;
        }
        if (ly == y1 && ry == y2) {
            return tree[kx][ky];
        }
        int mid = (ly + ry) / 2;
        T ans = nil;
        if (y1 < mid) {
            ans = op(ans, get_y(y1, std::min(mid, y2), kx, ly, mid, 2 * ky + 1));
        }
        if (y2 > mid) {
            ans = op(ans, get_y(std::max(mid, y1), y2, kx, mid, ry, 2 * ky + 2));
        }
        return ans;
    }
public:
    SegTree2D(const std::vector<std::vector<T>>& v, const std::function<T(T, T)>& op, const T& nil) : op(op), nil(nil) {
        int n = v.size(), m = v[0].size();
        while (x_sz < n) {
            x_sz <<= 1;
        }
        while (y_sz < m) {
            y_sz <<= 1;
        }
        tree.assign(2 * x_sz - 1, std::vector<T>(2 * y_sz - 1, nil));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                tree[x_sz - 1 + i][y_sz - 1 + j] = v[i][j];
            }
            for (int j = y_sz - 2; j >= 0; --j) {
                tree[x_sz - 1 + i][j] = op(tree[x_sz - 1 + i][2 * j + 1], tree[x_sz - 1 + i][2 * j + 2]);
            }
        }
        for (int i = x_sz - 2; i >= 0; --i) {
            for (int j = 0; j < y_sz - 1 + m; ++j) {
                tree[i][j] = op(tree[2 * i + 1][j], tree[2 * i + 2][j]);
            }
        }
    }
    void set_value(T val, int x, int y, int lx = 0, int rx = -1, int kx = 0) {
        if (rx == -1) {
            rx = x_sz;
        }
        if (lx + 1 == rx) {
            set_y(val, y, kx);
            return;
        }
        int mid = (lx + rx) / 2;
        if (x < mid) {
            set_value(val, x, y, lx, mid, 2 * kx + 1);
        } else {
            set_value(val, x, y, mid, rx, 2 * kx + 2);
        }
        set_y(op(tree[2 * kx + 1][y_sz - 1 + y], tree[2 * kx + 2][y_sz - 1 + y]), y, kx);
    }
    T get_op(int x1, int x2, int y1, int y2, int lx = 0, int rx = -1, int kx = 0) const {
        if (rx == -1) {
            rx = x_sz;
        }
        if (lx == x1 && rx == x2) {
            return get_y(y1, y2, kx);
        }
        int mid = (lx + rx) / 2;
        T ans = nil;
        if (x1 < mid) {
            ans = op(ans, get_op(x1, std::min(mid, x2), y1, y2, lx, mid, 2 * kx + 1));
        }
        if (x2 > mid) {
            ans = op(ans, get_op(std::max(mid, x1), x2, y1, y2, mid, rx, 2 * kx + 2));
        }
        return ans;
    }
};

int main() {
    return 0;
}
