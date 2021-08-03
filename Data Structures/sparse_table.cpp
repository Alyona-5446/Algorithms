#include <functional>
#include <iostream>
#include <vector>

template<typename T>
class SparseTable {
private:
    std::vector<std::vector<T>> table;
    std::vector<int> log2;
    std::function<T(const T&, const T&)> op;
public:
    SparseTable(const std::vector<T>& v, const std::function<T(const T&, const T&)>& op) : op(op) {
        table.emplace_back(v);
        int n = v.size();
        log2.assign(n + 1, 0);
        for (int l = 1; (1 << l) <= n; ++l) {
            for (int i = (1 << l); i < std::min((1 << (l + 1)), n + 1); ++i) {
                log2[i] = l;
            }
            table.emplace_back(n - (1 << l) + 1);
            for (int i = 0; i <= n - (1 << l); ++i) {
                table[l][i] = op(table[l - 1][i], table[l - 1][i + (1 << (l - 1))]);
            }
        }
    }
    T get_op(int l, int r) {
        int log = log2[r - l + 1];
        return op(table[log][l], table[log][r - (1 << log) + 1]);
    }
};

int main() {
    return 0;
}
