#include <iostream>
#include <vector>

int gray_code(int n) {
    return n ^ (n >> 1);
}

int gray_num(int code) {
    int n = 0;
    while (code) {
        n ^= code;
        code >>= 1;
    }
    return n;
}

int popcnt(int n) {
    int cnt = 0;
    while (n) {
        n &= n - 1;
        ++cnt;
    }
    return cnt;
}

bool next_combination(std::vector<int>& c, int n) {
    int k = c.size();
    for (int i = k - 1; i >= 0; --i) {
        if (c[i] < n - k + 1 + i) {
            ++c[i];
            for (int j = i + 1; j < k; ++j) {
                c[j] = c[j - 1] + 1;
            }
            return true;
        }
    }
    return false;
}

void gray_combinations(int n, int k) {
    for (int i = 0; i < (1 << n); ++i) {
        int code = gray_code(i);
        if (popcnt(code) == k) {
            for (int j = 0; j < n; ++j) {
                if (code & (1 << j)) {
                    std::cout << j + 1 << ' ';
                }
            }
            std::cout << '\n';
        }
    }
}

void recursive_combinations(std::vector<bool>& c, int k, int idx = 0, bool inv = false) {
    int n = c.size();
    if (k > n - idx) {
        return;
    }
    if (!k) {
        for (int i = 0; i < n; ++i) {
            if (c[i]) {
                std::cout << i + 1 << ' ';
            }
        }
        std::cout << '\n';
        return;
    }
    c[idx] = inv;
    recursive_combinations(c, k - inv, idx + 1, false);
    c[idx] = !inv;
    recursive_combinations(c, k - !inv, idx + 1, true);
}

int main() {
    return 0;
}
