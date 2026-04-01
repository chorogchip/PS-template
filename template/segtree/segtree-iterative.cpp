#include <bits/stdc++.h>
using namespace std;

struct IterSegTree {
    int n;
    vector<long long> tree;

    IterSegTree() {}
    IterSegTree(int n) { init(n); }
    IterSegTree(const vector<long long>& a) { init(a); }

    void init(int n_) {
        n = n_;
        tree.assign(2 * n, 0); // TODO: 항등원 수정
    }

    void init(const vector<long long>& a) {
        n = (int)a.size() - 1; // 1-indexed
        tree.assign(2 * n, 0); // TODO: 항등원 수정

        for (int i = 1; i <= n; i++) tree[n + i - 1] = a[i];
        for (int i = n - 1; i >= 1; i--) {
            tree[i] = merge(tree[i << 1], tree[i << 1 | 1]);
        }
    }

    long long merge(long long a, long long b) {
        // TODO: 원하는 연산으로 수정
        // sum -> a + b
        // min -> min(a, b)
        // max -> max(a, b)
        return a + b;
    }

    long long identity() {
        // TODO: 항등원 수정
        return 0;
    }

    void update(int pos, long long val) {
        // TODO: 점 갱신 방식 수정 가능
        // 대입이면 = val
        // 더하기면 += val
        pos = n + pos - 1;
        tree[pos] = val;
        for (pos >>= 1; pos >= 1; pos >>= 1) {
            tree[pos] = merge(tree[pos << 1], tree[pos << 1 | 1]);
        }
    }

    long long query(int l, int r) {
        long long leftRes = identity(), rightRes = identity();
        l = l + n - 1;
        r = r + n - 1;

        while (l <= r) {
            if (l & 1) leftRes = merge(leftRes, tree[l++]);
            if (!(r & 1)) rightRes = merge(tree[r--], rightRes);
            l >>= 1;
            r >>= 1;
        }

        return merge(leftRes, rightRes);
    }
};