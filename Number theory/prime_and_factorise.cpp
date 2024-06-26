#include <iostream>
#include <vector>
#include <algorithm>

bool is_prime(int n) {
    if (n == 2) {
        return true;
    }
    if (!(n & 1)) {
        return false;
    }
    for (int i = 3; i * i <= n; i += 2) {
        if (!(n % i)) {
            return false;
        }
    }
    return true;
}

auto factorise(int n) {
    std::vector<std::pair<int, int>> factors;
    if (!(n & 1)) {
        int p = 0;
        do {
            n >>= 1;
            ++p;
        } while (!(n & 1));
        factors.emplace_back(2, p);
    }
    for (int i = 3; i * i <= n; i += 2) {
        if (!(n % i)) {
            int p = 0;
            do {
                n /= i;
                ++p;
            } while (!(n % i));
            factors.emplace_back(i, p);
        }
    }
    if (n > 1) {
        factors.emplace_back(n, 1);
    }
    return factors;
}

auto all_divs(int n) {
    std::vector<int> divs;
    int i;
    for (i = 1; i * i < n; ++i) {
        if (!(n % i)) {
            divs.push_back(i);
            divs.push_back(n / i);
        }
    }
    if (i * i == n) {
        divs.push_back(i);
    }
    std::sort(divs.begin(), divs.end());
    return divs;
}

int main() {
    return 0;
}
