#include <iostream>
#include <stack>
#include <vector>

int C(int n, int k) {
    if ((k < 0) || (k > n)) {
        return 0;
    }
    k = std::min(k, n - k);
    int c = 1;
    for (int i = 1; i <= k; ++k) {
        c = c * (n - k + i) / i;
    }
    return c;
}

auto C_triangle(int n, int k) {
    std::vector<std::vector<int>> C(n + 1, std::vector<int>(k + 1));
    for (int i = 0; i <= n; ++i) {
        C[i][0] = 1;
    }
    for (int i = 1; i <= k; ++i) {
        C[i][i] = 1;
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j < std::min(i, k + 1); ++j) {
            C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
        }
    }
    return C;
}

int catalan(int n) {
    return C(2 * n, n) / (n + 1);
}

int C_free_catalan(int n) {
    int c = 1;
    for (int i = 0; i < n; ++i) {
        c = c * (4 * i + 2) / (i + 2);
    }
    return c;
}

auto dp_catalan(int n) {
    std::vector<int> C(n + 1);
    C[0] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < i; ++j) {
            C[i] += C[j] * C[i - 1 - j];
        }
    }
    return C;
}

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

int count_bbs(int n, int k) {
    return catalan(n) * binpow(k, n);
}

bool is_bbs(std::string& s) {
    std::stack<char> st;
    for (auto c : s) {
        switch (c) {
        case '(':
        case '[':
        case '{':
        case '<':
            st.push(c);
            break;
        case ')':
            if (st.empty() || st.top() != '(') {
                return false;
            }
            st.pop();
            break;
        case ']':
            if (st.empty() || st.top() != '[') {
                return false;
            }
            st.pop();
            break;
        case '}':
            if (st.empty() || st.top() != '{') {
                return false;
            }
            st.pop();
            break;
        case '>':
            if (st.empty() || st.top() != '<') {
                return false;
            }
            st.pop();
            break;
        default:
            break;
        }
    }
    return st.empty();
}

void generate_bbs(int n) {
    std::string s;
    for (int i = 0; i < (1 << (2 * n)); ++i) {
        s.clear();
        int balance = 0;
        for (int j = 0; j < 2 * n; ++j) {
            bool bit = (i >> j) & 1;
            bit ? --balance : ++balance;
            if (balance < 0) {
                break;
            }
            s += (bit ? ')' : '(');
        }
        if (!balance) {
            std::cout << s << '\n';
        }
    }
}

bool next_bbs(std::string& s) {
    int n = s.size(), balance = 0;
    for (int i = n - 1; i >= 0; --i) {
        if (s[i] == '(') {
            --balance;
            if (balance > 0) {
                --balance;
                int open = (n - i - 1 - balance) / 2, close = n - i - 1 - open;
                s = s.substr(0, i) + ')' + std::string(open, '(') + std::string(close, ')');
                return true;
            }
        } else {
            ++balance;
        }
    }
    return false;
}

int bbs_index(std::string& s) {
    int n = s.size() / 2, idx = 0;
    std::vector<std::vector<int>> d(2 * n + 1, std::vector<int>(2 * n + 1));
    for (int i = 0; i <= 2 * n; ++i) {
        d[i][i] = 1;
    }
    for (int i = 2; i <= 2 * n; ++i) {
        d[i][0] = d[i - 1][1];
        for (int j = 1 + !(i & 1); j < i; j += 2) {
            d[i][j] = d[i - 1][j - 1] + d[i - 1][j + 1];
        }
    }
    for (int i = 0, balance = 0; i < 2 * n; ++i) {
        if (s[i] == '(') {
             ++balance;
        } else {
            idx += d[2 * n - i - 1][balance + 1];
            --balance;
        }
    }
    return ++idx;
}

auto kth_bbs(int n, int k) { //1-indexed
    std::vector<std::vector<int>> d(2 * n + 1, std::vector<int>(2 * n + 1));
    for (int i = 0; i <= 2 * n; ++i) {
        d[i][i] = 1;
    }
    for (int i = 2; i <= 2 * n; ++i) {
        d[i][0] = d[i - 1][1];
        for (int j = 1 + !(i & 1); j < i; j += 2) {
            d[i][j] = d[i - 1][j - 1] + d[i - 1][j + 1];
        }
    }
    std::string bbs;
    for (int i = 0, balance = 0; i < 2 * n; ++i) {
        if (d[2 * n - i - 1][balance + 1] >= k) {
            bbs += '(';
            ++balance;
        } else {
            bbs += ')';
            k -= d[2 * n - i - 1][balance + 1];
            --balance;
        }
    }
    return bbs;
}

int main() {
    return 0;
}
