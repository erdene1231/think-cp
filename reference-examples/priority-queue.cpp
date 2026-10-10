#include <bits/stdc++.h>
using namespace std;

vector<long long> smallest_first(const vector<long long>& a) {
    priority_queue<long long, vector<long long>, greater<long long>> pq;

    for (long long x : a) {
        pq.push(x);
    }

    vector<long long> ans;

    while (!pq.empty()) {
        ans.push_back(pq.top());
        pq.pop();
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
    vector<long long> ans = smallest_first(a);
    for (int i = 0; i < (int)ans.size(); i++) {
        if (i > 0) {
            cout << ' ';
        }
        cout << ans[i];
    }
    cout << '\n';

    return 0;
}
