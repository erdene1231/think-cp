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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    unsigned int mask;
    cin >> n >> mask;
    vector<int> ans = selected_indices(n, mask);
    for (int i = 0; i < (int)ans.size(); i++) {
        if (i > 0) {
            cout << ' ';
        }
        cout << ans[i];
    }
    cout << '\n';

    return 0;
}
