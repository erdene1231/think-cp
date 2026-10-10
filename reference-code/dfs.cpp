#include <bits/stdc++.h>
using namespace std;

vector<int> components(const vector<vector<int>>& adj) {
    int n = adj.size();
    int count = 0;
    vector<int> comp(n, -1);

    for (int s = 0; s < n; s++) {
        if (comp[s] != -1) {
            continue;
        }

        stack<int> st;
        st.push(s);
        comp[s] = count;

        while (!st.empty()) {
            int v = st.top();
            st.pop();

            for (int u : adj[v]) {
                if (comp[u] == -1) {
                    comp[u] = count;
                    st.push(u);
                }
            }
        }

        count++;
    }

    return comp;
}
