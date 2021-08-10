#include <iostream>
#include <vector>

int randint() {
    return (rand() << 15) ^ rand();
}

class Rope {
private:
    struct Node;
    using Ptr = Node*;
    struct Node {
        int cnt, pr;
        char c;
        bool rev;
        Ptr left, right;
        Node(char c) : cnt(1), pr(randint()), c(c), rev(false), left(nullptr), right(nullptr) {}
    };
    static int get_cnt(Ptr tree) {
        return tree ? tree->cnt : 0;
    }
    static void upd_cnt(Ptr& tree) {
        tree->cnt = get_cnt(tree->left) + get_cnt(tree->right) + 1;
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
        upd_cnt(tree);
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
        upd_cnt(tree);
    }
    static void traverse(Ptr tree) {
        if (tree) {
            push(tree);
            traverse(tree->left);
            std::cout << tree->c;
            traverse(tree->right);
        }
    }
    Ptr root = nullptr;
public:
    Rope() = default;
    Rope(const std::string& s) {
        int n = s.size();
        for (int i = 0; i < n; ++i) {
            insert(i, s[i]);
        }
    }
    void insert(int pos, char elem) {
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
        split(r - l + 1, right, seg, right);
        merge(root, left, right);
        merge(root, root, seg);
    }
    void reverse(int l, int r) {
        Ptr left, seg, right;
        split(l, root, left, right);
        split(r - l + 1, right, seg, right);
        seg->rev ^= 1;
        merge(root, left, seg);
        merge(root, root, right);
    }
    void traverse() const {
        traverse(root);
        std::cout << '\n';
    }
};

int main() {
    return 0;
}
