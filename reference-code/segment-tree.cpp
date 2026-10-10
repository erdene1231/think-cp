#include <bits/stdc++.h>
using namespace std;

struct SegTree {
    int size;
    vector<long long> tree;

    SegTree(const vector<long long>& a) {
        int n = a.size();
        size = 1;

        while (size < n) {
            size *= 2;
        }

        tree.assign(2 * size, 0);

        for (int i = 0; i < n; i++) {
            tree[size + i] = a[i];
        }

        for (int v = size - 1; v >= 1; v--) {
            tree[v] = tree[2 * v] + tree[2 * v + 1];
        }
    }

    void assign(int i, long long x) {
        int v = size + i;
        tree[v] = x;

        while (v > 1) {
            v /= 2;
            tree[v] = tree[2 * v] + tree[2 * v + 1];
        }
    }

    long long sum(int l, int r) const {
        l += size;
        r += size;
        long long ans = 0;

        while (l < r) {
            if (l % 2 == 1) {
                ans += tree[l];
                l++;
            }

            if (r % 2 == 1) {
                r--;
                ans += tree[r];
            }

            l /= 2;
            r /= 2;
        }

        return ans;
    }
};
