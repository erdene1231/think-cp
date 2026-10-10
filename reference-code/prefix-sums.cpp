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

struct Update {
    int l;
    int r;
    long long x;
};

vector<long long> apply_updates(int n, const vector<Update>& updates) {
    vector<long long> diff(n + 1, 0);
    vector<long long> a(n, 0);

    for (const Update& update : updates) {
        diff[update.l] += update.x;
        diff[update.r] -= update.x;
    }

    long long sum = 0;

    for (int i = 0; i < n; i++) {
        sum += diff[i];
        a[i] = sum;
    }

    return a;
}
