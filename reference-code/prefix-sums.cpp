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
