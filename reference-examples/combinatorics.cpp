#include <bits/stdc++.h>
using namespace std;

struct Combinations {
    static constexpr long long MOD = 1000000007;
    vector<vector<long long>> c;

    Combinations(int N) {
        c.assign(N + 1, vector<long long>(N + 1, 0));
        c[0][0] = 1;

        for (int n = 1; n <= N; n++) {
            c[n][0] = 1;
            c[n][n] = 1;

            for (int k = 1; k < n; k++) {
                c[n][k] = (c[n - 1][k - 1] + c[n - 1][k]) % MOD;
            }
        }
    }

    long long choose(int n, int k) const {
        if (k < 0 || k > n) {
            return 0;
        }

        return c[n][k];
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, q;
    cin >> N >> q;
    Combinations comb(N);
    for (int i = 0; i < q; i++) {
        int n, k;
        cin >> n >> k;
        cout << comb.choose(n, k) << '\n';
    }

    return 0;
}
