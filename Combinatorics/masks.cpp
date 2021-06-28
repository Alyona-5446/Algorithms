#include <iostream>

auto to_bin(int mask, int n) {
    std::string s;
    while (n--) {
        s += '0' + ((mask >> n) & 1);
    }
    return s;
}

int to_num(std::string& bin) {
    int n = 0;
    for (auto bit : bin) {
        n = (n << 1) | (bit - '0');
    }
    return n;
}        

void masks(int n) {
    for (int mask = 0; mask < (1 << n); ++mask) {
        std::cout << to_bin(mask, n) << '\n';
    }
}

void submasks(int n) {
    for (int mask = 0; mask < (1 << n); ++mask) {
        for (int submask = mask; submask; submask = (submask - 1) & mask) {
            std::cout << to_bin(mask, n) << ": " << to_bin(submask, n) << '\n';
        }
        std::cout << to_bin(mask, n) << ": " << to_bin(0, n) << '\n';
    }
}

int main() {
    return 0;
}
