#include <iostream>

int gcd(int a, int b) {
    if (a < b) {
        std::swap(a, b);
    }
    while (b) {
        a %= b;
        std::swap(a, b);
    }
    return a;
}

int lcm(int a, int b) {
    return a / gcd(a, b) * b;
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

int main() {
    int a, b, x, y;
    std::cin >> a >> b;
    int g = expanded_gcd(a, b, x, y);
    printf("(%d%+d*k, %d%+d*k)", x, b / g, y, -a / g);
    return 0;
}
