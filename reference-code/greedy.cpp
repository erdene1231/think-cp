#include <bits/stdc++.h>
using namespace std;

bool compare_intervals(const pair<long long, long long>& a,
                       const pair<long long, long long>& b) {
    if (a.second != b.second) {
        return a.second < b.second;
    }

    return a.first < b.first;
}

int max_intervals(vector<pair<long long, long long>> intervals) {
    sort(intervals.begin(), intervals.end(), compare_intervals);

    long long last_end = LLONG_MIN;
    int ans = 0;

    for (const auto& interval : intervals) {
        long long l = interval.first;
        long long r = interval.second;

        if (l >= last_end) {
            ans++;
            last_end = r;
        }
    }

    return ans;
}
