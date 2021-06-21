#include <iostream>

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

int modbinpow(int a, int n, int M) {
    if (!n) {
        return 1;
    }
    if (n == 1) {
        return a % M;
    }
    int sq = modbinpow(a, n / 2, M);
    sq = (sq * 1LL * sq) % M;
    if (n & 1) {
        sq = (sq * 1LL * a) % M;
    }
    return sq;
}

long long modmult(long long a, long long b, long long M) { // if (a < b) std::swap(a, b)
    if (!b) {
        return 0;
    }
    if (b == 1) {
        return a % M;
    }
    long long ans = modmult(a, b / 2, M);
    ans = (2 * ans) % M;
    if (b & 1) {
        ans = (ans + a) % M;
    }
    return ans;
}

int main() {
     return 0;
}
