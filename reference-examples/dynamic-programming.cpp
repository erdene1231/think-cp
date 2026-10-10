#include <bits/stdc++.h>
using namespace std;

long long stair_ways(int n) {
    const long long MOD = 1000000007;
    vector<long long> dp(n + 1, 0);
    dp[0] = 1;

    for (int i = 1; i <= n; i++) {
        dp[i] = dp[i - 1];

        if (i >= 2) {
            dp[i] = (dp[i] + dp[i - 2]) % MOD;
        }
    }

    return dp[n];
}

int main() {
    cout << stair_ways(4) << '\n';

    return 0;
}
