#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct Comb {
    int n;
    ll mod;
    vector<ll> fac, ifac;

    ll modpow(ll a, ll e) {
        ll r = 1;
        while (e > 0) {
            if (e & 1) r = r * a % mod;
            a = a * a % mod;
            e >>= 1;
        }
        return r;
    }

    Comb(int _n, ll _mod) : n(_n), mod(_mod) {
        fac.assign(n + 1, 1);
        ifac.assign(n + 1, 1);

        for (int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % mod;
        ifac[n] = modpow(fac[n], mod - 2);
        for (int i = n; i >= 1; i--) ifac[i - 1] = ifac[i] * i % mod;
    }

    ll C(int N, int K) {
        if (K < 0 || K > N) return 0;
        return fac[N] * ifac[K] % mod * ifac[N - K] % mod;
    }

    ll P(int N, int K) {
        if (K < 0 || K > N) return 0;
        return fac[N] * ifac[N - K] % mod;
    }

    ll H(int N, int K) { // 중복조합: N종류에서 K개
        if (N == 0 && K == 0) return 1;
        if (N <= 0 || K < 0) return 0;
        return C(N + K - 1, K);
    }
};

vector<vector<ll>> make_nCk(int n, ll mod) {
    vector<vector<ll>> C(n + 1, vector<ll>(n + 1, 0));
    C[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; j++) {
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
        }
    }
    return C;
}

int main() {
    const ll MOD = 1'000'000'007;
    Comb comb(1'000'000, MOD);

    cout << comb.C(5, 2) << '\n'; // 10
    cout << comb.P(5, 2) << '\n'; // 20
    cout << comb.H(3, 2) << '\n'; // 6
}