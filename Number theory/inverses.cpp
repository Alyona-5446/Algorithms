#include <iostream>
#include <vector>

int binpow(int a, int n) {
    if (!n) {
        return 1;
    }
    if (n == 1) {
        return a;
    }
    int sq = binpow(a, n / 2);
    sq *= sq;
    if (n & 1) {
        sq *= a;
    }
    return sq;
}

int phi(int n) {
    int ans = n;
    if (!(n & 1)) {
        while (!(n & 1)) {
            n >>= 1;
        }
        ans >>= 1;
    }
    for (int i = 0; i * i <= n; i += 2) {
        if (!(n % i)) {
            while (!(n % i)) {
                n /= i;
            }
            ans -= ans / i;
        }
    }
    if (n > 1) {
        ans -= ans / n;
    }
    return ans;
}

int expanded_gcd(int a, int b, int& x, int& y) {
    if (!b) {
        x = 1;
        y = 0;
        return a;
    }
    int x1, y1, g = expanded_gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

int prime_inverse(int a, int p) {
    return binpow(a, p - 2);
}

int coprime_gcd_inverse(int a, int M) {
    int x, y;
    expanded_gcd(a, M, x, y);
    return (x % M + M) % M;
}

int inverse(int a, int M) {
    return binpow(a, phi(M) - 1);
}

auto all_inverses(int p) {
    std::vector<int> inv(p);
    inv[1] = 1;
    for (int i = 2; i < p; ++i) {
        inv[i] = (p - ((p / i) * inv[p % i]) % p) % p;
    }
    return inv;
}

int main() {
    return 0;
}
