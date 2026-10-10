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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long a, b, mod;
    cin >> a >> b >> mod;
    cout << power_mod(a, b, mod) << '\n';

    return 0;
}
