#include <bits/stdc++.h>
using namespace std;

struct PersistentDSU {
    struct Node {
        int l, r;
        int val;
        Node(int l=0, int r=0, int val=0) : l(l), r(r), val(val) {}
    };

    int n;
    vector<Node> seg;
    vector<int> parent_root, size_root;

    PersistentDSU(int n) : n(n) {
        seg.reserve(4000000); // 필요시 늘리기
        seg.push_back(Node()); // dummy
        parent_root.push_back(build_parent(1, n));
        size_root.push_back(build_size(1, n));
    }

    int new_node(const Node& x) {
        seg.push_back(x);
        return (int)seg.size() - 1;
    }

    int build_parent(int s, int e) {
        int idx = new_node(Node());
        if (s == e) {
            seg[idx].val = s;
            return idx;
        }
        int m = (s + e) >> 1;
        seg[idx].l = build_parent(s, m);
        seg[idx].r = build_parent(m + 1, e);
        return idx;
    }

    int build_size(int s, int e) {
        int idx = new_node(Node());
        if (s == e) {
            seg[idx].val = 1;
            return idx;
        }
        int m = (s + e) >> 1;
        seg[idx].l = build_size(s, m);
        seg[idx].r = build_size(m + 1, e);
        return idx;
    }

    int query(int node, int s, int e, int pos) const {
        if (s == e) return seg[node].val;
        int m = (s + e) >> 1;
        if (pos <= m) return query(seg[node].l, s, m, pos);
        return query(seg[node].r, m + 1, e, pos);
    }

    int update(int node, int s, int e, int pos, int val) {
        int idx = new_node(seg[node]);
        if (s == e) {
            seg[idx].val = val;
            return idx;
        }
        int m = (s + e) >> 1;
        if (pos <= m) seg[idx].l = update(seg[node].l, s, m, pos, val);
        else seg[idx].r = update(seg[node].r, m + 1, e, pos, val);
        return idx;
    }

    int get_parent(int ver, int x) const {
        return query(parent_root[ver], 1, n, x);
    }

    int get_size(int ver, int x) const {
        return query(size_root[ver], 1, n, x);
    }

    int find(int ver, int x) const {
        int p = get_parent(ver, x);
        if (p == x) return x;
        return find(ver, p);
    }

    bool same(int ver, int a, int b) const {
        return find(ver, a) == find(ver, b);
    }

    int size(int ver, int x) const {
        int r = find(ver, x);
        return get_size(ver, r);
    }

    // ver 기준으로 a,b를 합친 새 버전 반환
    int unite(int ver, int a, int b) {
        int ra = find(ver, a);
        int rb = find(ver, b);

        int new_parent = parent_root[ver];
        int new_size = size_root[ver];

        if (ra == rb) {
            parent_root.push_back(new_parent);
            size_root.push_back(new_size);
            return (int)parent_root.size() - 1;
        }

        int სა = get_size(ver, ra);
        int sb = get_size(ver, rb);

        if (სა < sb) swap(ra, rb), swap(სა, sb);

        // rb를 ra 밑으로
        new_parent = update(new_parent, 1, n, rb, ra);
        new_size = update(new_size, 1, n, ra, სა + sb);

        parent_root.push_back(new_parent);
        size_root.push_back(new_size);
        return (int)parent_root.size() - 1;
    }

    // 특정 기존 버전을 그대로 복사해서 새 버전으로 추가
    int clone_version(int ver) {
        parent_root.push_back(parent_root[ver]);
        size_root.push_back(size_root[ver]);
        return (int)parent_root.size() - 1;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    PersistentDSU uf(5);

    int v0 = 0;                  // 초기 버전
    int v1 = uf.unite(v0, 1, 2); // v1
    int v2 = uf.unite(v1, 2, 3); // v2
    int v3 = uf.unite(v0, 4, 5); // v0에서 갈라진 다른 버전

    cout << uf.same(v0, 1, 3) << '\n'; // 0
    cout << uf.same(v2, 1, 3) << '\n'; // 1
    cout << uf.same(v3, 1, 3) << '\n'; // 0
    cout << uf.same(v3, 4, 5) << '\n'; // 1
}