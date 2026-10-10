#include <bits/stdc++.h>
using namespace std;

long long assignment(const vector<vector<long long>>& cost) {
    int n = cost.size();
    int states = 1 << n;
    const long long INF = 4'000'000'000'000'000'000LL;

    vector<long long> dp(states, INF);
    dp[0] = 0;

    for (int mask = 0; mask < states; mask++) {
        int i = __builtin_popcount(mask);

        if (i == n) {
            continue;
        }

        for (int j = 0; j < n; j++) {
            if ((mask & (1 << j)) != 0) {
                continue;
            }

            int next_mask = mask | (1 << j);
            long long new_cost = dp[mask] + cost[i][j];
            dp[next_mask] = min(dp[next_mask], new_cost);
        }
    }

    return dp[states - 1];
}
