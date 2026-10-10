#include <bits/stdc++.h>
using namespace std;

long long power_mod(long long a, long long b, long long mod) {
    long long ans = 1 % mod;
    a %= mod;

    if (a < 0) {
        a += mod;
    }

    while (b > 0) {
        if (b % 2 == 1) {
            ans = ans * a % mod;
        }

        a = a * a % mod;
        b /= 2;
    }

    return ans;
}
