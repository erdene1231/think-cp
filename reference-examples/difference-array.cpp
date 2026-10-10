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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<Update> updates(q);
    for (int i = 0; i < q; i++) {
        cin >> updates[i].l >> updates[i].r >> updates[i].x;
    }
    vector<long long> ans = apply_updates(n, updates);
    for (int i = 0; i < (int)ans.size(); i++) {
        if (i > 0) {
            cout << ' ';
        }
        cout << ans[i];
    }
    cout << '\n';

    return 0;
}
