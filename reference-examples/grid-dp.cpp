#include <bits/stdc++.h>
using namespace std;

long long grid_paths(const vector<string>& grid) {
    const long long MOD = 1000000007;
    int n = grid.size();

    if (n == 0 || grid[0].empty()) {
        return 0;
    }

    int m = grid[0].size();
    vector<vector<long long>> dp(n, vector<long long>(m, 0));

    for (int r = 0; r < n; r++) {
        for (int c = 0; c < m; c++) {
            if (grid[r][c] == '#') {
                continue;
            }

            if (r == 0 && c == 0) {
                dp[r][c] = 1;
                continue;
            }

            if (r > 0) {
                dp[r][c] += dp[r - 1][c];
            }

            if (c > 0) {
                dp[r][c] += dp[r][c - 1];
            }

            dp[r][c] %= MOD;
        }
    }

    return dp[n - 1][m - 1];
}

int main() {
    vector<string> grid = {"...", "...", "..."};
    cout << grid_paths(grid) << '\n';

    return 0;
}
