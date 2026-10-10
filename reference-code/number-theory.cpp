#include <bits/stdc++.h>
using namespace std;

vector<bool> sieve(int n) {
    vector<bool> is_prime(n + 1, true);
    is_prime[0] = false;

    if (n >= 1) {
        is_prime[1] = false;
    }

    for (int p = 2; 1LL * p * p <= n; p++) {
        if (!is_prime[p]) {
            continue;
        }

        for (long long x = 1LL * p * p; x <= n; x += p) {
            is_prime[x] = false;
        }
    }

    return is_prime;
}

long long modpow(long long a, long long b, long long mod) {
    a %= mod;

    if (a < 0) {
        a += mod;
    }

    long long ans = 1 % mod;

    while (b > 0) {
        if (b % 2 == 1) {
            ans = (__int128) ans * a % mod;
        }

        a = (__int128) a * a % mod;
        b /= 2;
    }

    return ans;
}
