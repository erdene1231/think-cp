#include <bits/stdc++.h>
using namespace std;

bool can_split(const vector<long long>& a, int k, long long limit) {
    int parts = 1;
    long long sum = 0;

    for (long long x : a) {
        if (x > limit) {
            return false;
        }

        if (sum + x > limit) {
            parts++;
            sum = x;
        } else {
            sum += x;
        }
    }

    return parts <= k;
}

long long min_largest_sum(const vector<long long>& a, int k) {
    long long l = 0;
    long long r = 0;

    for (long long x : a) {
        l = max(l, x);
        r += x;
    }

    while (l < r) {
        long long mid = l + (r - l) / 2;

        if (can_split(a, k, mid)) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }

    return l;
}
