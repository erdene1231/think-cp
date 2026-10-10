#include <bits/stdc++.h>
using namespace std;

long long knapsack(int W, const vector<pair<int, long long>>& items) {
    int n = items.size();
    vector<vector<long long>> dp(n + 1, vector<long long>(W + 1, 0));

    for (int i = 1; i <= n; i++) {
        int w = items[i - 1].first;
        long long value = items[i - 1].second;

        for (int c = 0; c <= W; c++) {
            dp[i][c] = dp[i - 1][c];

            if (c >= w) {
                long long take = dp[i - 1][c - w] + value;
                dp[i][c] = max(dp[i][c], take);
            }
        }
    }

    return dp[n][W];
}

int main() {
    vector<pair<int, long long>> items = {{2, 3}, {3, 4}, {4, 5}};
    cout << knapsack(5, items) << '\n';

    return 0;
}
