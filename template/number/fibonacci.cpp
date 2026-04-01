#include <bits/stdc++.h>
using namespace std;

// F(92)는 long long에 들어감
// F(93)부터는 signed 64-bit overflow

using ll = long long;

pair<ll, ll> fib_mod(ll n, ll mod) {
    if (n == 0) return {0, 1};

    auto [a, b] = fib_mod(n >> 1, mod);

    ll two_b_minus_a = (2 * b % mod - a + mod) % mod;
    ll c = a * two_b_minus_a % mod;         // F(2k)
    ll d = (a * a % mod + b * b % mod) % mod; // F(2k+1)

    if (n & 1) return {d, (c + d) % mod};
    else return {c, d};  // (fib(n), fib(n+1))
}

long long fib_sum(long long l, long long r, long long mod) {
    auto A = fib_mod(r + 2, mod).first;
    auto B = fib_mod(l + 1, mod).first;
    return (A - B + mod) % mod;
}

long long fib_gcd(long long n, long long m, long long mod) {
    return fib_mod(std::gcd(n, m), mod).first;
}

vector<long long> build_fibs(long long limit) {
    vector<long long> f = {0, 1};
    while (true) {
        long long nxt = f[f.size() - 1] + f[f.size() - 2];
        if (nxt > limit) break;
        f.push_back(nxt);
    }
    return f;
}

vector<long long> fib_decompose(long long x) {  // Zeckendorf: 양의정수를 이웃하지 않은 피보나치 합으로 표현
    vector<long long> fibs = build_fibs(x);
    vector<long long> res;

    for (int i = (int)fibs.size() - 1; i >= 2; --i) {
        if (fibs[i] <= x) {
            x -= fibs[i];
            res.push_back(fibs[i]);
        }
    }
    return res;
}