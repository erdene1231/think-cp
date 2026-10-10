#include <bits/stdc++.h>
using namespace std;

struct LazySeg {
    int n;
    vector<long long> tree;
    vector<long long> lazy;

    LazySeg(const vector<long long>& a) {
        n = a.size();
        tree.assign(4 * n, 0);
        lazy.assign(4 * n, 0);
        build(1, 0, n, a);
    }

    void build(int v, int l, int r, const vector<long long>& a) {
        if (r - l == 1) {
            tree[v] = a[l];
            return;
        }

        int mid = l + (r - l) / 2;
        build(2 * v, l, mid, a);
        build(2 * v + 1, mid, r, a);

        tree[v] = tree[2 * v] + tree[2 * v + 1];
    }

    void apply(int v, int l, int r, long long x) {
        tree[v] += x * (r - l);
        lazy[v] += x;
    }

    void push(int v, int l, int r) {
        if (r - l == 1 || lazy[v] == 0) {
            return;
        }

        int mid = l + (r - l) / 2;
        apply(2 * v, l, mid, lazy[v]);
        apply(2 * v + 1, mid, r, lazy[v]);
        lazy[v] = 0;
    }

    void add(int ql, int qr, long long x, int v, int l, int r) {
        if (qr <= l || r <= ql) {
            return;
        }

        if (ql <= l && r <= qr) {
            apply(v, l, r, x);
            return;
        }

        push(v, l, r);
        int mid = l + (r - l) / 2;

        add(ql, qr, x, 2 * v, l, mid);
        add(ql, qr, x, 2 * v + 1, mid, r);

        tree[v] = tree[2 * v] + tree[2 * v + 1];
    }

    long long query(int ql, int qr, int v, int l, int r) {
        if (qr <= l || r <= ql) {
            return 0;
        }

        if (ql <= l && r <= qr) {
            return tree[v];
        }

        push(v, l, r);
        int mid = l + (r - l) / 2;

        long long left_sum = query(ql, qr, 2 * v, l, mid);
        long long right_sum = query(ql, qr, 2 * v + 1, mid, r);

        return left_sum + right_sum;
    }

    void add(int l, int r, long long x) {
        add(l, r, x, 1, 0, n);
    }

    long long query(int l, int r) {
        return query(l, r, 1, 0, n);
    }
};
