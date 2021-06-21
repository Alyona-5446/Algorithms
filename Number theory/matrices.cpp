#include <iostream>
#include <vector>

using Matrix = std::vector<std::vector<int>>;

Matrix mult(const Matrix& mt1, const Matrix& mt2) {
    int n = mt1.size(), l = mt1[0].size(), m = mt2[0].size();
    Matrix mt3(n, std::vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            for (int k = 0; k < l; ++k) {
                mt3[i][j] += mt1[i][k] * mt2[k][j];
            }
        }
    }
    return mt3;
}

Matrix binpow(const Matrix& mt, int n) {
    if (!n) {
        int l = mt.size();
        Matrix mt1(l, std::vector<int>(l));
        for (int i = 0; i < l; ++i) {
            mt1[i][i] = 1;
        }
        return mt1;
    }
    if (n == 1) {
        return mt;
    }
    Matrix sq = binpow(mt, n / 2);
    sq = mult(sq, sq);
    if (n & 1) {
        sq = mult(sq, mt);
    }
    return sq;
}

int main() {
    int n;
    std::cin >> n;
    Matrix mt = {{0, 1}, {1, 1}}, f = {{0}, {1}};
    std::cout << mult(binpow(mt, n), f)[0][0];
    return 0;
}
