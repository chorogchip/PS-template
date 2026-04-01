#include <bits/stdc++.h>
using namespace std;

struct UF_PC {
    vector<int> parent;
    UF_PC(int n) {
        parent.resize(n + 1);
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]); // path compression
    }
    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false;
        parent[b] = a;
        return true;
    }
    bool same(int a, int b) {
        return find(a) == find(b);
    }
};

struct UF_Size {
    vector<int> parent, sz;

    UF_Size(int n) {
        parent.resize(n + 1);
        sz.assign(n + 1, 1);
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int x) {
        while (parent[x] != x) x = parent[x];
        return x;
    }
    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false;

        if (sz[a] < sz[b]) swap(a, b);
        parent[b] = a;
        sz[a] += sz[b];
        return true;
    }
    bool same(int a, int b) {
        return find(a) == find(b);
    }
    int size(int x) {
        return sz[find(x)];
    }
};

struct DSURollback {
    vector<int> p; // root면 -size, 아니면 parent
    vector<pair<int,int>> st; // (idx, old_value)

    DSURollback(int n) {
        p.assign(n + 1, -1);
    }
    int find(int x) {
        while (p[x] >= 0) x = p[x];
        return x;
    }
    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false;
        if (p[a] > p[b]) swap(a, b); // size(a) >= size(b)
        st.push_back({a, p[a]});
        st.push_back({b, p[b]});

        p[a] += p[b];
        p[b] = a;
        return true;
    }
    int snapshot() {
        return (int)st.size();
    }
    void rollback(int snap) {
        while ((int)st.size() > snap) {
            auto [idx, val] = st.back();
            st.pop_back();
            p[idx] = val;
        }
    }
    int size(int x) {
        x = find(x);
        return -p[x];
    }
    bool same(int a, int b) {
        return find(a) == find(b);
    }
};



int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
}