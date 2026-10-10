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
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    cout << stair_ways(n) << '\n';

    return 0;
}
