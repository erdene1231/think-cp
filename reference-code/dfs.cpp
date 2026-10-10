#include <bits/stdc++.h>
using namespace std;

void dfs(int v, int id, const vector<vector<int>>& adj, vector<int>& comp) {
    comp[v] = id;

    for (int u : adj[v]) {
        if (comp[u] == -1) {
            dfs(u, id, adj, comp);
        }
    }
}

vector<int> components(const vector<vector<int>>& adj) {
    int n = adj.size();
    vector<int> comp(n, -1);
    int count = 0;

    for (int v = 0; v < n; v++) {
        if (comp[v] == -1) {
            dfs(v, count, adj, comp);
            count++;
        }
    }

    return comp;
}
