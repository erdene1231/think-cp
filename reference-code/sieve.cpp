#include <bits/stdc++.h>
using namespace std;

vector<bool> prime_sieve(int n) {
    vector<bool> prime(n + 1, true);
    prime[0] = false;

    if (n >= 1) {
        prime[1] = false;
    }

    for (int p = 2; 1LL * p * p <= n; p++) {
        if (!prime[p]) {
            continue;
        }

        for (long long x = 1LL * p * p; x <= n; x += p) {
            prime[x] = false;
        }
    }

    return prime;
}
