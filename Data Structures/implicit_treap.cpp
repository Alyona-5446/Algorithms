#include <iostream>
#include <vector>

constexpr int INF = 1000000001;

int randint() {
    return (rand() << 15) ^ rand();
}

class ImplicitTreap {
    struct Node;
    using Ptr = Node*;
    struct Node {
        int cnt, pr, val, mn;
        bool rev;
        Ptr left, right;
        Node(int val) : cnt(1), pr(randint()), val(val), mn(val), rev(false), left(nullptr), right(nullptr) {}
    };
    static int get_cnt(Ptr tree) {
        return tree ? tree->cnt : 0;
    }
    static void upd_cnt(Ptr& tree) {
        tree->cnt = get_cnt(tree->left) + get_cnt(tree->right) + 1;
    }
    static int get_min(Ptr tree) {
        return tree ? tree->mn : INF;
    }
    static void upd_min(Ptr& tree) {
        tree->mn = std::min(tree->val, std::min(get_min(tree->left), get_min(tree->right)));
    }
    static void push(Ptr& tree) {
        if (tree->rev) {
            std::swap(tree->left, tree->right);
            if (tree->left) {
                tree->left->rev ^= 1;
            }
            if (tree->right) {
                tree->right->rev ^= 1;
            }
            tree->rev = false;
        }
    }
    static void split(int x, Ptr tree, Ptr& left, Ptr& right) {
        if (!tree) {
            left = right = nullptr;
            return;
        }
        push(tree);
        int k = get_cnt(tree->left);
        if (x > k) {
            split(x - k - 1, tree->right, tree->right, right);
            left = tree;
        } else {
            split(x, tree->left, left, tree->left);
            right = tree;
        }
        upd_cnt(tree), upd_min(tree);
    }
    static void merge(Ptr& tree, Ptr left, Ptr right) {
        if (!left || !right) {
            tree = left ? left : right;
            return;
        }
        push(left), push(right);
        if (left->pr > right->pr) {
            merge(left->right, left->right, right);
            tree = left;
        } else {
            merge(right->left, left, right->left);
            tree = right;
        }
        upd_cnt(tree), upd_min(tree);
    }
    static void traverse(Ptr tree) {
        if (tree) {
            push(tree);
            traverse(tree->left);
            std::cout << tree->val << ' ';
            traverse(tree->right);
        }
    }
    Ptr root = nullptr;
public:
    ImplicitTreap() = default;
    ImplicitTreap(const std::vector<int>& v) {
        int n = v.size();
        for (int i = 0; i < n; ++i) {
            insert(i, v[i]);
        }
    }
    void insert(int pos, int elem) {
        Ptr left, right;
        split(pos, root, left, right);
        merge(root, left, new Node(elem));
        merge(root, root, right);
    }
    void erase(int pos) {
        Ptr left, node, right;
        split(pos, root, left, right);
        split(1, right, node, right);
        merge(root, left, right);
    }
    int get_min(int l, int r) {
        Ptr left, seg, right;
        split(l, root, left, right);
        split(r - l + 1, right, seg, right);
        int mn = get_min(seg);
        merge(root, left, seg);
        merge(root, root, right);
        return mn;
    }
    void reverse(int l, int r) {
        Ptr left, seg, right;
        split(l, root, left, right);
        split(r - l + 1, right, seg, right);
        seg->rev ^= 1;
        merge(root, left, seg);
        merge(root, root, right);
    }
    void to_front(int l, int r) {
        Ptr left, seg, right;
        split(l, root, left, right);
        split(r - l + 1, right, seg, right);
        merge(root, seg, left);
        merge(root, root, right);
    }
    void to_back(int l, int r) {
        Ptr left, seg, right;
        split(l, root, left, right);
        split(l - r + 1, right, seg, right);
        merge(root, left, right);
        merge(root, root, seg);
    }
    void traverse() const {
        traverse(root);
        std::cout << '\n';
    }
};

int main() {
    return 0;
}
