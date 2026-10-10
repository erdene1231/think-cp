#include <bits/stdc++.h>
using namespace std;

vector<long long> prefix(const vector<long long>& a) {
    int n = a.size();
    vector<long long> pref(n + 1, 0);

    for (int i = 0; i < n; i++) {
        pref[i + 1] = pref[i] + a[i];
    }

    return pref;
}

long long range_sum(const vector<long long>& pref, int l, int r) {
    return pref[r + 1] - pref[l];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<long long> pref = prefix(a);
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        cout << range_sum(pref, l, r) << '\n';
    }

    return 0;
}
