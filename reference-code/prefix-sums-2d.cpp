#include <bits/stdc++.h>
using namespace std;

vector<vector<long long>> prefix_2d(const vector<vector<long long>>& a) {
    int n = a.size();
    int m = n == 0 ? 0 : a[0].size();
    vector<vector<long long>> pref(n + 1, vector<long long>(m + 1, 0));

    for (int r = 1; r <= n; r++) {
        for (int c = 1; c <= m; c++) {
            pref[r][c] = a[r - 1][c - 1] + pref[r - 1][c] + pref[r][c - 1];
            pref[r][c] -= pref[r - 1][c - 1];
        }
    }

    return pref;
}

long long rectangle_sum(const vector<vector<long long>>& pref,
                        int r1, int c1, int r2, int c2) {
    long long ans = pref[r2 + 1][c2 + 1];
    ans -= pref[r1][c2 + 1];
    ans -= pref[r2 + 1][c1];
    ans += pref[r1][c1];

    return ans;
}
