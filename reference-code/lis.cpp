#include <bits/stdc++.h>
using namespace std;

int lis_length(const vector<long long>& a) {
    vector<long long> tails;

    for (long long x : a) {
        int pos = lower_bound(tails.begin(), tails.end(), x) - tails.begin();

        if (pos == (int) tails.size()) {
            tails.push_back(x);
        } else {
            tails[pos] = x;
        }
    }

    return tails.size();
}
