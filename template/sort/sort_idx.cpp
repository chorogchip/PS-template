#include <bits/stdc++.h>
using namespace std;

template <class T, class C = less<T>>
pair<vector<T>, vector<int>> sorted(vector<T> a, C comp = C()) {
    vector<int> p(a.size());
    iota(p.begin(), p.end(), 0);
    sort(p.begin(), p.end(), [&](int i, int j) { return comp(a[i], a[j]); });
    vector<T> b;
    b.reserve(a.size());
    for (int i : p) b.push_back(a[i]);
    return {b, p};
}