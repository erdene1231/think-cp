#include <bits/stdc++.h>
using namespace std;

vector<int> next_greater(const vector<long long>& a) {
    int n = a.size();
    vector<int> ans(n, -1);
    stack<int> st;

    for (int i = 0; i < n; i++) {
        while (!st.empty() && a[st.top()] < a[i]) {
            int j = st.top();
            st.pop();

            ans[j] = i;
        }

        st.push(i);
    }

    return ans;
}
