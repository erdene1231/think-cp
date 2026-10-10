#include <bits/stdc++.h>
using namespace std;

struct Fenwick {
    int n;
    vector<long long> bit;

    Fenwick(int size) {
        n = size;
        bit.assign(n + 1, 0);
    }

    void add(int index, long long x) {
        int i = index + 1;

        while (i <= n) {
            bit[i] += x;
            i += i & (-i);
        }
    }

    long long prefix(int r) const {
        long long ans = 0;
        int i = r;

        while (i > 0) {
            ans += bit[i];
            i -= i & (-i);
        }

        return ans;
    }

    long long sum(int l, int r) const {
        return prefix(r + 1) - prefix(l);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    Fenwick bit(n);
    for (int i = 0; i < n; i++) {
        long long x;
        cin >> x;
        bit.add(i, x);
    }
    for (int i = 0; i < q; i++) {
        string type;
        cin >> type;
        if (type == "add") {
            int pos;
            long long x;
            cin >> pos >> x;
            bit.add(pos, x);
        } else if (type == "sum") {
            int l, r;
            cin >> l >> r;
            cout << bit.sum(l, r) << '\n';
        }
    }

    return 0;
}
