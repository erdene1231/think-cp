#include <bits/stdc++.h>
using namespace std;

long long knapsack(int W, const vector<pair<int, long long>>& items) {
    vector<long long> dp(W + 1, 0);

    for (const auto& item : items) {
        int w = item.first;
        long long value = item.second;

        for (int c = W; c >= w; c--) {
            dp[c] = max(dp[c], dp[c - w] + value);
        }
    }

    return dp[W];
}
