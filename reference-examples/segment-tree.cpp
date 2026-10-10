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
    vector<long long> a = {2, 1, 3, 4};
    SegTree st(a);

    cout << st.query(1, 3) << '\n';
    st.update(2, 8);
    cout << st.query(1, 3) << '\n';

    return 0;
}
