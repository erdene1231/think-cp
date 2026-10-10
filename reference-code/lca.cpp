#include <bits/stdc++.h>
using namespace std;

struct LCA {
    int n;
    int LOG;
    vector<int> depth;
    vector<vector<int>> up;

    LCA(const vector<vector<int>>& adj, int root) {
        n = adj.size();
        LOG = 1;

        while ((1LL << LOG) <= n) {
            LOG++;
        }

        depth.assign(n, -1);
        up.assign(LOG, vector<int>(n, root));
        queue<int> q;

        depth[root] = 0;
        q.push(root);

        while (!q.empty()) {
            int v = q.front();
            q.pop();

            for (int u : adj[v]) {
                if (depth[u] == -1) {
                    depth[u] = depth[v] + 1;
                    up[0][u] = v;
                    q.push(u);
                }
            }
        }

        for (int k = 1; k < LOG; k++) {
            for (int v = 0; v < n; v++) {
                int parent = up[k - 1][v];
                up[k][v] = up[k - 1][parent];
            }
        }
    }

    int query(int u, int v) const {
        if (depth[u] < depth[v]) {
            swap(u, v);
        }

        int diff = depth[u] - depth[v];

        for (int k = 0; k < LOG; k++) {
            if ((diff & (1 << k)) != 0) {
                u = up[k][u];
            }
        }

        if (u == v) {
            return u;
        }

        for (int k = LOG - 1; k >= 0; k--) {
            if (up[k][u] != up[k][v]) {
                u = up[k][u];
                v = up[k][v];
            }
        }

        return up[0][u];
    }

    int distance(int u, int v) const {
        int ancestor = query(u, v);
        return depth[u] + depth[v] - 2 * depth[ancestor];
    }
};
