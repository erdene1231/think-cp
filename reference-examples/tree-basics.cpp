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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, root;
    cin >> n >> root;
    vector<vector<int>> adj(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> parent(n, -1), depth(n, 0), sz(n, 0);
    tree_dfs(root, -1, adj, parent, depth, sz);
    for (int v = 0; v < n; v++) {
        cout << parent[v] << ' ' << depth[v] << ' ' << sz[v] << '\n';
    }

    return 0;
}
