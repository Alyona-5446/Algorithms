#include <functional>
#include <iostream>
#include <stack>
#include <vector>

template<typename T>
class ExtrStack {
private:
    std::stack<std::pair<T, T>> st;
    std::function<T(const T&, const T&)> extr;
public:
    ExtrStack(const std::function<T(const T&, const T&)>& extr) : extr(extr) {}
    bool empty() const {
        return !st.size();
    }
    void push(T n) {
        if (empty()) {
            st.emplace(n, n);
        } else {
            st.emplace(n, extr(n, st.top().second));
        }
    }
    void pop() {
        st.pop();
    }
    T top() const {
        return st.top().first;
    }
    T get_extr() const {
        return st.top().second;
    }
};

template<typename T>
class ExtrQueue {
private:
    ExtrStack<T> st1, st2;
    std::function<T(const T&, const T&)> extr;
public:
    ExtrQueue(const std::function<T(const T&, const T&)>& extr) : st1(extr), st2(extr), extr(extr) {}
    void push_back(T n) {
        st1.push(n);
    }
    void pop_front() {
        if (st2.empty()) {
            while (!st1.empty()) {
                st2.push(st1.top());
                st1.pop();
            }
        }
        st2.pop();
    }
    T get_extr() const {
        if (st1.empty()) {
            return st2.get_extr();
        }
        if (st2.empty()) {
            return st1.get_extr();
        }
        return extr(st1.get_extr(), st2.get_extr());
    }
};

int main() {
    return 0;
}
