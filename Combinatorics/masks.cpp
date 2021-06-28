#include <iostream>

auto bin(int mask, int n) {
    std::string s;
    while (n--) {
        s += '0' + ((mask >> n) & 1);
    }
    return s;
}

void masks(int n) {
    for (int mask = 0; mask < (1 << n); ++mask) {
        std::cout << bin(mask, n) << '\n';
    }
}

void submasks(int n) {
    for (int mask = 0; mask < (1 << n); ++mask) {
        for (int submask = mask; submask; submask = (submask - 1) & mask) {
            std::cout << bin(mask, n) << ": " << bin(submask, n) << '\n';
        }
        std::cout << bin(mask, n) << ": " << bin(0, n) << '\n';
    }
}

int main() {
    return 0;
}
