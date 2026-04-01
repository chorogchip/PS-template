#include <bits/stdc++.h>
using namespace std;

namespace std {
    template <class A, class B>
    struct hash<pair<A, B>> {
        size_t operator()(const pair<A, B>& p) const {
            size_t h1 = hash<A>{}(p.first);
            size_t h2 = hash<B>{}(p.second);
            return h1 ^ (h2 + 0x9e3779b9 + (h1 << 6) + (h1 >> 2));
        }
    };

    template <class... Ts>
    struct hash<tuple<Ts...>> {
        size_t operator()(const tuple<Ts...>& t) const {
            size_t seed = 0;
            apply([&](const auto&... xs) {
                ((seed ^= hash<decay_t<decltype(xs)>>{}(xs)
                        + 0x9e3779b9 + (seed << 6) + (seed >> 2)), ...);
            }, t);
            return seed;
        }
    };

    template <class T>
    struct hash<vector<T>> {
        size_t operator()(const vector<T>& v) const {
            size_t seed = v.size();
            for (const auto& x : v) {
                seed ^= hash<T>{}(x) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            }
            return seed;
        }
    };
}