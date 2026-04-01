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

template <class T>
struct Edge {
    int u, v;
    T w;
    bool operator<(const Edge& other) const {
        return w < other.w;
    }
};

template <class T>
pair<T, vector<Edge<T>>> mst(int n, vector<Edge<T>> edges) {
    sort(edges.begin(), edges.end());
    UF_PC dsu(n);
    T cost = 0;
    vector<Edge<T>> used;
    for (auto& e : edges) {
        if (dsu.unite(e.u, e.v)) {
            cost += e.w;
            used.push_back(e);
        }
    }
    return {cost, used};
}