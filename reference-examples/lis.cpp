#include <bits/stdc++.h>
using namespace std;

int lis_length(const vector<long long>& a) {
    int n = a.size();
    vector<int> dp(n, 1);
    int ans = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (a[j] < a[i]) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }

        ans = max(ans, dp[i]);
    }

    return ans;
}

int main() {
    vector<long long> a = {3, 1, 2, 5, 4};
    cout << lis_length(a) << '\n';

    return 0;
}
