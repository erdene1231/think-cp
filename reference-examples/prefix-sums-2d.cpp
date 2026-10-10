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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, q;
    cin >> n >> m >> q;
    vector<vector<long long>> a(n, vector<long long>(m));
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < m; c++) {
            cin >> a[r][c];
        }
    }
    auto pref = prefix_2d(a);
    for (int i = 0; i < q; i++) {
        int r1, c1, r2, c2;
        cin >> r1 >> c1 >> r2 >> c2;
        cout << rectangle_sum(pref, r1, c1, r2, c2) << '\n';
    }

    return 0;
}
