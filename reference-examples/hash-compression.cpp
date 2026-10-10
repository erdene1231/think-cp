#include <bits/stdc++.h>
using namespace std;

pair<vector<int>, vector<long long>> compress(const vector<long long>& a) {
    vector<long long> values = a;

    sort(values.begin(), values.end());
    values.erase(unique(values.begin(), values.end()), values.end());

    vector<int> rank;

    for (long long x : a) {
        int pos = lower_bound(values.begin(), values.end(), x) - values.begin();
        rank.push_back(pos);
    }

    return {rank, values};
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
    auto result = compress(a);
    vector<int> ans = result.first;
    for (int i = 0; i < (int)ans.size(); i++) {
        if (i > 0) {
            cout << ' ';
        }
        cout << ans[i];
    }
    cout << '\n';

    return 0;
}
