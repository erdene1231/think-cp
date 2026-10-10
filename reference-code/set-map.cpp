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
