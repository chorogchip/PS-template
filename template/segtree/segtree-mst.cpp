#include <bits/stdc++.h>
using namespace std;

struct MergeSortTree {
    int n;
    vector<vector<int>> tree;

    MergeSortTree() {}
    MergeSortTree(const vector<int>& a) { init(a); }

    void init(const vector<int>& a) {
        n = (int)a.size() - 1; // 1-indexed
        tree.assign(4 * n + 4, {});
        build(1, 1, n, a);
    }

    void build(int node, int s, int e, const vector<int>& a) {
        if (s == e) {
            tree[node] = {a[s]};
            return;
        }
        int mid = (s + e) >> 1;
        build(node << 1, s, mid, a);
        build(node << 1 | 1, mid + 1, e, a);

        tree[node].resize(tree[node << 1].size() + tree[node << 1 | 1].size());
        merge(tree[node << 1].begin(), tree[node << 1].end(),
              tree[node << 1 | 1].begin(), tree[node << 1 | 1].end(),
              tree[node].begin());
    }

    int count_leq(int node, int s, int e, int l, int r, int x) {
        if (r < s || e < l) return 0;
        if (l <= s && e <= r) {
            return upper_bound(tree[node].begin(), tree[node].end(), x) - tree[node].begin();
        }
        int mid = (s + e) >> 1;
        return count_leq(node << 1, s, mid, l, r, x)
             + count_leq(node << 1 | 1, mid + 1, e, l, r, x);
    }

    int count_lt(int node, int s, int e, int l, int r, int x) {
        if (r < s || e < l) return 0;
        if (l <= s && e <= r) {
            return lower_bound(tree[node].begin(), tree[node].end(), x) - tree[node].begin();
        }
        int mid = (s + e) >> 1;
        return count_lt(node << 1, s, mid, l, r, x)
             + count_lt(node << 1 | 1, mid + 1, e, l, r, x);
    }

    int count_geq(int l, int r, int x) {
        return (r - l + 1) - count_lt(1, 1, n, l, r, x);
    }

    int count_gt(int l, int r, int x) {
        return (r - l + 1) - count_leq(1, 1, n, l, r, x);
    }

    int count_leq(int l, int r, int x) {
        return count_leq(1, 1, n, l, r, x);
    }

    int count_lt(int l, int r, int x) {
        return count_lt(1, 1, n, l, r, x);
    }
};