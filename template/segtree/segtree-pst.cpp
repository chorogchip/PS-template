#include <bits/stdc++.h>
using namespace std;

struct PersistentSegTree {
    struct Node {
        long long val;
        Node *l, *r;
        Node(long long val = 0, Node* l = nullptr, Node* r = nullptr)
            : val(val), l(l), r(r) {}
    };

    int n;
    vector<Node*> root;

    PersistentSegTree() {}
    PersistentSegTree(int n) { init(n); }

    void init(int n_) {
        n = n_;
        root.clear();
        root.push_back(build(1, n));
    }

    Node* build(int s, int e) {
        if (s == e) return new Node(0);
        int mid = (s + e) >> 1;
        Node* left = build(s, mid);
        Node* right = build(mid + 1, e);
        return new Node(left->val + right->val, left, right);
    }

    Node* update(Node* prev, int s, int e, int idx, long long val) {
        if (idx < s || e < idx) return prev;
        if (s == e) {
            // TODO: 점 갱신 방식 수정 가능
            // 대입이면 val
            // 증가면 prev->val + val
            return new Node(val);
        }
        int mid = (s + e) >> 1;
        Node* left = update(prev->l, s, mid, idx, val);
        Node* right = update(prev->r, mid + 1, e, idx, val);
        return new Node(left->val + right->val, left, right);
    }

    long long query(Node* node, int s, int e, int l, int r) {
        if (r < s || e < l) return 0; // TODO: 항등원 수정
        if (l <= s && e <= r) return node->val;
        int mid = (s + e) >> 1;
        return query(node->l, s, mid, l, r) + query(node->r, mid + 1, e, l, r);
    }

    void update(int version, int idx, long long val) {
        Node* newRoot = update(root[version], 1, n, idx, val);
        root.push_back(newRoot);
    }

    long long query(int version, int l, int r) {
        return query(root[version], 1, n, l, r);
    }
};