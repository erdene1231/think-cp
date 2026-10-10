#include <bits/stdc++.h>
using namespace std;

pair<vector<int>, vector<int>> bfs(const vector<vector<int>>& adj, int s) {
    int n = adj.size();
    vector<int> dist(n, -1);
    vector<int> parent(n, -1);
    queue<int> q;

    dist[s] = 0;
    q.push(s);

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        for (int u : adj[v]) {
            if (dist[u] == -1) {
                dist[u] = dist[v] + 1;
                parent[u] = v;
                q.push(u);
            }
        }
    }

    return {dist, parent};
}

int main() {
    vector<vector<int>> adj = {{1, 2}, {0, 3}, {0, 3}, {1, 2, 4}, {3}};
    auto result = bfs(adj, 0);
    vector<int> dist = result.first;

    cout << dist[4] << '\n';

    return 0;
}
