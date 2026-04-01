#include <bits/stdc++.h>
using namespace std;

vector<int> topo_sort(const vector<vector<int>>& g) {
    int n = (int)g.size();
    vector<int> indeg(n), ord;
    queue<int> q;
    for (int u = 0; u < n; u++) for (int v : g[u]) indeg[v]++;
    for (int i = 0; i < n; i++) if (indeg[i] == 0) q.push(i);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        ord.push_back(u);
        for (int v : g[u]) if (--indeg[v] == 0) q.push(v);
    }
    if ((int)ord.size() != n) return {};
    return ord;
}

vector<int> topo_sort_lexi(const vector<vector<int>>& g) {
    int n = (int)g.size();
    vector<int> indeg(n), ord;
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int u = 0; u < n; u++) for (int v : g[u]) indeg[v]++;
    for (int i = 0; i < n; i++) if (indeg[i] == 0) pq.push(i);
    while (!pq.empty()) {
        int u = pq.top(); pq.pop();
        ord.push_back(u);
        for (int v : g[u]) if (--indeg[v] == 0) pq.push(v);
    }
    if ((int)ord.size() != n) return {};
    return ord;
}

vector<int> topo_sort_dfs(const vector<vector<int>>& g) {
    int n = (int)g.size();
    vector<int> vis(n, 0), ord;
    bool ok = true;

    auto dfs = [&](auto&& self, int u) -> void {
        vis[u] = 1;
        for (int v : g[u]) {
            if (vis[v] == 0) self(self, v);
            else if (vis[v] == 1) ok = false;
        }
        vis[u] = 2;
        ord.push_back(u);
    };

    for (int i = 0; i < n; i++) {
        if (vis[i] == 0) dfs(dfs, i);
    }

    if (!ok) return {};
    reverse(ord.begin(), ord.end());
    return ord;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        g[u].push_back(v);
    }

    auto ord = topo_sort(g);

    if (ord.empty()) {
        cout << -1 << '\n'; // cycle
    } else {
        for (int x : ord) cout << x + 1 << ' ';
        cout << '\n';
    }
}