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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        long long x;
        cin >> x;
        cout << first_at_least(a, x) << '\n';
    }

    return 0;
}
