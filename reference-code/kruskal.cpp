#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> parent;
    vector<int> sz;

    DSU(int n) {
        parent.resize(n);
        sz.assign(n, 1);
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int v) {
        if (parent[v] == v) {
            return v;
        }

        parent[v] = find(parent[v]);
        return parent[v];
    }

    bool unite(int u, int v) {
        u = find(u);
        v = find(v);

        if (u == v) {
            return false;
        }

        if (sz[u] < sz[v]) {
            swap(u, v);
        }

        parent[v] = u;
        sz[u] += sz[v];
        return true;
    }
};

struct Edge {
    int u;
    int v;
    long long w;
};

bool compare_edges(const Edge& a, const Edge& b) {
    return a.w < b.w;
}

pair<bool, long long> kruskal(int n, vector<Edge> edges) {
    sort(edges.begin(), edges.end(), compare_edges);
    DSU dsu(n);
    long long ans = 0;
    int used = 0;

    for (const auto& edge : edges) {
        if (dsu.unite(edge.u, edge.v)) {
            ans += edge.w;
            used++;
        }
    }

    return {used == n - 1, ans};
}
