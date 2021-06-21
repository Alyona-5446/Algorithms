#include <iostream>
#include <vector>

auto sieve(int n) {
    std::vector<bool> prime(n + 1);
    prime[2] = true;
    for (int i = 3; i <= n; i += 2) {
        prime[i] = true;
    }
    for (int i = 3; i * i <= n; i += 2) {
        if (prime[i]) {
            for (int j = i * i; j <= n; j += i) {
                prime[j] = false;
            }
        }
    }
    return prime;
}

auto linear_sieve(int n) {
    std::vector<int> lp(n + 1), primes;
    for (int i = 2; i <= n; ++i) {
        if (!lp[i]) {
            lp[i] = i;
            primes.push_back(i);
        }
        for (auto p : primes) {
            if (p > lp[i] || i * p > n) {
                break;
            }
            lp[i * p] = p;
        }
    }
    return lp;
}

auto sieve_factorise(int n, std::vector<int>& lp) {
    std::vector<int> factors;
    while (lp[n]) {
        factors.push_back(lp[n]);
        n /= lp[n];
    }
    return factors;
}

int main() {
    return 0;
}
