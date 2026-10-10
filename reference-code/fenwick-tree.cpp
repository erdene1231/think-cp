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
        return prefix(r) - prefix(l);
    }
};
