#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> parent;
    vector<int> sz;

    DSU(int n) {
        parent.resize(n);
        sz.assign(n, 1);

        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int find(int v) {
        if (parent[v] == v) {
            return v;
        }

        parent[v] = find(parent[v]);
        return parent[v];
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);

        if (a == b) {
            return false;
        }

        if (sz[a] < sz[b]) {
            swap(a, b);
        }

        parent[b] = a;
        sz[a] += sz[b];

        return true;
    }

    int size(int v) {
        int root = find(v);
        return sz[root];
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    DSU dsu(n);
    for (int i = 0; i < q; i++) {
        string type;
        int u;
        cin >> type >> u;
        if (type == "size") {
            cout << dsu.size(u) << '\n';
        } else {
            int v;
            cin >> v;
            if (type == "union") {
                dsu.unite(u, v);
            } else if (type == "same") {
                cout << (dsu.find(u) == dsu.find(v) ? "YES" : "NO") << '\n';
            }
        }
    }

    return 0;
}
