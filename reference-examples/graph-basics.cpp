#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> make_graph(int n, const vector<pair<int, int>>& edges) {
    vector<vector<int>> adj(n);

    for (const auto& edge : edges) {
        int u = edge.first;
        int v = edge.second;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    return adj;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> edges(m);
    for (int i = 0; i < m; i++) {
        cin >> edges[i].first >> edges[i].second;
    }
    auto adj = make_graph(n, edges);
    for (int v = 0; v < n; v++) {
        cout << v << ':';
        for (int u : adj[v]) {
            cout << ' ' << u;
        }
        cout << '\n';
    }

    return 0;
}
