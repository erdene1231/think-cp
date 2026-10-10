#include <bits/stdc++.h>
using namespace std;

const long long INF = 4'000'000'000'000'000'000LL;

vector<long long> dijkstra(const vector<vector<pair<int, long long>>>& adj, int s) {
    int n = adj.size();
    vector<long long> dist(n, INF);

    // Each state stores (distance, vertex).
    using State = pair<long long, int>;
    priority_queue<State, vector<State>, greater<State>> pq;

    dist[s] = 0;
    pq.push({0, s});

    while (!pq.empty()) {
        long long d = pq.top().first;
        int v = pq.top().second;
        pq.pop();

        if (d != dist[v]) {
            continue;
        }

        for (const auto& edge : adj[v]) {
            int u = edge.first;
            long long w = edge.second;

            if (d > INF - w) {
                continue;
            }

            long long new_dist = d + w;

            if (new_dist < dist[u]) {
                dist[u] = new_dist;
                pq.push({dist[u], u});
            }
        }
    }

    return dist;
}
