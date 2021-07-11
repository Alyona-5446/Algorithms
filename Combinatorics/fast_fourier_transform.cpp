#include <cmath>
#include <complex>
#include <iostream>
#include <vector>

using Point = std::complex<double>;

constexpr double PI = 3.141592653589793238462643;

void fft(std::vector<Point>& poly, bool inv = false) {
    int n = poly.size();
    for (int i = 1, j = 0; i < n - 1; ++i) {
        int bit = n >> 1;
        while (j & bit) {
            j ^= bit;
            bit >>= 1;
        }
        j |= bit;
        if (i < j) {
            std::swap(poly[i], poly[j]);
        }
    }
    for (int l = 2; l <= n; l <<= 1) {
        double phi = (inv ? -2 : 2) * PI / l;
        Point z1 = {std::cos(phi), std::sin(phi)};
        for (int i = 0; i < n; i += l) {
            Point z = {1, 0};
            for (int j = 0; j < l / 2; ++j) {
                Point u = poly[i + j], v = poly[i + j + l / 2] * z;
                poly[i + j] = u + v;
                poly[i + j + l / 2] = u - v;
                z *= z1;
            }
        }
    }
    if (inv) {
        for (int i = 0; i < n; ++i) {
            poly[i] /= n;
        }
    }
}

auto multiply(const std::vector<int>& p1, const std::vector<int>& p2) {
    int mx = std::max(p1.size(), p2.size()), n = 1;
    while (n < (mx << 1)) {
        n <<= 1;
    }
    std::vector<Point> fp1(p1.begin(), p1.end()), fp2(p2.begin(), p2.end());
    fp1.resize(n);
    fp2.resize(n);
    fft(fp1);
    fft(fp2);
    for (int i = 0; i < n; ++i) {
        fp1[i] *= fp2[i];
    }
    fft(fp1, true);
    std::vector<long long> ans(n);
    for (int i = 0; i < n; ++i) {
        ans[i] = fp1[i].real() + 0.5;
    }
    return ans;
}

int main() {
    return 0;
}
