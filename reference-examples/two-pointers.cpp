#include <bits/stdc++.h>
using namespace std;

long long count_subarrays(const vector<long long>& a, long long k) {
    if (k < 0) {
        return 0;
    }

    int n = a.size();
    int l = 0;
    long long sum = 0;
    long long ans = 0;

    for (int r = 0; r < n; r++) {
        sum += a[r];

        while (sum > k) {
            sum -= a[l];
            l++;
        }

        ans += r - l + 1;
    }

    return ans;
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
    long long k;
    cin >> k;
    cout << count_subarrays(a, k) << '\n';

    return 0;
}
