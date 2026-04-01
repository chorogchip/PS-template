#include <bits/stdc++.h>
using namespace std;

template <class F>
long long parametric_search_max(F check) {
    long long lo = 0, hi = 1e18 + 1;
    while (lo + 1 < hi) {
        long long mid = lo + (hi - lo) / 2;
        if (check(mid)) lo = mid;
        else hi = mid;
    }
    return lo;
}

template <class F>
long long parametric_search_min(F check) {
    long long lo = 0, hi = 1e18 + 1;
    while (lo + 1 < hi) {
        long long mid = lo + (hi - lo) / 2;
        if (check(mid)) hi = mid;
        else lo = mid;
    }
    return hi;
}


