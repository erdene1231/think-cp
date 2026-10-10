#include <bits/stdc++.h>
using namespace std;

struct SegTree {
    int n;
    vector<long long> tree;

    SegTree(const vector<long long>& a) {
        n = a.size();
        tree.assign(4 * max(1, n), 0);

        if (n > 0) {
            build(1, 0, n - 1, a);
        }
    }

    void build(int v, int l, int r, const vector<long long>& a) {
        if (l == r) {
            tree[v] = a[l];
            return;
        }

        int mid = l + (r - l) / 2;
        build(2 * v, l, mid, a);
        build(2 * v + 1, mid + 1, r, a);
        tree[v] = tree[2 * v] + tree[2 * v + 1];
    }

    void update(int v, int l, int r, int pos, long long x) {
        if (l == r) {
            tree[v] = x;
            return;
        }

        int mid = l + (r - l) / 2;

        if (pos <= mid) {
            update(2 * v, l, mid, pos, x);
        } else {
            update(2 * v + 1, mid + 1, r, pos, x);
        }

        tree[v] = tree[2 * v] + tree[2 * v + 1];
    }

    long long query(int v, int l, int r, int ql, int qr) const {
        if (qr < l || r < ql) {
            return 0;
        }

        if (ql <= l && r <= qr) {
            return tree[v];
        }

        int mid = l + (r - l) / 2;
        long long left_sum = query(2 * v, l, mid, ql, qr);
        long long right_sum = query(2 * v + 1, mid + 1, r, ql, qr);

        return left_sum + right_sum;
    }

    void update(int pos, long long x) {
        update(1, 0, n - 1, pos, x);
    }

    long long query(int l, int r) const {
        if (n == 0 || l > r) {
            return 0;
        }

        return query(1, 0, n - 1, l, r);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    SegTree st(a);
    for (int i = 0; i < q; i++) {
        string type;
        cin >> type;
        if (type == "set") {
            int pos;
            long long x;
            cin >> pos >> x;
            st.update(pos, x);
        } else if (type == "sum") {
            int l, r;
            cin >> l >> r;
            cout << st.query(l, r) << '\n';
        }
    }

    return 0;
}
