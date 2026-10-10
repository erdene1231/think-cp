#include <bits/stdc++.h>
using namespace std;

struct Combinations {
    static constexpr long long MOD = 1000000007;
    vector<long long> fact;
    vector<long long> invFact;

    static long long power(long long a, long long b) {
        long long ans = 1;

        while (b > 0) {
            if (b % 2 == 1) {
                ans = ans * a % MOD;
            }

            a = a * a % MOD;
            b /= 2;
        }

        return ans;
    }

    Combinations(int n) {
        fact.assign(n + 1, 1);
        invFact.assign(n + 1, 1);

        for (int i = 1; i <= n; i++) {
            fact[i] = fact[i - 1] * i % MOD;
        }

        invFact[n] = power(fact[n], MOD - 2);

        for (int i = n; i >= 1; i--) {
            invFact[i - 1] = invFact[i] * i % MOD;
        }
    }

    long long choose(int n, int k) const {
        if (k < 0 || k > n) {
            return 0;
        }

        long long ans = fact[n] * invFact[k] % MOD;
        ans = ans * invFact[n - k] % MOD;

        return ans;
    }
};
