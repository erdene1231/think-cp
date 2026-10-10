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
