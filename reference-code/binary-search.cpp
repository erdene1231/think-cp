#include <bits/stdc++.h>
using namespace std;

int first_at_least(const vector<long long>& a, long long x) {
    int n = a.size();
    int l = 0;
    int r = n;

    while (l < r) {
        int mid = l + (r - l) / 2;

        if (a[mid] >= x) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }

    return l;
}
