#include <bits/stdc++.h>
using namespace std;

vector<int> prefix_function(const string& p) {
    int m = p.size();
    vector<int> pi(m, 0);

    for (int i = 1; i < m; i++) {
        int j = pi[i - 1];

        while (j > 0 && p[i] != p[j]) {
            j = pi[j - 1];
        }

        if (p[i] == p[j]) {
            j++;
        }

        pi[i] = j;
    }

    return pi;
}

vector<int> kmp(const string& s, const string& p) {
    int n = s.size();
    int m = p.size();
    vector<int> ans;

    if (m == 0) {
        for (int i = 0; i <= n; i++) {
            ans.push_back(i);
        }

        return ans;
    }

    vector<int> pi = prefix_function(p);
    int j = 0;

    for (int i = 0; i < n; i++) {
        while (j > 0 && s[i] != p[j]) {
            j = pi[j - 1];
        }

        if (s[i] == p[j]) {
            j++;
        }

        if (j == m) {
            ans.push_back(i - m + 1);
            j = pi[j - 1];
        }
    }

    return ans;
}
