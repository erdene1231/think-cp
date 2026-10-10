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
