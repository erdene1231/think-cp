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
