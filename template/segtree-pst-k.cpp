#include <bits/stdc++.h>
using namespace std;

struct PersistentKthSegTree {
    struct Node {
        int cnt;
        Node *l, *r;
        Node(int cnt = 0, Node* l = nullptr, Node* r = nullptr)
            : cnt(cnt), l(l), r(r) {}
    };

    int n; // compressed value range
    vector<Node*> root;

    PersistentKthSegTree() {}
    PersistentKthSegTree(int n) { init(n); }

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
        return new Node(0, left, right);
    }

    Node* update(Node* prev, int s, int e, int idx) {
        if (idx < s || e < idx) return prev;
        if (s == e) return new Node(prev->cnt + 1);
        int mid = (s + e) >> 1;
        Node* left = update(prev->l, s, mid, idx);
        Node* right = update(prev->r, mid + 1, e, idx);
        return new Node(left->cnt + right->cnt, left, right);
    }

    void addVersion(int compressedValue) {
        root.push_back(update(root.back(), 1, n, compressedValue));
    }

    int kth(Node* leftRoot, Node* rightRoot, int s, int e, int k) {
        if (s == e) return s;
        int mid = (s + e) >> 1;
        int leftCnt = rightRoot->l->cnt - leftRoot->l->cnt;
        if (k <= leftCnt) return kth(leftRoot->l, rightRoot->l, s, mid, k);
        return kth(leftRoot->r, rightRoot->r, mid + 1, e, k - leftCnt);
    }

    int kth(int l, int r, int k) {
        return kth(root[l - 1], root[r], 1, n, k);
    }

    int count_leq(Node* leftRoot, Node* rightRoot, int s, int e, int x) {
        if (x < s) return 0;
        if (e <= x) return rightRoot->cnt - leftRoot->cnt;
        int mid = (s + e) >> 1;
        return count_leq(leftRoot->l, rightRoot->l, s, mid, x)
             + count_leq(leftRoot->r, rightRoot->r, mid + 1, e, x);
    }

    int count_leq(int l, int r, int x) {
        return count_leq(root[l - 1], root[r], 1, n, x);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 예시 배열 (1-indexed)
    int n = 5;
    vector<int> a = {0, 5, 1, 7, 3, 9};

    // 1) 좌표압축
    vector<int> vals;
    for (int i = 1; i <= n; i++) vals.push_back(a[i]);
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());

    auto compress = [&](int x) {
        return (int)(lower_bound(vals.begin(), vals.end(), x) - vals.begin()) + 1;
    };

    // 2) PST 초기화
    PersistentKthSegTree pst((int)vals.size());

    // 3) prefix 버전 생성
    // root[0] : 아무것도 없는 상태
    // root[i] : a[1..i]까지 반영된 상태
    for (int i = 1; i <= n; i++) {
        pst.addVersion(compress(a[i]));
    }

    // 예시 1: 구간 [2, 5] = [1, 7, 3, 9]
    // 정렬하면 [1, 3, 7, 9]
    // 2번째 수는 3
    int l = 2, r = 5, k = 2;
    int kthCompressed = pst.kth(l, r, k);
    int kthValue = vals[kthCompressed - 1];
    cout << "kth = " << kthValue << '\n';  // 3

    // 예시 2: 구간 [1, 4] = [5, 1, 7, 3]
    // 5 이하 개수는 3개 (5,1,3)
    int x = 5;
    int compressedX = upper_bound(vals.begin(), vals.end(), x) - vals.begin();
    int cnt = pst.count_leq(1, 4, compressedX);
    cout << "count <= 5 = " << cnt << '\n'; // 3

    return 0;
}