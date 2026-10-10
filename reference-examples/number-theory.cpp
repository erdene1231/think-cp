#include <bits/stdc++.h>
using namespace std;

vector<pair<long long, int>> factorize(long long n) {
    vector<pair<long long, int>> factors;

    for (long long p = 2; p <= n / p; p++) {
        if (n % p != 0) {
            continue;
        }

        int count = 0;

        while (n % p == 0) {
            n /= p;
            count++;
        }

        factors.push_back({p, count});
    }

    if (n > 1) {
        factors.push_back({n, 1});
    }

    return factors;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n;
    cin >> n;
    auto factors = factorize(n);
    for (const auto& factor : factors) {
        cout << factor.first << ' ' << factor.second << '\n';
    }

    return 0;
}
