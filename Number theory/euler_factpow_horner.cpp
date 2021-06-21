#include <iostream>
#include <vector>

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

int factpow(int n, int p) {
    int ans = 0;
    while (n) {
        n /= p;
        ans += n;
    }
    return ans;
}

int horner(int n, std::vector<int>& p) {
    int ans = p[0];
    for (int i = 1; i < p.size(); ++i) {
        ans = ans * n + p[i];
    }
    return ans;
}

int main() {
    return 0;
}
