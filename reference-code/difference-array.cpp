#include <bits/stdc++.h>
using namespace std;

struct Update {
    int l;
    int r;
    long long x;
};

vector<long long> apply_updates(int n, const vector<Update>& updates) {
    vector<long long> diff(n + 1, 0);

    for (const auto& update : updates) {
        diff[update.l] += update.x;
        diff[update.r + 1] -= update.x;
    }

    vector<long long> a(n, 0);
    long long sum = 0;

    for (int i = 0; i < n; i++) {
        sum += diff[i];
        a[i] = sum;
    }

    return a;
}
