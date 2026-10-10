#include <bits/stdc++.h>
using namespace std;

bool topological(const vector<vector<int>>& adj, vector<int>& order) {
    int n = adj.size();
    vector<int> indegree(n, 0);
    queue<int> q;
    order.clear();

    for (int v = 0; v < n; v++) {
        for (int u : adj[v]) {
            indegree[u]++;
        }
    }

    for (int v = 0; v < n; v++) {
        if (indegree[v] == 0) {
            q.push(v);
        }
    }

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        order.push_back(v);

        for (int u : adj[v]) {
            indegree[u]--;

            if (indegree[u] == 0) {
                q.push(u);
            }
        }
    }

    if ((int) order.size() != n) {
        order.clear();
        return false;
    }

    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }
    vector<int> ans;
    if (topological(adj, ans)) {
        for (int i = 0; i < (int)ans.size(); i++) {
            if (i > 0) {
                cout << ' ';
            }
            cout << ans[i];
        }
        cout << '\n';
    } else {
        cout << "CYCLE\n";
    }

    return 0;
}
