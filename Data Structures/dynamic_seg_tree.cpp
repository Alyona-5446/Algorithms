#include <iostream>
#include <vector>

class DynamicSegTree {
private:
    struct Node;
    using Ptr = Node*;
    struct Node {
        Ptr left, right;
        long long s;
        Node(long long val) : s(val) {}
        Node(Ptr left, Ptr right) : left(left), right(right), s(left->s + right->s) {}
    };
    static Ptr build(int l, int r, const std::vector<long long>& v) {
        if (l + 1 == r) {
            return new Node(v[l]);
        }
        int mid = (l + r) / 2;
        return new Node(build(l, mid, v), build(mid, r, v));
    }
    static Ptr set_value(long long val, int idx, int l, int r, Ptr x) {
        if (l + 1 == r) {
            return new Node(val);
        }
        int mid = (l + r) / 2;
        if (idx < mid) {
            return new Node(set_value(val, idx, l, mid, x->left), x->right);
        } else {
            return new Node(x->left, set_value(val, idx, mid, r, x->right));
        }
    }
    static long long get(int left, int right, int l, int r, const Ptr x) {
        if (l == left && r == right) {
            return x->s;
        }
        int mid = (l + r) / 2;
        long long ans = 0;
        if (left < mid) {
            ans += get(left, std::min(mid, right), l, mid, x->left);
        }
        if (right > mid) {
            ans += get(std::max(mid, left), right, mid, r, x->right);
        }
        return ans;
    }
    std::vector<Ptr> history;
    int sz;
public:
    DynamicSegTree(const std::vector<long long>& v) : sz(v.size()) {
        history.push_back(build(0, sz, v));
    }
    long long get_sum(int k, int left, int right) {
        return get(left, right, 0, sz, history[k]);
    }
    void set_value(int k, long long val, int idx) {
        history[k] = set_value(val, idx, 0, sz, history[k]);
    }
    void persist(int k) {
        history.push_back(history[k]);
    }
    void roll_back() {
        history.pop_back();
    }
    void clear() {
        history.clear();
    }
};

int main() {
    return 0;
}
