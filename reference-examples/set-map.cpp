#include <bits/stdc++.h>
using namespace std;

map<long long, int> frequencies(const vector<long long>& a) {
    map<long long, int> freq;

    for (long long x : a) {
        freq[x]++;
    }

    return freq;
}

int distinct_count(const vector<long long>& a) {
    set<long long> values;

    for (long long x : a) {
        values.insert(x);
    }

    return values.size();
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
    map<long long, int> freq = frequencies(a);
    cout << distinct_count(a) << '\n';
    for (const auto& entry : freq) {
        cout << entry.first << ' ' << entry.second << '\n';
    }

    return 0;
}
