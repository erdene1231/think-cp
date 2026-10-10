#include <bits/stdc++.h>
using namespace std;

vector<int> selected_indices(int n, unsigned int mask) {
    vector<int> ans;

    for (int i = 0; i < n; i++) {
        unsigned int bit = 1u << i;

        if ((mask & bit) != 0) {
            ans.push_back(i);
        }
    }

    return ans;
}
