#include <bits/stdc++.h>
using namespace std;

struct SparseTable {
    vector<vector<long long>> st;
    vector<int> lg;

    SparseTable(const vector<long long>& a) {
        int n = a.size();
        lg.assign(n + 1, 0);

        for (int i = 2; i <= n; i++) {
            lg[i] = lg[i / 2] + 1;
        }

        int levels = lg[n] + 1;
        st.assign(levels, vector<long long>(n));
        st[0] = a;

        for (int k = 1; k < levels; k++) {
            int len = 1 << k;
            int half = len / 2;

            for (int i = 0; i + len <= n; i++) {
                st[k][i] = min(st[k - 1][i], st[k - 1][i + half]);
            }
        }
    }

    long long query(int l, int r) const {
        int k = lg[r - l + 1];
        int len = 1 << k;

        return min(st[k][l], st[k][r - len + 1]);
    }
};
