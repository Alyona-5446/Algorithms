#include <iostream>
#include <vector>

constexpr int INF = 1'000'000'001;

int randint() {
    return (rand() << 15) ^ rand();
}

class Treap {
private:
    struct Node;
    using Ptr = Node*;
    struct Node {
        int k, pr;
        Ptr left, right;
        Node(int k, int pr = randint(), Ptr left = nullptr, Ptr right = nullptr) :
                k(k), pr(pr), left(left), right(right) {}
    };
    static void split(int x, Ptr tree, Ptr& left, Ptr& right) {
        if (!tree) {
            left = right = nullptr;
            return;
        }
        if (x < tree->k) {
            split(x, tree->left, left, tree->left);
            right = tree;
        } else {
            split(x, tree->right, tree->right, right);
            left = tree;
        }
    }
    static void merge(Ptr& tree, Ptr left, Ptr right) {
        if (!left || !right) {
            tree = (left ? left : right);
            return;
        }
        if (left->pr > right->pr) {
            merge(left->right, left->right, right);
            tree = left;
        } else {
            merge(right->left, left, right->left);
            tree = right;
        }
    }
    static bool insert(Ptr& tree, Ptr node) {
        if (!tree) {
            tree = node;
        } else if (node->pr == tree->pr) {
            return false;
        } else if (node->pr > tree->pr) {
            split(node->k, tree, node->left, node->right);
            tree = node;
        } else {
            return insert(node->k > tree->k ? tree->right : tree->left, node);
        }
        return true;
    }
    static void erase(Ptr& tree, int elem) {
        if (!tree) {
            return;
        }
        if (tree->k == elem) {
            merge(tree, tree->left, tree->right);
            return;
        }
        erase(elem > tree->k ? tree->right : tree->left, elem);
    }
    Ptr root = nullptr;
public:
    void insert(int elem) {
        Ptr node = new Node(elem);
        while (!insert(root, node)) {
            node->k = randint();
        }
    }
    void erase(int elem) {
        erase(root, elem);
    }
    int lower_bound(int elem) const {
        Ptr tree = root;
        int mn = INF;
        while (tree) {
            if (elem > tree->k) {
                tree = tree->right;
            } else {
                mn = std::min(mn, tree->k);
                tree = tree->left;
            }
        }
        return mn == INF ? -1 : mn;
    }
    Treap() = default;
    Treap(const std::vector<int>& v) {
        for (auto elem : v) {
            insert(elem);
        }
    }
};

int main() {
    return 0;
}
