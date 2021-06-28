#include <iostream>
#include <vector>

bool narajana(std::vector<int>& p) {
    int n = p.size(), j, k;
    for (j = n - 1; j && p[j] <= p[j - 1]; --j);
    if (!j) {
        return false;
    }
    --j;
    for (k = n - 1; p[k] <= p[j]; --k);
    std::swap(p[j], p[k]);
    for (int idx1 = j + 1, idx2 = n - 1; idx1 < idx2; ++idx1, --idx2) {
        std::swap(p[idx1], p[idx2]);
    }
    return true;
}

int main() {
    return 0;
}
