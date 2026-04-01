#include <bits/stdc++.h>
using namespace std;

struct LazySegTree {
    int n;
    vector<long long> tree, lazy;

    LazySegTree() {}
    LazySegTree(int n) { init(n); }
    LazySegTree(const vector<long long>& a) { init(a); }

    void init(int n_) {
        n = n_;
        tree.assign(4 * n + 4, 0);
        lazy.assign(4 * n + 4, 0);
    }

    void init(const vector<long long>& a) {
        n = (int)a.size() - 1; // 1-indexed
        tree.assign(4 * n + 4, 0);
        lazy.assign(4 * n + 4, 0);
        build(1, 1, n, a);
    }

    void build(int node, int s, int e, const vector<long long>& a) {
        if (s == e) {
            tree[node] = a[s];
            return;
        }
        int mid = (s + e) >> 1;
        build(node << 1, s, mid, a);
        build(node << 1 | 1, mid + 1, e, a);
        tree[node] = tree[node << 1] + tree[node << 1 | 1];
    }

    void apply(int node, int s, int e, long long val) {
        // TODO: lazy 적용 방식 수정
        // 현재: 구간 덧셈 + 구간합
        tree[node] += (e - s + 1) * val;
        lazy[node] += val;
    }

    void push(int node, int s, int e) {
        if (lazy[node] == 0) return;
        if (s != e) {
            int mid = (s + e) >> 1;
            apply(node << 1, s, mid, lazy[node]);
            apply(node << 1 | 1, mid + 1, e, lazy[node]);
        }
        lazy[node] = 0;
    }

    void update(int node, int s, int e, int l, int r, long long val) {
        if (r < s || e < l) return;
        if (l <= s && e <= r) {
            apply(node, s, e, val);
            return;
        }
        push(node, s, e);
        int mid = (s + e) >> 1;
        update(node << 1, s, mid, l, r, val);
        update(node << 1 | 1, mid + 1, e, l, r, val);
        tree[node] = tree[node << 1] + tree[node << 1 | 1];
    }

    long long query(int node, int s, int e, int l, int r) {
        if (r < s || e < l) return 0; // TODO: 항등원 수정
        if (l <= s && e <= r) return tree[node];
        push(node, s, e);
        int mid = (s + e) >> 1;
        return query(node << 1, s, mid, l, r)
             + query(node << 1 | 1, mid + 1, e, l, r);
    }

    void update(int l, int r, long long val) {
        update(1, 1, n, l, r, val);
    }

    long long query(int l, int r) {
        return query(1, 1, n, l, r);
    }
};