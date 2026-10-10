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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<bool> prime = prime_sieve(n);
    bool first = true;
    for (int x = 2; x <= n; x++) {
        if (prime[x]) {
            if (!first) {
                cout << ' ';
            }
            cout << x;
            first = false;
        }
    }
    cout << '\n';

    return 0;
}
