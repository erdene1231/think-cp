#include <bits/stdc++.h>
using namespace std;

void tree_dfs(int v, int p, const vector<vector<int>>& adj,
              vector<int>& parent, vector<int>& depth, vector<int>& sz) {
    parent[v] = p;
    sz[v] = 1;

    for (int u : adj[v]) {
        if (u == p) {
            continue;
        }

        depth[u] = depth[v] + 1;
        tree_dfs(u, v, adj, parent, depth, sz);
        sz[v] += sz[u];
    }
}
