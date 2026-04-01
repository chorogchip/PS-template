#include <bits/stdc++.h>
using namespace std;

struct SegTreeBeats {
    struct Node {
        long long sum;
        long long mx1, mx2;
        int mxcnt;
    };

    int n;
    vector<Node> tree;

    SegTreeBeats() {}
    SegTreeBeats(const vector<long long>& a) { init(a); }

    Node make_node(long long x) {
        return {x, x, (long long)-4e18, 1};
    }

    Node merge(Node a, Node b) {
        Node ret;
        ret.sum = a.sum + b.sum;

        if (a.mx1 > b.mx1) {
            ret.mx1 = a.mx1;
            ret.mxcnt = a.mxcnt;
            ret.mx2 = max(a.mx2, b.mx1);
        } else if (a.mx1 < b.mx1) {
            ret.mx1 = b.mx1;
            ret.mxcnt = b.mxcnt;
            ret.mx2 = max(a.mx1, b.mx2);
        } else {
            ret.mx1 = a.mx1;
            ret.mxcnt = a.mxcnt + b.mxcnt;
            ret.mx2 = max(a.mx2, b.mx2);
        }
        return ret;
    }

    void init(const vector<long long>& a) {
        n = (int)a.size() - 1; // 1-indexed
        tree.assign(4 * n + 4, {0, 0, 0, 0});
        build(1, 1, n, a);
    }

    void build(int node, int s, int e, const vector<long long>& a) {
        if (s == e) {
            tree[node] = make_node(a[s]);
            return;
        }
        int mid = (s + e) >> 1;
        build(node << 1, s, mid, a);
        build(node << 1 | 1, mid + 1, e, a);
        tree[node] = merge(tree[node << 1], tree[node << 1 | 1]);
    }

    void apply_chmin(int node, long long x) {
        if (tree[node].mx1 <= x) return;
        tree[node].sum -= (tree[node].mx1 - x) * tree[node].mxcnt;
        tree[node].mx1 = x;
    }

    void push(int node) {
        long long x = tree[node].mx1;
        if (tree[node << 1].mx1 > x) apply_chmin(node << 1, x);
        if (tree[node << 1 | 1].mx1 > x) apply_chmin(node << 1 | 1, x);
    }

    void range_chmin(int node, int s, int e, int l, int r, long long x) {
        if (r < s || e < l || tree[node].mx1 <= x) return;

        if (l <= s && e <= r && tree[node].mx2 < x) {
            apply_chmin(node, x);
            return;
        }

        if (s == e) return;

        push(node);
        int mid = (s + e) >> 1;
        range_chmin(node << 1, s, mid, l, r, x);
        range_chmin(node << 1 | 1, mid + 1, e, l, r, x);
        tree[node] = merge(tree[node << 1], tree[node << 1 | 1]);
    }

    long long query_sum(int node, int s, int e, int l, int r) {
        if (r < s || e < l) return 0;
        if (l <= s && e <= r) return tree[node].sum;
        push(node);
        int mid = (s + e) >> 1;
        return query_sum(node << 1, s, mid, l, r)
             + query_sum(node << 1 | 1, mid + 1, e, l, r);
    }

    long long query_max(int node, int s, int e, int l, int r) {
        if (r < s || e < l) return (long long)-4e18;
        if (l <= s && e <= r) return tree[node].mx1;
        push(node);
        int mid = (s + e) >> 1;
        return max(
            query_max(node << 1, s, mid, l, r),
            query_max(node << 1 | 1, mid + 1, e, l, r)
        );
    }

    void range_chmin(int l, int r, long long x) {
        range_chmin(1, 1, n, l, r, x);
    }

    long long query_sum(int l, int r) {
        return query_sum(1, 1, n, l, r);
    }

    long long query_max(int l, int r) {
        return query_max(1, 1, n, l, r);
    }
};