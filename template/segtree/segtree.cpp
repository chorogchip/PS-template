#include <bits/stdc++.h>
using namespace std;

struct SegTree {
    int n;
    vector<long long> tree;

    SegTree() {}
    SegTree(int n) { init(n); }
    SegTree(const vector<long long>& a) { init(a); }

    void init(int n_) {
        n = n_;
        tree.assign(4 * n + 4, 0);  // fix: identitical
    }

    void init(const vector<long long>& a) {
        n = (int)a.size() - 1;
        tree.assign(4 * n + 4, 0);
        build(1, 1, n, a);
    }

    long long merge(long long a, long long b) {
        // fix: custom op
        return a + b;
    }

    long long identity() {
        // fix: identity
        // sum -> 0
        // min -> INF
        // max -> -INF
        return 0;
    }

    void build(int node, int s, int e, const vector<long long>& a) {
        if (s == e) {
            tree[node] = a[s];
            return;
        }
        int mid = (s + e) >> 1;
        build(node << 1, s, mid, a);
        build(node << 1 | 1, mid + 1, e, a);
        tree[node] = merge(tree[node << 1], tree[node << 1 | 1]);
    }

    void update(int node, int s, int e, int idx, long long val) {
        if (idx < s || e < idx) return;
        if (s == e) {
            // fix: update
            // tree[node] = val / tree[node] += val;
            tree[node] = val;
            return;
        }
        int mid = (s + e) >> 1;
        update(node << 1, s, mid, idx, val);
        update(node << 1 | 1, mid + 1, e, idx, val);
        tree[node] = merge(tree[node << 1], tree[node << 1 | 1]);
    }

    long long query(int node, int s, int e, int l, int r) {
        if (r < s || e < l) return identity();
        if (l <= s && e <= r) return tree[node];
        int mid = (s + e) >> 1;
        return merge(
            query(node << 1, s, mid, l, r),
            query(node << 1 | 1, mid + 1, e, l, r)
        );
    }

    void update(int idx, long long val) {
        update(1, 1, n, idx, val);
    }

    long long query(int l, int r) {
        return query(1, 1, n, l, r);
    }
};
