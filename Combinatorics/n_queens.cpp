#include <cmath>
#include <ctime>
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

bool check(std::vector<int>& queens) {
    int x = queens.size() - 1, y = queens.back();
    for (int i = 0; i < x; ++i) {
        if (queens[i] == y || std::abs(y - queens[i]) == x - i) {
            return false;
        }
    }
    return true;
}

bool backtracking(int n, std::vector<int>& queens) {
    if (queens.size() == n) {
        return true;
    }
    for (int i = 0; i < n; ++i) {
        queens.push_back(i);
        if (check(queens) && backtracking(n, queens)) {
            return true;
        }
        queens.pop_back();
    }
    return false;
}

int randint(int a, int b) {
    return a + rand() / (RAND_MAX + 1.) * (b - a);
}

bool toss_coin(double prob) {
    return prob > rand() / (RAND_MAX + 1.);
}

void random_permutation(std::vector<int>& p) {
    int n = p.size();
    for (int i = 0; i < n; ++i) {
        p[i] = i;
    }
    for (int i = 0; i < n - 1; ++i) {
        int j = randint(i, n);
        std::swap(p[i], p[j]);
    }
}

int entropy(std::vector<int>& p) {
    int n = p.size();
    std::vector<int> diag(4 * n - 2);
    for (int i = 0; i < n; ++i) {
        ++diag[i - p[i] + n - 1];
        ++diag[i + p[i] + 2 * n - 1];
    }
    int ent = 0;
    for (int i = 0; i < 4 * n - 2; ++i) {
        ent += diag[i] * (diag[i] - 1) / 2;
    }
    return ent;
}

bool simulated_annealing(std::vector<int>& p) {
    constexpr int MX = 30;
    constexpr double T_0 = 1, T_MIN = 1e-6, K = 0.9999;
    int n = p.size();
    srand(time(0));
    for (int i = 0; i < MX; ++i) {
        random_permutation(p);
        int ent = entropy(p);
        for (double t = T_0; ent && t >= T_MIN; t *= K) {
            int idx1 = randint(0, n), idx2 = randint(0, n);
            if (idx1 != idx2) {
                std::swap(p[idx1], p[idx2]);
                int new_ent = entropy(p);
                if (new_ent < ent || toss_coin(std::exp((ent - new_ent) / t))) {
                    ent = new_ent;
                } else {
                    std::swap(p[idx1], p[idx2]);
                }
            }
        }
        if (!ent) {
            return true;
        }
    }
    return false;
}

int main() {
    int n;
    std::cin >> n;
    std::vector<int> p(n);
    for (int i = 1; i < n; ++i) {
        p[i] = i;
    }
    for (; entropy(p) && narajana(p););
    if (!entropy(p)) {
        for (auto q : p) {
            std::cout << q << ' ';
        }
    } else {
        std::cout << "No solutions";
    }
    std::cout << '\n';
    return 0;
}
