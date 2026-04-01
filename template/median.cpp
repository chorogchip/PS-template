#include <bits/stdc++.h>
using namespace std;

template <class T>
struct RunningMedian {
    priority_queue<T> left; // max heap
    priority_queue<T, vector<T>, greater<T>> right; // min heap

    void add(const T& x) {
        if (left.empty() || x <= left.top()) left.push(x);
        else right.push(x);
        balance();
    }
    T median() const {
        return left.top();
    }
    int size() const {
        return (int)left.size() + (int)right.size();
    }
    bool empty() const {
        return size() == 0;
    }
private:
    void balance() {
        if (left.size() < right.size()) {
            left.push(right.top());
            right.pop();
        } else if (left.size() > right.size() + 1) {
            right.push(left.top());
            left.pop();
        }
    }
};