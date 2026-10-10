#include <bits/stdc++.h>
using namespace std;

bool has_pair(const vector<long long>& a, long long target) {
    int n = a.size();

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (a[i] + a[j] == target) {
                return true;
            }
        }
    }

    return false;
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
    long long target;
    cin >> target;
    cout << (has_pair(a, target) ? "YES" : "NO") << '\n';

    return 0;
}
