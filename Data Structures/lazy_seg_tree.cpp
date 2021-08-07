#include <iostream>
#include <vector>

class LazySegTree {
private:
    std::vector<long long> tree, add, ass;
    long long nil;
    int sz = 1;
    long long get(int x, int l, int r) {
        return (ass[x] != nil ? ass[x] * (r - l) : tree[x]) + add[x] * (r - l);
    }
    void push(int x) {
        if (ass[x] != nil) {
            ass[2 * x + 1] = ass[2 * x + 2] = ass[x];
            add[2 * x + 2] = add[2 * x + 1] = 0;
            ass[x] = nil;
        }
        if (add[x]) {
            add[2 * x + 1] += add[x];
            add[2 * x + 2] += add[x];
            add[x] = 0;
        }
    }
public:
    LazySegTree(const std::vector<long long>& v, long long nil) : nil(nil) {
        int n = v.size();
        while (sz < n) {
            sz <<= 1;
        }
        tree.assign(2 * sz - 1, 0);
        add.assign(2 * sz - 1, 0);
        ass.assign(2 * sz - 1, nil);
        for (int i = 0; i < n; ++i) {
            tree[sz - 1 + i] = v[i];
        }
        for (int i = sz - 2; i >= 0; --i) {
            tree[i] = tree[2 * i + 1] + tree[2 * i + 2];
        }
    }
    void assign(long long val, int left, int right, int l = 0, int r = -1, int x = 0) {
        if (r == -1) {
            r = sz;
        }
        if (l == left && r == right) {
            ass[x] = val;
            add[x] = 0;
            return;
        }
        push(x);
        int mid = (l + r) / 2;
        if (left < mid) {
            assign(val, left, std::min(mid, right), l, mid, 2 * x + 1);
        }
        if (right > mid) {
            assign(val, std::max(mid, left), right, mid, r, 2 * x + 2);
        }
        tree[x] = get(2 * x + 1, l, mid) + get(2 * x + 2, mid, r);
    }
    void modify(long long delta, int left, int right, int l = 0, int r = -1, int x = 0) {
        if (r == -1) {
            r = sz;
        }
        if (l == left && r == right) {
            add[x] += delta;
            return;
        }
        push(x);
        int mid = (l + r) / 2;
        if (left < mid) {
            modify(delta, left, std::min(mid, right), l, mid, 2 * x + 1);
        }
        if (right > mid) {
            modify(delta, std::max(mid, left), right, mid, r, 2 * x + 2);
        }
        tree[x] = get(2 * x + 1, l, mid) + get(2 * x + 2, mid, r);
    }
    long long get_sum(int left, int right, int l = 0, int r = -1, int x = 0) {
        if (r == -1) {
            r = sz;
        }
        if (l == left && r == right) {
            return get(x, l, r);
        }
        push(x);
        int mid = (l + r) / 2;
        long long sum = 0;
        if (left < mid) {
            sum += get_sum(left, std::min(mid, right), l, mid, 2 * x + 1);
        }
        if (right > mid) {
            sum += get_sum(std::max(mid, left), right, mid, r, 2 * x + 2);
        }
        tree[x] = get(2 * x + 1, l, mid) + get(2 * x + 2, mid, r);
        return sum;
    }
};

int main() {
    return 0;
}
