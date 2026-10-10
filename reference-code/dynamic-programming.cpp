#include <bits/stdc++.h>
using namespace std;

long long stair_ways(int n) {
    const long long MOD = 1000000007;

    if (n == 0) {
        return 1;
    }

    long long prev = 1;
    long long curr = 1;

    for (int i = 2; i <= n; i++) {
        long long next = (prev + curr) % MOD;
        prev = curr;
        curr = next;
    }

    return curr;
}
