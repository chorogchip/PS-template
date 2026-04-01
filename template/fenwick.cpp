#include <bits/stdc++.h>
using namespace std;

struct Fenwick {
    int n;
    vector<long long> tree;
    Fenwick() {}
    Fenwick(int n) { init(n); }
    void init(int n_) {
        n = n_;
        tree.assign(n + 1, 0);
    }
    void add(int i, long long v) {
        for (; i <= n; i += i & -i) tree[i] += v;
    }
    long long sum(int i) {
        long long ret = 0;
        for (; i > 0; i -= i & -i) ret += tree[i];
        return ret;
    }
    long long query(int l, int r) {
        return sum(r) - sum(l - 1);
    }
};